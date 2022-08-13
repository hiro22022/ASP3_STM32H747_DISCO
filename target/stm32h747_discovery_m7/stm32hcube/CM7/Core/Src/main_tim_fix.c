/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"
#include "string.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#if 1
#define TIM_CLK  TIM5
#define TIM_CLK_IRQNO  TIM5_IRQn
#define TIM_CLK_IRQHandler  TIM5_IRQHandler
#else
#define TIM_CLK  TIM1
#define TIM_CLK_IRQNO  TIM1_UP_IRQn
#define TIM_CLK_IRQHandler  TIM1_UP_IRQHandler
#endif

#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim_clk;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/*---------------------------------------------*/
#include "stm32h747xx.h"
#include "stm32h7xx_hal_gpio.h"

/* LED 番号 LED1～LED4 */
typedef enum  {
    LED1 = 0, LED2, LED3, LED4
} LED_Index;

/* LED 構成構造体 */
typedef struct {
    GPIO_TypeDef  *gpio;
    uint32_t      Pin;
} LED_conf;

/* LED1～LED4 の構成 */
const LED_conf led_conf[] =
{
    { GPIOI, GPIO_PIN_12 },      /* LED1 */
    { GPIOI, GPIO_PIN_13 },      /* LED2 */
    { GPIOI, GPIO_PIN_14 },      /* LED3 */
    { GPIOI, GPIO_PIN_15 },      /* LED4 */
};

/* LED の初期化 */
void led_init()
{
    uint32_t temp;
    int  i;

    /* RCC (クロック) の設定 */
    RCC_TypeDef  *rcc = RCC;
    temp = rcc->AHB4ENR;
    temp |= RCC_AHB4ENR_GPIOIEN;
    rcc->AHB4ENR = temp;

    /* GPIO コントロールレジスタの設定 */
    GPIO_InitTypeDef gpio_init;
    gpio_init.Mode      = GPIO_MODE_OUTPUT_OD;
    gpio_init.Pull      = GPIO_NOPULL;
    gpio_init.Speed     = GPIO_SPEED_FREQ_HIGH;
    gpio_init.Alternate = 0x0;
    for( i = LED1; i <= LED4; i++ ){
        gpio_init.Pin   = led_conf[ i ].Pin;
        HAL_GPIO_Init( led_conf[ i ].gpio, &gpio_init );
    }
}

void led_on( uint32_t no )
{
    if( no <= LED4 )
        HAL_GPIO_WritePin( led_conf[no].gpio, led_conf[no].Pin, GPIO_PIN_RESET );
}

void led_off( uint32_t no )
{
    if( no <= LED4 )
        HAL_GPIO_WritePin( led_conf[no].gpio, led_conf[no].Pin, GPIO_PIN_SET );
}

void led_set( int val )
{
#if 0   /* これを切り替えてみると IO ポートアクセスの遅さがわかる */
    if( val & (1 << LED1) )
      led_on( LED1 );
    else
      led_off( LED1 );
    if( val & (1 << LED2) )
      led_on( LED2 );
    else
      led_off( LED2 );
    if( val & (1 << LED3) )
      led_on( LED3 );
    else
      led_off( LED3 );
    if( val & (1 << LED4) )
      led_on( LED4 );
    else
      led_off( LED4 );
#else
    /* LED が同じ GPIO で並んでいることを利用して、１回の IO アクセスでよいように効率化したバージョン */
    uint32_t rs_val = 0;
    int i;
    for( i = LED1; i <= LED4; i++ ){
      if( val & ( 1 << i ) )
        rs_val |= 1 << (i+12+16);
      else
        rs_val |= 1 << (i+12);
    }
    /* GPIO のレジスタに直接書き込む */
    led_conf[0].gpio->BSRR = rs_val;
#endif
}
/*---------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM5_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
/* USER CODE BEGIN Boot_Mode_Sequence_0 */
  int32_t timeout;
/* USER CODE END Boot_Mode_Sequence_0 */

/* USER CODE BEGIN Boot_Mode_Sequence_1 */
  /* Wait until CPU2 boots and enters in stop mode or timeout*/
  timeout = 0xFFFF;
  while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) != RESET) && (timeout-- > 0));
  if ( timeout < 0 )
  {
    Error_Handler();
  }

#if 1
  // Time wait  to make a chance to halt CPU when programming by STM32CubeProgrammer
  volatile int k;
  for( k = 0; k < 200 * 10000; k++ ){}
#endif

/* USER CODE END Boot_Mode_Sequence_1 */
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();
/* USER CODE BEGIN Boot_Mode_Sequence_2 */
  /* When system initialization is finished, Cortex-M7 will release Cortex-M4 by means of
  HSEM notification */
  /*HW semaphore Clock enable*/
  __HAL_RCC_HSEM_CLK_ENABLE();
  /*Take HSEM */
  HAL_HSEM_FastTake(HSEM_ID_0);
  /*Release HSEM in order to notify the CPU2(CM4)*/
  HAL_HSEM_Release(HSEM_ID_0,0);
  /* wait until CPU2 wakes up from stop mode */
  timeout = 0xFFFF;
  while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) == RESET) && (timeout-- > 0));
  if ( timeout < 0 )
  {
    Error_Handler();
  }
/* USER CODE END Boot_Mode_Sequence_2 */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_TIM5_Init();
  /* USER CODE BEGIN 2 */
#define MSG_CM7 "hello CM7!\r\n"
  HAL_UART_Transmit(&huart1, (uint8_t*)MSG_CM7, sizeof(MSG_CM7), 0xfffffff);

  //-------------------------
  // print clock frequency calculated from register settings
  uint32_t   clk_val;
  char  buf[32];
  clk_val = HAL_RCC_GetSysClockFreq();
  snprintf( buf, sizeof(buf), "SysClockFreq=%lu\r\n", clk_val );
  HAL_UART_Transmit(&huart1, (uint8_t*)buf, strlen(buf), 0xfffffff);
  clk_val = HAL_RCC_GetHCLKFreq();
  snprintf( buf, sizeof(buf), "HClockFreq=%lu\r\n", clk_val );
  HAL_UART_Transmit(&huart1, (uint8_t*)buf, strlen(buf), 0xfffffff);
  clk_val = HAL_RCC_GetPCLK1Freq();
  snprintf( buf, sizeof(buf), "P1ClockFreq=%lu\r\n", clk_val );
  HAL_UART_Transmit(&huart1, (uint8_t*)buf, strlen(buf), 0xfffffff);
  clk_val = HAL_RCC_GetPCLK2Freq();
  snprintf( buf, sizeof(buf), "P2ClockFreq=%lu\r\n", clk_val );
  HAL_UART_Transmit(&huart1, (uint8_t*)buf, strlen(buf), 0xfffffff);
  clk_val = HAL_RCCEx_GetD1SysClockFreq();
  snprintf( buf, sizeof(buf), "D1SysCloc=%lu\r\n", clk_val );
  HAL_UART_Transmit(&huart1, (uint8_t*)buf, strlen(buf), 0xfffffff);
  clk_val = HAL_RCCEx_GetD1PCLK1Freq();
  snprintf( buf, sizeof(buf), "D1PCLK1=%lu\r\n", clk_val );
  HAL_UART_Transmit(&huart1, (uint8_t*)buf, strlen(buf), 0xfffffff);
  clk_val = HAL_RCCEx_GetD3PCLK1Freq();
  snprintf( buf, sizeof(buf), "D3PCLK1=%lu\r\n", clk_val );
  HAL_UART_Transmit(&huart1, (uint8_t*)buf, strlen(buf), 0xfffffff);
  //-------------------------

  led_init();
  int  i, j = 0;
  for( j = 0; j < 16; j++ ){
    for( i = 0; i < 100 * 1000; i++ ){
      /* 単純なループだと消される可能性があるので、値が変わらなくても毎回呼出す */
      /* 時間を延ばす役割もある */
      led_set( j );
    }
  }

#define MSG_LED1 "LED1!\r\n"
  HAL_UART_Transmit(&huart1, (uint8_t*)MSG_LED1, sizeof(MSG_LED1), 0xfffffff);

  for(j=0; j<64; ){
    if( __HAL_TIM_GET_COUNTER(&htim2) % 100000 == 0 ){
      led_set( j );
      j++;
    }
  }
#define MSG_LED2 "LED2!\r\n"
  HAL_UART_Transmit(&huart1, (uint8_t*)MSG_LED2, sizeof(MSG_LED2), 0xfffffff);

#define MSG_TIM3 "hello CM7 Enable Interrupt!\r\n"
  HAL_UART_Transmit(&huart1, (uint8_t*)MSG_TIM3, sizeof(MSG_TIM3), 0xfffffff);
  __enable_irq();
  /* TIM5 Interrupt Vector Number = TIM_CLK_IRQNO */
  NVIC_EnableIRQ( TIM_CLK_IRQNO );

#if 1
  /* USER CODE BEGIN TIM5_Init 2 */
// #define ONEPULSE
  /* カウンターをスタート */
#ifndef ONEPULSE
  if(HAL_TIM_Base_Start_IT(&htim_clk) != HAL_OK) {
#else
  if( HAL_TIM_OnePulse_Start_IT(&htim_clk, 0) != HAL_OK ){
#endif
    /* Initialization Error */
#define MSG_BASE_START_ERR "HAL_TIM_Base_Start Error\r\n"
    HAL_UART_Transmit(&huart1, (uint8_t*)MSG_BASE_START_ERR, sizeof(MSG_BASE_START_ERR), 0xfffffff);
    Error_Handler();
  }
#define MSG_HAL_TIM_INIT_DONE "HAL_TIM_Base_Start Done\r\n"
  HAL_UART_Transmit(&huart1, (uint8_t*)MSG_HAL_TIM_INIT_DONE, sizeof(MSG_HAL_TIM_INIT_DONE), 0xfffffff);
#ifdef USE_EGR
	htim_clk.Instance->EGR = TIM_EVENTSOURCE_UPDATE;
#endif // EGR
#endif

  /* USER CODE END TIM5_Init 2 */
  for(j=0; j<64; ){
    if( __HAL_TIM_GET_COUNTER(&htim_clk) % 1000000 == 0 ){
      led_set( j );
      j++;
    }
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  for (i = 0; ; i++ )
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_DIRECT_SMPS_SUPPLY);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSI);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
#if 0
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 32;
  RCC_OscInitStruct.PLL.PLLN = 129;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_1;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_USART1
                              |RCC_PERIPHCLK_UART8|RCC_PERIPHCLK_SPDIFRX
                              |RCC_PERIPHCLK_SPI5|RCC_PERIPHCLK_SPI2
                              |RCC_PERIPHCLK_SAI1|RCC_PERIPHCLK_SDMMC
                              |RCC_PERIPHCLK_ADC|RCC_PERIPHCLK_CEC
                              |RCC_PERIPHCLK_QSPI|RCC_PERIPHCLK_FMC;
  PeriphClkInitStruct.PLL2.PLL2M = 32;
  PeriphClkInitStruct.PLL2.PLL2N = 129;
  PeriphClkInitStruct.PLL2.PLL2P = 2;
  PeriphClkInitStruct.PLL2.PLL2Q = 2;
  PeriphClkInitStruct.PLL2.PLL2R = 2;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_1;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
  PeriphClkInitStruct.FmcClockSelection = RCC_FMCCLKSOURCE_D1HCLK;
  PeriphClkInitStruct.QspiClockSelection = RCC_QSPICLKSOURCE_D1HCLK;
  PeriphClkInitStruct.SdmmcClockSelection = RCC_SDMMCCLKSOURCE_PLL;
  PeriphClkInitStruct.Sai1ClockSelection = RCC_SAI1CLKSOURCE_PLL;
  PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL;
  PeriphClkInitStruct.Spi45ClockSelection = RCC_SPI45CLKSOURCE_D2PCLK1;
  PeriphClkInitStruct.SpdifrxClockSelection = RCC_SPDIFRXCLKSOURCE_PLL;
  PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;
  PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_D2PCLK2;
  PeriphClkInitStruct.CecClockSelection = RCC_CECCLKSOURCE_LSI;
  PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSI, RCC_MCODIV_1);
#else
  /* Clock Security System Enable */
  HAL_RCC_EnableCSS();

  /*
   * HSE を有効にする
   * PLL 発振周波数を 320MHz とする HSE を 5分周、VCO を 128分周
   * sysclk を PLL とする (320MHz)
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;  // RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;     /* HSE divider 25MHz/5 => 5MHz */
  RCC_OscInitStruct.PLL.PLLN = 128;   /* VCO divider 640MHz/128 => 5MHz*/
  RCC_OscInitStruct.PLL.PLLP = 2;     /* P: 640MHz/2 => 320MHz (System Clock Source) */
  RCC_OscInitStruct.PLL.PLLQ = 8;     /* Q: 640MHz/8 => 80MHz */
  RCC_OscInitStruct.PLL.PLLR = 4;     /* R: 640MHz/4 => 160MHz */
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;  /* 4-8MHz */  // RCC_PLL1VCIRANGE_1; /* 2-4MHz */
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE; 
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;       /* System Clock : PLL */
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;   // 320MHz  /* set D1CPRE which affects Cortex M7 Clock */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV4;     // 80MHz   /* set HPRE which afects Cortex M4 clock */
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;    // 40MHz
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;               /* APB1, Timer TIMX clock */
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;               /* APB2, Timer TIMY clock */
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;	              /* */

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_USART1
                              |RCC_PERIPHCLK_UART8|RCC_PERIPHCLK_SPDIFRX
                              |RCC_PERIPHCLK_SPI5|RCC_PERIPHCLK_SPI2
                              |RCC_PERIPHCLK_SAI1|RCC_PERIPHCLK_SDMMC
                              |RCC_PERIPHCLK_ADC|RCC_PERIPHCLK_CEC
                              |RCC_PERIPHCLK_QSPI|RCC_PERIPHCLK_FMC;
  PeriphClkInitStruct.PLL2.PLL2M = 12; // 32;  // 2.08MHz
  PeriphClkInitStruct.PLL2.PLL2N = 129;
  PeriphClkInitStruct.PLL2.PLL2P = 2;
  PeriphClkInitStruct.PLL2.PLL2Q = 2;
  PeriphClkInitStruct.PLL2.PLL2R = 2;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_1;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
  PeriphClkInitStruct.FmcClockSelection = RCC_FMCCLKSOURCE_D1HCLK;
  PeriphClkInitStruct.QspiClockSelection = RCC_QSPICLKSOURCE_D1HCLK;
  PeriphClkInitStruct.SdmmcClockSelection = RCC_SDMMCCLKSOURCE_PLL;
  PeriphClkInitStruct.Sai1ClockSelection = RCC_SAI1CLKSOURCE_PLL;
  PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL;
  PeriphClkInitStruct.Spi45ClockSelection = RCC_SPI45CLKSOURCE_D2PCLK1;
  PeriphClkInitStruct.SpdifrxClockSelection = RCC_SPDIFRXCLKSOURCE_PLL;
  PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;
  PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_D2PCLK2;
  PeriphClkInitStruct.CecClockSelection = RCC_CECCLKSOURCE_LSI;
  PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSI, RCC_MCODIV_1);
#endif /* 0 */
}

#define TIMX_CLOCK_HZ (40 * 1000 * 1000 * 2)   // APB1 クロック(40MHz) の 2倍
        // APB1CLKDivider を分周した場合は、2倍or4倍になるが、分周しない(DIV1)場合はAPB1と同じクロック

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */
#if 0
	__HAL_RCC_TIM2_CLK_ENABLE();
#endif

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
#if 0
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4294967295;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
#else
//	htim2.Init.Period = 0xFFFFFFFF;
	htim2.Init.Period = 0xFFFF;                       // 65,535 μsec
	htim2.Init.Prescaler = (TIMX_CLOCK_HZ/1000000);    /* 1μsec / count */
	htim2.Init.ClockDivision = 0;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;  /* STM32H747 added */
#endif
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }

#if 1
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
#else
  (void)sClockSourceConfig;
  (void)sMasterConfig;
#endif

#if 1
  /* USER CODE BEGIN TIM2_Init 2 */
  /* カウンターをスタート */
  if(HAL_TIM_Base_Start(&htim2) != HAL_OK) {
    /* Initialization Error */
#define MSG_BASE_START_ERR "HAL_TIM_Base_Start Error\r\n"
    HAL_UART_Transmit(&huart1, (uint8_t*)MSG_BASE_START_ERR, sizeof(MSG_BASE_START_ERR), 0xfffffff);
    Error_Handler();
  }
#define MSG_HAL_TIM_INIT_DONE "HAL_TIM_Base_Start Done\r\n"
  HAL_UART_Transmit(&huart1, (uint8_t*)MSG_HAL_TIM_INIT_DONE, sizeof(MSG_HAL_TIM_INIT_DONE), 0xfffffff);
#endif
  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
#if 0
static void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim_clk.Instance = TIM5;
  htim_clk.Init.Prescaler = 0;
  htim_clk.Init.CounterMode = TIM_COUNTERMODE_UP;
#if 0
  htim_clk.Init.Period = 4294967295;
#else
  htim_clk.Init.Period = 100 * 1000;
#endif
  htim_clk.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim_clk.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim_clk) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim_clk, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OnePulse_Init(&htim_clk, TIM_OPMODE_SINGLE) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim_clk, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */

  /* USER CODE END TIM5_Init 2 */

}
#else
static void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM5_Init 1 */
#if 0
	__HAL_RCC_TIM5_CLK_ENABLE();
#endif

  /* USER CODE END TIM5_Init 1 */
  htim_clk.Instance = TIM_CLK;
#if 0
  htim_clk.Init.Prescaler = 0;
  htim_clk.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim_clk.Init.Period = 4294967295;
  htim_clk.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim_clk.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
#else
	htim_clk.Init.Period = 1000;                          // 1,000 μsec
	htim_clk.Init.Prescaler = (TIMX_CLOCK_HZ/1000000);     // 1μsec/count
	htim_clk.Init.ClockDivision = 0;
	htim_clk.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim_clk.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;  /* STM32H747 added */
#endif

#ifndef ONEPULSE
  if (HAL_TIM_Base_Init(&htim_clk) != HAL_OK)
#else
  if (HAL_TIM_OnePulse_Init( &htim_clk, TIM_OPMODE_REPETITIVE) != HAL_OK)
#endif
  {
    Error_Handler();
  }

#if 1
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim_clk, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim_clk, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
#else
  (void)sClockSourceConfig;
  (void)sMasterConfig;
#endif
}

#define COUNT_BASE 1000
uint32_t  tim_clk_count;
void TIM_CLK_IRQHandler()
{
  __HAL_TIM_CLEAR_FLAG(&htim_clk, TIM_SR_UIF);
  tim_clk_count++;
//  led_set( tim_clk_count / COUNT_BASE );
  if( tim_clk_count % 1000 == 0 )
    led_set( tim_clk_count / 1000 );

  // 動的にタイマ値を変更するテスト
#if 0
  if(tim_clk_count%2 == 0)
    __HAL_TIM_SET_AUTORELOAD(&htim_clk, 0xffff);
  else
    __HAL_TIM_SET_AUTORELOAD(&htim_clk, 0xffff/4);
#endif

#ifdef ONEPULSE
  HAL_TIM_OnePulse_Start_IT(&htim_clk, 0);
#endif

#ifdef USE_EGR
 	htim_clk.Instance->EGR = TIM_EVENTSOURCE_UPDATE;
#endif
}
#endif

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /*Configure GPIO pin : CEC_CK_MCO1_Pin */
  GPIO_InitStruct.Pin = CEC_CK_MCO1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
  HAL_GPIO_Init(CEC_CK_MCO1_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/