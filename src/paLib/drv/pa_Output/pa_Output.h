#ifndef __PA_OUTPUT_H__
#define __PA_OUTPUT_H__
#include "paLib/drv/pa_BaseDrv/pa_BaseDrv.h"

#if output_use
// class Output
// {
// private:
//     /* data */
// public:
//     static void pa_print(const char *format);
// };

namespace Output
{
    void pa_print(const char *format);
    //     {
    // #if output_use_cdc
    //         cdc_print(format);
    // #endif
    //     }
} // namespace Output
#endif
#endif // __PA_OUTPUT_H__