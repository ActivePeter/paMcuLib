#include <paLib/drv/pa_Ltdc/pa_Ltdc.hpp>

#if drv_ltdc
extern LTDC_HandleTypeDef hltdc;
// char Ltdc_buff[3000];
LTDC_LayerCfgTypeDef pLayerCfg = {0};
void Ltdc_init(RgbConfig rgbConfig)
{
    /* USER CODE BEGIN LTDC_Init 0 */
    // extern char Ltdc_buff[];
    // /* USER CODE END LTDC_Init 0 */
    // for (int i = 0; i < 3000; i++)
    // {
    //     Ltdc_buff[i] = i % 255;
    // }

    // LTDC_LayerCfgTypeDef pLayerCfg1 = {0};

    /* USER CODE BEGIN LTDC_Init 1 */

    /* USER CODE END LTDC_Init 1 */
    hltdc.Instance = LTDC;
    hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
    hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
    hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
    hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
    // hltdc.Init.HorizontalSync = 7;
    // hltdc.Init.VerticalSync = 3;
    // hltdc.Init.AccumulatedHBP = 14;
    // hltdc.Init.AccumulatedVBP = 5;
    // hltdc.Init.AccumulatedActiveW = 654;
    // hltdc.Init.AccumulatedActiveH = 485;
    // hltdc.Init.TotalWidth = 660;
    // hltdc.Init.TotalHeigh = 487;
    hltdc.Init.HorizontalSync = rgbConfig.HSW - 1;
    hltdc.Init.VerticalSync = rgbConfig.VSW - 1;
    hltdc.Init.AccumulatedHBP = rgbConfig.HSW + rgbConfig.HBP - 1;
    hltdc.Init.AccumulatedVBP = rgbConfig.VSW + rgbConfig.VBP - 1;
    hltdc.Init.AccumulatedActiveW = rgbConfig.HSW + rgbConfig.HBP + 480 - 1;
    hltdc.Init.AccumulatedActiveH = rgbConfig.VSW + rgbConfig.VBP + 800 - 1;
    hltdc.Init.TotalWidth = hltdc.Init.AccumulatedActiveW + rgbConfig.HFP;
    hltdc.Init.TotalHeigh = hltdc.Init.AccumulatedActiveH + rgbConfig.VFP;
    hltdc.Init.Backcolor.Blue = 0;
    hltdc.Init.Backcolor.Green = 0;
    hltdc.Init.Backcolor.Red = 255;
    if (HAL_LTDC_Init(&hltdc) != HAL_OK)
    {
        // Error_Handler();
    }
    pLayerCfg.WindowX0 = 0;
    pLayerCfg.WindowX1 = 480;
    pLayerCfg.WindowY0 = 0;
    pLayerCfg.WindowY1 = 800;
    pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB888;
    pLayerCfg.Alpha = 255;
    pLayerCfg.Alpha0 = 0;
    pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
    pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
    pLayerCfg.FBStartAdress = (uint32_t)0xC0000000;
    pLayerCfg.ImageWidth = 480;
    pLayerCfg.ImageHeight = 800;
    pLayerCfg.Backcolor.Blue = 0;
    pLayerCfg.Backcolor.Green = 0;
    pLayerCfg.Backcolor.Red = 255;
    if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
    {
        // Error_Handler();
    }
}
#endif
