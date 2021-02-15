#include "pa_Output.h"
#if output_use
#include "mcuDrvs/pa_Output_drv.h"
namespace Output
{
    void pa_print(const char *format)
    {
#if output_use_cdc
        cdc_print(format);
#endif
    }
} // namespace Output
#endif
