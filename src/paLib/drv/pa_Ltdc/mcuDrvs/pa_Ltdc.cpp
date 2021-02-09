#include <paLib/drv/pa_Ltdc/pa_Ltdc.hpp>

#if drv_ltdc
extern LTDC_HandleTypeDef hltdc;
char Ltdc_buff[3000];

void Ltdc_init(RgbConfig rgbConfig)
{
    /* USER CODE BEGIN LTDC_Init 0 */
    extern char Ltdc_buff[];
    /* USER CODE END LTDC_Init 0 */
    for (int i = 0; i < 3000; i++)
    {
        Ltdc_buff[i] = i % 255;
    }
    LTDC_LayerCfgTypeDef pLayerCfg = {0};
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
    pLayerCfg.WindowX0 = 50;
    pLayerCfg.WindowX1 = 100;
    pLayerCfg.WindowY0 = 50;
    pLayerCfg.WindowY1 = 100;
    pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
    pLayerCfg.Alpha = 255;
    pLayerCfg.Alpha0 = 0;
    pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
    pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
    pLayerCfg.FBStartAdress = (uint32_t)Ltdc_buff;
    pLayerCfg.ImageWidth = 50;
    pLayerCfg.ImageHeight = 50;
    pLayerCfg.Backcolor.Blue = 0;
    pLayerCfg.Backcolor.Green = 0;
    pLayerCfg.Backcolor.Red = 255;
    if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
    {
        // Error_Handler();
    }
    // pLayerCfg1.WindowX0 = 0;
    // pLayerCfg1.WindowX1 = 10;
    // pLayerCfg1.WindowY0 = 0;
    // pLayerCfg1.WindowY1 = 10;
    // pLayerCfg1.Alpha = 0;
    // pLayerCfg1.Alpha0 = 0;
    // pLayerCfg1.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
    // pLayerCfg1.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
    // pLayerCfg1.FBStartAdress = 0x20000100;
    // pLayerCfg1.ImageWidth = 10;
    // pLayerCfg1.ImageHeight = 10;
    // pLayerCfg1.Backcolor.Blue = 255;
    // pLayerCfg1.Backcolor.Green = 0;
    // pLayerCfg1.Backcolor.Red = 0;
    // if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg1, 1) != HAL_OK)
    // {
    //     // Error_Handler();
    // }
    // LTDC_LayerCfgTypeDef pLayerCfg = {0};

    // hltdc.Instance = LTDC;
    // hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
    // hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
    // hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
    // hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
    // hltdc.Init.HorizontalSync = 0;
    // hltdc.Init.VerticalSync = 5;
    // hltdc.Init.AccumulatedHBP = 20;
    // hltdc.Init.AccumulatedVBP = 20;
    // hltdc.Init.AccumulatedActiveW = 500;
    // hltdc.Init.AccumulatedActiveH = 770;
    // hltdc.Init.TotalWidth = 502;
    // hltdc.Init.TotalHeigh = 772;
    // hltdc.Init.Backcolor.Blue = 255;
    // hltdc.Init.Backcolor.Green = 255;
    // hltdc.Init.Backcolor.Red = 0;
    // if (HAL_LTDC_Init(&hltdc) != HAL_OK)
    // {
    //     while (1)
    //         ;
    // }
    // pLayerCfg.WindowX0 = 0;
    // pLayerCfg.WindowX1 = 40;
    // pLayerCfg.WindowY0 = 0;
    // pLayerCfg.WindowY1 = 40;
    // pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB888;
    // pLayerCfg.Alpha = 255;
    // pLayerCfg.Alpha0 = 127;
    // pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
    // pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
    // pLayerCfg.FBStartAdress = (uint32_t)Ltdc_buff;
    // pLayerCfg.ImageWidth = 20;
    // pLayerCfg.ImageHeight = 20;
    // pLayerCfg.Backcolor.Blue = 255;
    // pLayerCfg.Backcolor.Green = 0;
    // pLayerCfg.Backcolor.Red = 0;
    // if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
    // {
    //     while (1)
    //         ;
    // }
    /* USER CODE BEGIN LTDC_Init 0 */

    /* USER CODE END LTDC_Init 0 */

    // LTDC_LayerCfgTypeDef pLayerCfg = {0};
    // LTDC_LayerCfgTypeDef pLayerCfg1 = {0};

    // /* USER CODE BEGIN LTDC_Init 1 */

    // /* USER CODE END LTDC_Init 1 */
    // hltdc.Instance = LTDC;
    // hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
    // hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
    // hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
    // hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
    // hltdc.Init.HorizontalSync = rgbConfig.HSW - 1;
    // hltdc.Init.VerticalSync = rgbConfig.VSW - 1;
    // hltdc.Init.AccumulatedHBP = rgbConfig.HSW + rgbConfig.HBP - 1;
    // hltdc.Init.AccumulatedVBP = rgbConfig.VSW + rgbConfig.VBP - 1;
    // hltdc.Init.AccumulatedActiveW = rgbConfig.HSW + rgbConfig.HBP + 480 - 1;
    // hltdc.Init.AccumulatedActiveH = rgbConfig.VSW + rgbConfig.VBP + 480 - 1;
    // hltdc.Init.TotalWidth = hltdc.Init.AccumulatedActiveW + rgbConfig.HFP;
    // hltdc.Init.TotalHeigh = hltdc.Init.AccumulatedActiveH + rgbConfig.VFP;
    // hltdc.Init.Backcolor.Blue = 0;
    // hltdc.Init.Backcolor.Green = 0;
    // hltdc.Init.Backcolor.Red = 255;
    // if (HAL_LTDC_Init(&hltdc) != HAL_OK)
    // {
    //     // Error_Handler();
    // }
    // pLayerCfg.WindowX0 = 0;
    // pLayerCfg.WindowX1 = 5;
    // pLayerCfg.WindowY0 = 0;
    // pLayerCfg.WindowY1 = 5;
    // pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
    // pLayerCfg.Alpha = 0;
    // pLayerCfg.Alpha0 = 0;
    // pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
    // pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
    // pLayerCfg.FBStartAdress = (uint32_t)Ltdc_buff;
    // pLayerCfg.ImageWidth = 0;
    // pLayerCfg.ImageHeight = 0;
    // pLayerCfg.Backcolor.Blue = 255;
    // pLayerCfg.Backcolor.Green = 0;
    // pLayerCfg.Backcolor.Red = 0;
    // if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
    // {
    //     // Error_Handler();
    // }
    // pLayerCfg1.WindowX0 = 0;
    // pLayerCfg1.WindowX1 = 5;
    // pLayerCfg1.WindowY0 = 0;
    // pLayerCfg1.WindowY1 = 5;
    // pLayerCfg1.Alpha = 0;
    // pLayerCfg1.Alpha0 = 0;
    // pLayerCfg1.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
    // pLayerCfg1.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
    // pLayerCfg1.FBStartAdress = (uint32_t)Ltdc_buff;
    // pLayerCfg1.ImageWidth = 0;
    // pLayerCfg1.ImageHeight = 0;
    // pLayerCfg1.Backcolor.Blue = 0;
    // pLayerCfg1.Backcolor.Green = 0;
    // pLayerCfg1.Backcolor.Red = 255;
    // if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg1, 1) != HAL_OK)
    // {
    //     // Error_Handler();
    // }
    // /* USER CODE BEGIN LTDC_Init 2 */

    /* USER CODE END LTDC_Init 2 */
}
#endif
