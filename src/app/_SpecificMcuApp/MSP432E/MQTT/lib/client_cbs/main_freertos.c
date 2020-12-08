// /*
//  * Copyright (c) 2016-2019, Texas Instruments Incorporated
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  *
//  * *  Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  *
//  * *  Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * *  Neither the name of Texas Instruments Incorporated nor the names of
//  *    its contributors may be used to endorse or promote products derived
//  *    from this software without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
//  * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//  * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//  * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
//  * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//  * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
//  * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
//  * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
//  * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
//  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  */

// /*
//  *  ======== main_freertos.c ========
//  */

// /* RTOS header files */
// #include <FreeRTOS.h>
// #include <task.h>
// #include <ti/display/Display.h>

// /* Driver configuration */
// #include <ti/drivers/Board.h>

// extern void ti_ndk_config_Global_startupFxn();

// Display_Handle display;

// /*
//  *  ======== main ========
//  */
// int main(void)
// {
//     /* Call driver init functions */
//     Board_init();

//     /* Configure the Display module for UART output */
//     Display_init();

//     display = Display_open(Display_Type_UART, NULL);
//     if (display == NULL)
//     {
//         /* Failed to open Display module */
//         while (1)
//             ;
//     }

//     ti_ndk_config_Global_startupFxn();

//     /* Start the FreeRTOS scheduler */
//     vTaskStartScheduler();

//     return (0);
// }

// //*****************************************************************************
// //
// //! \brief Application defined malloc failed hook
// //!
// //! \param  none
// //!
// //! \return none
// //!
// //*****************************************************************************
// void vApplicationMallocFailedHook()
// {
//     /* Handle Memory Allocation Errors */
//     while (1)
//     {
//     }
// }

// //*****************************************************************************
// //
// //! \brief Application defined stack overflow hook
// //!
// //! \param  none
// //!
// //! \return none
// //!
// //*****************************************************************************
// void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
// {
//     //Handle FreeRTOS Stack Overflow
//     while (1)
//     {
//     }
// }
