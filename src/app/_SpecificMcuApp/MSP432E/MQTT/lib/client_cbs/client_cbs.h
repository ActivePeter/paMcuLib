/*
 * Copyright (c) 2016-2018, Texas Instruments Incorporated
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

#ifndef __SERVER_CLIENT_CBS_H__
#define __SERVER_CLIENT_CBS_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

/* MQTT library includes                                                      */
#include <ti/net/mqtt/mqttserver.h>
#include <ti/net/mqtt/mqttclient.h>

//*****************************************************************************
// Macros
//*****************************************************************************
#define MAX_CONNECTION              1

#define PUBLISH_PUSH_BUTTON_PRESSED 1
#define MSG_RECV_BY_CLIENT          11
#define LOCAL_CLIENT_DISCONNECTION  12 /* Client disconnected from remote broker       */
#define DISC_PUSH_BUTTON_PRESSED    14
#define THREAD_TERMINATE_REQ        15

//*****************************************************************************
// typedef enum/struct/union
//*****************************************************************************
struct publishMsgHeader
{
    uint32_t        topicLen;
    uint32_t        payLen;
    bool            retain;
    bool            dup;
    unsigned char   qos;
};

struct client_info
{
    void *ctx;
};

struct msgQueue
{
    int32_t     event;
    void        *msgPtr;
    int32_t     topLen;
};

//******************************************************************************
// APIs
//******************************************************************************

extern void MqttClientCallback(int32_t event , void * metaData , uint32_t metaDateLen , void *data , uint32_t dataLen);
//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __SERVER_CLIENT_CBS_H__
