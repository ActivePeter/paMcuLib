/*
 * Copyright (c) 2016-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*****************************************************************************

 Application Name     -   MQTT Client
 Application Overview -   The device is running a MQTT client which is
                           connected to the online broker. An LED on the
                           device can be controlled from a web client by
                           publishing msgs on a topic. Similarly,
                           message can be published on a pre-configured topic
                           by pressing the a switch button on the device.

 Application Details  - Refer to 'MQTT Client' README.html

 *****************************************************************************/
/* Standard includes                                                          */
#include <stdlib.h>
#include <pthread.h>
#include <mqueue.h>
#include <time.h>
#include <unistd.h>

/* TI-Driver includes                                                         */
#include <ti/drivers/GPIO.h>
#include <ti/display/Display.h>

/* NDK includes */
#include <ti/ndk/inc/netmain.h>
#include <ti/ndk/inc/stkmain.h>

/* MQTT Library includes                                                      */
#include <ti/net/mqtt/mqttclient.h>

/* Application includes                                                       */
#include "ti_drivers_config.h"
#include "client_cbs.h"

#include "../pa_Mqtt/pa_Mqtt.h"
//*****************************************************************************
//                          LOCAL DEFINES
//*****************************************************************************
/* enables secured client                                                     */
//#define SECURE_CLIENT

/* enables client authentication by the server                                */
//#define CLNT_USR_PWD

#define CLIENT_INIT_STATE (0x01)
#define MQTT_INIT_STATE (0x04)

#define APPLICATION_VERSION "1.1.1"
#define APPLICATION_NAME "MQTT client"

/* Length of MAC address */
#define SL_MAC_ADDR_LEN (6)

/* Operate Lib in MQTT 3.1 mode.                                              */
#define MQTT_3_1_1 false
#define MQTT_3_1 true

#define WILL_TOPIC "Client"
#define WILL_MSG "Client Stopped"
#define WILL_QOS MQTT_QOS_2
#define WILL_RETAIN false

/* Defining Broker IP address and port Number                                 */
#define SERVER_ADDRESS "192.168.199.145"
// #define SERVER_IP_ADDRESS "192.168.178.67"
#define PORT_NUMBER 1883
#define SECURED_PORT_NUMBER 8883
#define LOOPBACK_PORT 1882

/* Clean session flag                                                         */
#define CLEAN_SESSION true

/* Retain Flag. Used in publish message.                                      */
#define RETAIN_ENABLE 1

/* Defining Number of subscription topics                                     */
#define SUBSCRIPTION_TOPIC_COUNT 2

/* Defining Subscription Topic Values                                         */
#define SUBSCRIPTION_TOPIC0 "/Broker/To/simplelink"
#define SUBSCRIPTION_TOPIC1 "/simplelink/ToggleLEDCmdL0"

/* Defining Publish Topic Values                                              */
#define PUBLISH_TOPIC0 "/simplelink/ButtonPressEvt0"
#define PUBLISH_TOPIC0_DATA "Push Button 0 has been pressed on " \
                            "SimpleLink device"

/* Spawn task priority and Task and Thread Stack Size                         */
#define TASKSTACKSIZE 2048
#define RXTASKSIZE 4096
#define MQTTTHREADSIZE 8192
#define SPAWN_TASK_PRIORITY 9

extern void startSNTP(void);

extern void *TaskSelf();

/* Number of files used for secure connection                                 */
#define CLIENT_NUM_SECURE_FILES 1

/* Expiration value for the timer that is being used to toggle the Led.       */
#define TIMER_EXPIRATION_VALUE 100 * 1000000

//*****************************************************************************
//                      LOCAL FUNCTION PROTOTYPES
//*****************************************************************************
void pushButtonInterruptHandler0(uint_least8_t index);
void pushButtonInterruptHandler1(uint_least8_t index);
static void DisplayBanner(char *AppName);
void *MqttClient(void *arg0);
void Mqtt_ClientStop(uint8_t disconnect);
void Mqtt_ServerStop();
void Mqtt_Stop();
void Mqtt_start();
int32_t Mqtt_IF_Connect();
int32_t MqttServer_start();
int32_t MqttClient_start();
int32_t MQTT_SendMsgToQueue(struct msgQueue *queueElement);

//*****************************************************************************
//                 GLOBAL VARIABLES
//*****************************************************************************

/* Connection state: (0) - connected, (negative) - disconnected               */
int32_t gApConnectionState = -1;
uint32_t gInitState = 0;
uint32_t memPtrCounterfree = 0;
bool gResetApplication = false;
static MQTTClient_Handle gMqttClient;
MQTTClient_Params MqttClientExmple_params;
unsigned short g_usTimerInts;

/* Receive task handle                                                        */
pthread_t g_rx_task_hndl = (pthread_t)NULL;
uint32_t gUiConnFlag = 0;

/* Display instance for output to UART */
extern Display_Handle display;

/* AP Security Parameters                                                     */
//SlWlanSecParams_t SecurityParams = { 0 };

/* Client ID                                                                  */
/* If ClientId isn't set, the MAC address of the device will be copied into   */
/* the ClientID parameter.                                                    */
char ClientId[13] = {'\0'};

/* Client User Name and Password                                              */
const char *ClientUsername = "username1";
const char *ClientPassword = "pwd1";

/* Subscription topics and qos values                                         */
char *topic[SUBSCRIPTION_TOPIC_COUNT] =
    {SUBSCRIPTION_TOPIC0, SUBSCRIPTION_TOPIC1};

unsigned char qos[SUBSCRIPTION_TOPIC_COUNT] =
    {MQTT_QOS_2, MQTT_QOS_2};

/* Publishing topics and messages                                             */
const char *publish_topic = {PUBLISH_TOPIC0};
const char *publish_data = {PUBLISH_TOPIC0_DATA};

/* Message Queue                                                              */
mqd_t g_PBQueue;
pthread_t mqttThread = (pthread_t)NULL;
pthread_t appThread = (pthread_t)NULL;
timer_t g_timer;

/* Printing new line                                                          */
char lineBreak[] = "\n\r";

//*****************************************************************************
//                 Banner VARIABLES
//*****************************************************************************
#ifdef SECURE_CLIENT
/* SL network layer includes */
#include <ti/net/slnetif.h>
#include <ti/net/slnetsock.h>

char *Mqtt_Client_secure_files[CLIENT_NUM_SECURE_FILES] = {"ca-cert.pem"};

/* Initialization structure to be used with sl_ExtMqtt_Init API. In order to  */
/* use secured socket method, the flag MQTTCLIENT_NETCONN_SEC, cipher,        */
/* n_files and secure_files must be configured.                               */
/* certificates also must be programmed  ("ca-cert.pem").                     */
/* The first parameter is a bit mask which configures server address type and */
/* security mode.                                                             */
/* Server address type: IPv4, IPv6 and URL must be declared with The          */
/* corresponding flag.                                                        */
/* Security mode: The flag MQTTCLIENT_NETCONN_SEC enables the security (TLS)  */
/* which includes domain name verification and certificate catalog            */
/* verification, those verifications can be disabled by adding to the bit mask*/
/* MQTTCLIENT_NETCONN_SKIP_DOMAIN_NAME_VERIFICATION and                       */
/* MQTTCLIENT_NETCONN_SKIP_CERTIFICATE_CATALOG_VERIFICATION flags             */
/* Example: MQTTCLIENT_NETCONN_IP6 | MQTTCLIENT_NETCONN_SEC |                 */
/* MQTTCLIENT_NETCONN_SKIP_CERTIFICATE_CATALOG_VERIFICATION                   */
/* For this bit mask, the IPv6 address type will be in use, the security      */
/* feature will be enable and the certificate catalog verification will be    */
/* skipped.                                                                   */
/* Note: The domain name verification requires URL Server address type        */
/*       otherwise, this verification will be disabled.                       */
MQTTClient_ConnParams Mqtt_ClientCtx =
    {
        MQTTCLIENT_NETCONN_URL | MQTTCLIENT_NETCONN_SEC |
            MQTTCLIENT_NETCONN_SKIP_CERTIFICATE_CATALOG_VERIFICATION |
            MQTTCLIENT_NETCONN_SKIP_DOMAIN_NAME_VERIFICATION,
        SERVER_ADDRESS,
        SECURED_PORT_NUMBER, //  PORT_NUMBER
        SLNETSOCK_SEC_METHOD_SSLv3_TLSV1_2,
        SLNETSOCK_SEC_CIPHER_FULL_LIST,
        CLIENT_NUM_SECURE_FILES,
        Mqtt_Client_secure_files};
#else
MQTTClient_ConnParams Mqtt_ClientCtx =
    {
        MQTTCLIENT_NETCONN_IP4,
        SERVER_ADDRESS,
        PORT_NUMBER, 0, 0, 0,
        NULL};
#endif

/* Initialize the will_param structure to the default will parameters         */
MQTTClient_Will will_param =
    {
        WILL_TOPIC,
        WILL_MSG,
        WILL_QOS,
        WILL_RETAIN};

//*****************************************************************************
//
//! MQTT_SendMsgToQueue - Utility function that receive msgQueue parameter and
//! tries to push it the queue with minimal time for timeout of 0.
//! If the queue isn't full the parameter will be stored and the function
//! will return 0.
//! If the queue is full and the timeout expired (because the timeout parameter
//! is 0 it will expire immediately), the parameter is thrown away and the
//! function will return -1 as an error for full queue.
//!
//! \param[in] struct msgQueue *queueElement
//!
//! \return 0 on success, -1 on error
//
//*****************************************************************************
int32_t MQTT_SendMsgToQueue(struct msgQueue *queueElement)
{
    struct timespec abstime = {0};

    clock_gettime(CLOCK_REALTIME, &abstime);

    if (g_PBQueue)
    {
        /* send message to the queue                                         */
        if (mq_timedsend(g_PBQueue, (char *)queueElement,
                         sizeof(struct msgQueue), 0, &abstime) == 0)
        {
            return (0);
        }
    }
    return (-1);
}

//*****************************************************************************
//
//! Push Button Handler0. Press push button 0 whenever user
//! wants to publish a message. Write message into message queue signaling the
//! event publish messages
//!
//! \param none
//!
//! return none
//
//*****************************************************************************
void pushButtonInterruptHandler0(uint_least8_t index)
{
    struct msgQueue queueElement;

    /* Disable the interrupt for button 0 */
    GPIO_disableInt(CONFIG_GPIO_BUTTON_0);

    queueElement.event = PUBLISH_PUSH_BUTTON_PRESSED;
    queueElement.msgPtr = NULL;

    /* write message indicating publish message                              */
    {
        if (MQTT_SendMsgToQueue(&queueElement))
            Display_printf(display, 0, 0, "\n\n\rQueue is full\n\r");
    }
}

//*****************************************************************************
//
//! Push Button Handler1. Press push button 1 whenever user wants to
//! disconnect from the remote broker. Write message into message queue
//! indicating disconnect from broker.
//!
//! \param none
//!
//! return none
//
//*****************************************************************************
void pushButtonInterruptHandler1(uint_least8_t index)
{
    struct msgQueue queueElement;
    struct msgQueue queueElemRecv;

    queueElement.event = DISC_PUSH_BUTTON_PRESSED;
    queueElement.msgPtr = NULL;

    /* write message indicating disconnect push button pressed message       */
    if (MQTT_SendMsgToQueue(&queueElement))
    {
        Display_printf(display, 0, 0,
                       "\n\n\rQueue is full, throw first msg and send the new "
                       "one\n\r");
        mq_receive(g_PBQueue, (char *)&queueElemRecv, sizeof(struct msgQueue),
                   NULL);
        MQTT_SendMsgToQueue(&queueElement);
    }
}

//*****************************************************************************
//
//! Application startup display on UART
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
static void DisplayBanner(char *AppName)
{
    Display_printf(display, 0, 0, "\n\n\r");
    Display_printf(display, 0, 0,
                   "\t\t *************************************************");
    Display_printf(display, 0, 0,
                   "\t\t    SimpleLink %s Application       ", AppName);
    Display_printf(display, 0, 0,
                   "\t\t *************************************************");
    Display_printf(display, 0, 0, "\n\n\r");
}

void *MqttClientThread(void *arg0)
{
    struct msgQueue queueElement;
    struct msgQueue queueElemRecv;

    fdOpenSession(TaskSelf());

    MQTTClient_run((MQTTClient_Handle)arg0);

    queueElement.event = LOCAL_CLIENT_DISCONNECTION;
    queueElement.msgPtr = NULL;

    /* write message indicating disconnect Broker message.                    */
    if (MQTT_SendMsgToQueue(&queueElement))
    {
        Display_printf(display, 0, 0,
                       "\n\n\rQueue is full, throw first msg and send the new "
                       "one\n\r");
        mq_receive(g_PBQueue, (char *)&queueElemRecv, sizeof(struct msgQueue),
                   NULL);
        MQTT_SendMsgToQueue(&queueElement);
    }

    fdCloseSession(TaskSelf());

    return (NULL);
}

//*****************************************************************************
//
//! Task implementing MQTT Client
//!
//! This function
//!    1. Initializes network driver and connects to the default AP
//!    2. Initializes the mqtt client and server libraries and sets up MQTT
//!       with the remote broker.
//!    3. sets up the button events and their callbacks(for publishing)
//!    4. handles the callback signals
//!
//! \param  none
//!
//! \return None
//!
//*****************************************************************************
void *MqttClient(void *arg0)
{

    struct msgQueue queueElemRecv;
    long lRetVal = -1;
    char *tmpBuff;

    fdOpenSession(TaskSelf());

    /* Initializing Client and Subscribing to the Broker.                     */
    if (gApConnectionState >= 0)
    {
        lRetVal = MqttClient_start();
        if (lRetVal == -1)
        {
            Display_printf(display, 0, 0,
                           "MQTT Client lib initialization failed");
            return (NULL);
        }
    }

    /* handling the signals from various callbacks including the push button  */
    /* prompting the client to publish a msg on PUB_TOPIC OR msg received by  */
    /* the server on enrolled topic(for which the on-board client ha enrolled)*/
    /* from a local client(will be published to the remote broker by the      */
    /* client) OR msg received by the client from the remote broker (need to  */
    /* be sent to the server to see if any local client has subscribed on the */
    /* same topic).                                                           */
    for (;;)
    {
        /* waiting for signals                                                */
        mq_receive(g_PBQueue, (char *)&queueElemRecv, sizeof(struct msgQueue),
                   NULL);

        switch (queueElemRecv.event)
        {
        case PUBLISH_PUSH_BUTTON_PRESSED:

            /* send publish message                                       */
            lRetVal = MQTTClient_publish(gMqttClient, (char *)publish_topic,
                                         strlen((char *)publish_topic), (char *)publish_data,
                                         strlen((char *)publish_data), MQTT_QOS_2 | ((RETAIN_ENABLE) ? MQTT_PUBLISH_RETAIN : 0));

            Display_printf(display, 0, 0,
                           "\n\r Publishes the following message ");
            Display_printf(display, 0, 0, "Topic: %s", publish_topic);
            Display_printf(display, 0, 0, "Data: %s", publish_data);

            /* Clear and reenable the button 0 interrupt */
            GPIO_clearInt(CONFIG_GPIO_BUTTON_0);
            GPIO_enableInt(CONFIG_GPIO_BUTTON_0);

            break;

            /* msg received by client from remote broker (on a topic      */
            /* subscribed by local client)                                */
        case MSG_RECV_BY_CLIENT:
            tmpBuff = (char *)((char *)queueElemRecv.msgPtr + 12);
            if (strncmp(tmpBuff, SUBSCRIPTION_TOPIC1, queueElemRecv.topLen) == 0)
            {
                GPIO_toggle(CONFIG_GPIO_LED_0);
            }

            free(queueElemRecv.msgPtr);
            break;

            /* On-board client disconnected from remote broker, only      */
            /* local MQTT network will work                               */
        case LOCAL_CLIENT_DISCONNECTION:
            Display_printf(display, 0, 0,
                           "\n\rOn-board Client Disconnected");
            gUiConnFlag = 0;
            break;

            /* Push button for full restart check                         */
        case DISC_PUSH_BUTTON_PRESSED:
            gResetApplication = true;
            break;

        case THREAD_TERMINATE_REQ:
            gUiConnFlag = 0;
            fdCloseSession(TaskSelf());
            return (NULL);

        default:
            sleep(1);
            break;
        }
    }
}
void pa_Mqtt_publish(char *topic, uint16_t topicLen, char *data, uint16_t dataLen)
{
    // MQTTClient_publish(gMqttClient, topic,
    //                    topicLen, (char *)publish_data,
    //                    strlen((char *)publish_data), MQTT_QOS_2 | ((RETAIN_ENABLE) ? MQTT_PUBLISH_RETAIN : 0));
    MQTTClient_publish(gMqttClient,
                       topic,
                       topicLen,
                       data,
                       dataLen,
                       MQTT_QOS_2 | ((RETAIN_ENABLE) ? MQTT_PUBLISH_RETAIN : 0));
}
//*****************************************************************************
//
//! This function connect the MQTT device to an AP.
//!
//! \param  none
//!
//! \return None
//!
//*****************************************************************************
int32_t Mqtt_IF_Connect()
{
    /* Display Application Banner                                             */
    DisplayBanner(APPLICATION_NAME);

    /* Switch ON RED LED to indicate that Device acquired an IP.              */
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);

    sleep(1);

    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_OFF);

    return (0);
}

//*****************************************************************************
//!
//! MQTT Start - Initialize and create all the items required to run the MQTT
//! protocol
//!
//! \param  none
//!
//! \return None
//!
//*****************************************************************************
void Mqtt_start()
{
    pthread_t thread;
    pthread_attr_t attrs;
    struct sched_param priParam;
    int retc;
    int detachState;
    mq_attr attr;
    unsigned mode = 0;

    /* sync object for inter thread communication                             */
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(struct msgQueue);
    g_PBQueue = mq_open("g_PBQueue", O_CREAT, mode, &attr);

    if (g_PBQueue == NULL)
    {
        Display_printf(display, 0, 0, "MQTT Message Queue create fail");
        gInitState &= ~MQTT_INIT_STATE;
        return;
    }

    /* Set priority and stack size attributes */
    pthread_attr_init(&attrs);
    priParam.sched_priority = 2;

    detachState = PTHREAD_CREATE_DETACHED;
    retc = pthread_attr_setdetachstate(&attrs, detachState);
    if (retc != 0)
    {
        Display_printf(display, 0, 0,
                       "Mqtt_start: pthread_attr_setdetachstate() failed\n");
        while (1)
            ;
    }

    pthread_attr_setschedparam(&attrs, &priParam);

    retc |= pthread_attr_setstacksize(&attrs, MQTTTHREADSIZE);
    if (retc != 0)
    {
        Display_printf(display, 0, 0,
                       "Mqtt_start: pthread_attr_setstacksize() failed\n");
        while (1)
            ;
    }

    retc = pthread_create(&thread, &attrs, MqttClient, 0);
    if (retc != 0)
    {
        Display_printf(display, 0, 0,
                       "Mqtt_start: pthread_create() failed\n");
        while (1)
            ;
    }

    /* enable interrupts for the push buttons             */
    GPIO_setConfig(CONFIG_GPIO_BUTTON_0, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);
    GPIO_setCallback(CONFIG_GPIO_BUTTON_0, pushButtonInterruptHandler0);
    GPIO_enableInt(CONFIG_GPIO_BUTTON_0);

    GPIO_setConfig(CONFIG_GPIO_BUTTON_1, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);
    GPIO_setCallback(CONFIG_GPIO_BUTTON_1, pushButtonInterruptHandler1);
    GPIO_enableInt(CONFIG_GPIO_BUTTON_1);

    gInitState &= ~MQTT_INIT_STATE;
}

//*****************************************************************************
//!
//! MQTT Stop - Close the client instance and free all the items required to
//! run the MQTT protocol
//!
//! \param  none
//!
//! \return None
//!
//*****************************************************************************

void Mqtt_Stop()
{
    struct msgQueue queueElement;
    struct msgQueue queueElemRecv;

    if (gApConnectionState >= 0)
    {
        Mqtt_ClientStop(1);
    }

    queueElement.event = THREAD_TERMINATE_REQ;
    queueElement.msgPtr = NULL;

    /* write message indicating publish message                               */
    if (MQTT_SendMsgToQueue(&queueElement))
    {
        Display_printf(display, 0, 0,
                       "\n\n\rQueue is full, throw first msg and send the new one");
        mq_receive(g_PBQueue, (char *)&queueElemRecv, sizeof(struct msgQueue),
                   NULL);
        MQTT_SendMsgToQueue(&queueElement);
    }

    sleep(2);

    mq_close(g_PBQueue);
    g_PBQueue = NULL;

    Display_printf(display, 0, 0, "\n\r Client Stop completed");

    /* Disable the button interrupts */
    GPIO_disableInt(CONFIG_GPIO_BUTTON_0);
    GPIO_disableInt(CONFIG_GPIO_BUTTON_1);
}

int32_t MqttClient_start()
{
    pthread_t thread;
    pthread_attr_t attrs;
    struct sched_param priParam;
    int retc;
    int detachState;
    int32_t lRetVal = -1;
    int32_t iCount = 0;

    MqttClientExmple_params.clientId = ClientId;
    MqttClientExmple_params.connParams = &Mqtt_ClientCtx;
    MqttClientExmple_params.mqttMode31 = MQTT_3_1;
    MqttClientExmple_params.blockingSend = true;

    gInitState |= CLIENT_INIT_STATE;

    /* Initialize MQTT client lib                                             */
    gMqttClient = MQTTClient_create(MqttClientCallback, &MqttClientExmple_params);
    if (gMqttClient == NULL)
    {
        /* lib initialization failed                                          */
        gInitState &= ~CLIENT_INIT_STATE;
        return (-1);
    }

    /* Set priority and stack size attributes */
    pthread_attr_init(&attrs);
    priParam.sched_priority = 2;

    detachState = PTHREAD_CREATE_DETACHED;
    retc = pthread_attr_setdetachstate(&attrs, detachState);
    if (retc != 0)
    {
        Display_printf(display, 0, 0,
                       "MqttClient_start: pthread_attr_setdetachstate() failed\n");
        while (1)
            ;
    }

    pthread_attr_setschedparam(&attrs, &priParam);

    retc |= pthread_attr_setstacksize(&attrs, RXTASKSIZE);
    if (retc != 0)
    {
        Display_printf(display, 0, 0,
                       "MqttClient_start: pthread_attr_setstacksize() failed\n");
        while (1)
            ;
    }

    retc = pthread_create(&thread, &attrs, MqttClientThread, 0);
    if (retc != 0)
    {
        Display_printf(display, 0, 0,
                       "MqttClient_start: pthread_create() failed\n");
        while (1)
            ;
    }

#ifdef SECURE_CLIENT
    /*  Use SNTP to get the current time, as needed for SSL authentication */
    startSNTP();
#endif

    /* setting will parameters                                                */
    MQTTClient_set(gMqttClient, MQTTClient_WILL_PARAM, &will_param,
                   sizeof(will_param));

#ifdef CLNT_USR_PWD
    /* Set user name for client connection                                    */
    MQTTClient_set(gMqttClient, MQTTClient_USER_NAME, (void *)ClientUsername,
                   strlen((char *)ClientUsername));

    /* Set password                                                           */
    MQTTClient_set(gMqttClient, MQTTClient_PASSWORD, (void *)ClientPassword,
                   strlen((char *)ClientPassword));
#endif
    /* Initiate MQTT Connect                                                  */
    if (gApConnectionState >= 0)
    {
#if CLEAN_SESSION == false
        bool clean = CLEAN_SESSION;
        MQTTClient_set(gMqttClient, MQTTClient_CLEAN_CONNECT, (void *)&clean,
                       sizeof(bool));
#endif
        /* The return code of MQTTClient_connect is the ConnACK value that
           returns from the server */
        lRetVal = MQTTClient_connect(gMqttClient);

        /* negative lRetVal means error,
           0 means connection successful without session stored by the server,
           greater than 0 means successful connection with session stored by
           the server */
        if (0 > lRetVal)
        {
            /* lib initialization failed                                      */
            Display_printf(display, 0, 0,
                           "Connection to broker failed, Error code: %d", lRetVal);

            gUiConnFlag = 0;
        }
        else
        {
            gUiConnFlag = 1;
        }
        /* Subscribe to topics when session is not stored by the server       */
        if ((gUiConnFlag == 1) && (0 == lRetVal))
        {
            uint8_t subIndex;
            MQTTClient_SubscribeParams subscriptionInfo[SUBSCRIPTION_TOPIC_COUNT];

            for (subIndex = 0; subIndex < SUBSCRIPTION_TOPIC_COUNT; subIndex++)
            {
                subscriptionInfo[subIndex].topic = topic[subIndex];
                subscriptionInfo[subIndex].qos = qos[subIndex];
            }

            if (MQTTClient_subscribe(gMqttClient, subscriptionInfo,
                                     SUBSCRIPTION_TOPIC_COUNT) < 0)
            {
                Display_printf(display, 0, 0, "\n\r Subscription Error ");
                MQTTClient_disconnect(gMqttClient);
                gUiConnFlag = 0;
            }
            else
            {
                for (iCount = 0; iCount < SUBSCRIPTION_TOPIC_COUNT; iCount++)
                {
                    Display_printf(display, 0, 0,
                                   "Client subscribed on %s,", topic[iCount]);
                }
            }
        }
    }

    gInitState &= ~CLIENT_INIT_STATE;

    return (0);
}

//*****************************************************************************
//!
//! MQTT Client stop - Unsubscribe from the subscription topics and exit the
//! MQTT client lib.
//!
//! \param  none
//!
//! \return None
//!
//*****************************************************************************

void Mqtt_ClientStop(uint8_t disconnect)
{
    uint32_t iCount;

    MQTTClient_UnsubscribeParams subscriptionInfo[SUBSCRIPTION_TOPIC_COUNT];

    for (iCount = 0; iCount < SUBSCRIPTION_TOPIC_COUNT; iCount++)
    {
        subscriptionInfo[iCount].topic = topic[iCount];
    }

    MQTTClient_unsubscribe(gMqttClient, subscriptionInfo,
                           SUBSCRIPTION_TOPIC_COUNT);
    for (iCount = 0; iCount < SUBSCRIPTION_TOPIC_COUNT; iCount++)
    {
        Display_printf(display, 0, 0,
                       "Unsubscribed from the topic %s", topic[iCount]);
    }
    gUiConnFlag = 0;

    /* exiting the Client library                                             */
    MQTTClient_delete(gMqttClient);
}

//*****************************************************************************
//!
//! Utility function which prints the borders
//!
//! \param[in] ch  -  hold the charater for the border.
//! \param[in] n   -  hold the size of the border.
//!
//! \return none.
//!
//*****************************************************************************

void printBorder(char ch, int n)
{
    char *border = NULL;

    border = (char *)malloc(n + 1);
    if (border != NULL)
    {
        memset(border, ch, n);
        border[n] = '\0';
        Display_printf(display, 0, 0, border);
        free(border);
    }
    else
    {
        Display_printf(display, 0, 0, "out of memory");
        while (1)
            ;
    }
}

//*****************************************************************************
//!
//! Set the ClientId with its own mac address
//! This routine converts the mac address which is given
//! by an integer type variable in hexadecimal base to ASCII
//! representation, and copies it into the ClientId parameter.
//!
//! \param  macAddress  -   Points to string Hex.
//!
//! \return void.
//!
//*****************************************************************************
void SetClientIdNamefromMacAddress(uint8_t *macAddress)
{
    uint8_t Client_Mac_Name[2];
    uint8_t Index;

    /* When ClientID isn't set, use the mac address as ClientID               */
    if (ClientId[0] == '\0')
    {
        /* 6 bytes is the length of the mac address                           */
        for (Index = 0; Index < SL_MAC_ADDR_LEN; Index++)
        {
            /* Each mac address byte contains two hexadecimal characters      */
            /* Copy the 4 MSB - the most significant character                */
            Client_Mac_Name[0] = (macAddress[Index] >> 4) & 0xf;
            /* Copy the 4 LSB - the least significant character               */
            Client_Mac_Name[1] = macAddress[Index] & 0xf;

            if (Client_Mac_Name[0] > 9)
            {
                /* Converts and copies from number that is greater than 9 in  */
                /* hexadecimal representation (a to f) into ascii character   */
                ClientId[2 * Index] = Client_Mac_Name[0] + 'a' - 10;
            }
            else
            {
                /* Converts and copies from number 0 - 9 in hexadecimal       */
                /* representation into ascii character                        */
                ClientId[2 * Index] = Client_Mac_Name[0] + '0';
            }
            if (Client_Mac_Name[1] > 9)
            {
                /* Converts and copies from number that is greater than 9 in  */
                /* hexadecimal representation (a to f) into ascii character   */
                ClientId[2 * Index + 1] = Client_Mac_Name[1] + 'a' - 10;
            }
            else
            {
                /* Converts and copies from number 0 - 9 in hexadecimal       */
                /* representation into ascii character                        */
                ClientId[2 * Index + 1] = Client_Mac_Name[1] + '0';
            }
        }
    }
}

//*****************************************************************************
//!
//! Utility function which Display the app banner
//!
//! \param[in] appName     -  holds the application name.
//! \param[in] appVersion  -  holds the application version.
//!
//! \return none.
//!
//*****************************************************************************

int32_t DisplayAppBanner(char *appName, char *appVersion)
{
    int32_t ret = 0;
    uint8_t macAddress[SL_MAC_ADDR_LEN];
    uint16_t macAddressLen = SL_MAC_ADDR_LEN;
    NIMU_IF_REQ if_req;

    if_req.name[0] = 0;
    if_req.index = 1; /* ethernet IF # */

    ret = NIMUIoctl(NIMU_GET_DEVICE_MAC, &if_req, macAddress, macAddressLen);

    Display_printf(display, 0, 0, lineBreak);
    printBorder('=', 44);
    Display_printf(display, 0, 0, "   %s Example Ver: %s", appName, appVersion);
    printBorder('=', 44);
    Display_printf(display, 0, 0, lineBreak);
    Display_printf(display, 0, 0,
                   " MAC address: %02x:%02x:%02x:%02x:%02x:%02x", macAddress[0],
                   macAddress[1], macAddress[2], macAddress[3], macAddress[4],
                   macAddress[5]);
    Display_printf(display, 0, 0, lineBreak);
    printBorder('=', 44);
    Display_printf(display, 0, 0, lineBreak);

    SetClientIdNamefromMacAddress(macAddress);

    return (ret);
}

void *mainThread(void *arg0)
{

    uint32_t count = 0;
    int32_t retc = 0;

    // GPIO_init();
    // main_select();
    fdOpenSession(TaskSelf());

    /* Output device information to the UART terminal */
    retc = DisplayAppBanner(APPLICATION_NAME, APPLICATION_VERSION);
    if (retc < 0)
    {
        /* Handle Error */
        Display_printf(display, 0, 0, "\n DisplayAppBanner failed");
        while (1)
            ;
    }

#ifdef SECURE_CLIENT
    extern uint8_t externalCAPem[];
    extern uint16_t externalCAPemLen;

    retc = SlNetIf_loadSecObj(SLNETIF_SEC_OBJ_TYPE_CERTIFICATE,
                              Mqtt_Client_secure_files[0], strlen(Mqtt_Client_secure_files[0]),
                              externalCAPem, externalCAPemLen, SLNETIF_ID_2);
    if (retc < 0)
    {
        Display_printf(display, 0, 0, "failed to load security object");
        while (1)
            ;
    }
#endif

    while (1)
    {

        gResetApplication = false;
        topic[0] = SUBSCRIPTION_TOPIC0;
        topic[1] = SUBSCRIPTION_TOPIC1;
        gInitState = 0;

        /* Connect to AP                                                      */
        gApConnectionState = Mqtt_IF_Connect();

        gInitState |= MQTT_INIT_STATE;
        /* Run MQTT Main Thread (it will open the Client and Server)          */
        Mqtt_start();

        /* Wait for init to be completed!!!                                   */
        while (gInitState != 0)
        {
            Display_printf(display, 0, 0, ".");
            sleep(1);
        }
        Display_printf(display, 0, 0, ".");
        main_select();
        while (gResetApplication == false)
            ;

        Display_printf(display, 0, 0,
                       "TO Complete - Closing all threads and resources");

        /* Stop the MQTT Process                                              */
        Mqtt_Stop();

        Display_printf(display, 0, 0, "reopen MQTT # %d  ", ++count);
    }
}
