/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32c0xx_ll_gpio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define INPUT_SOURCE    2    // 1: B1 버튼(PC13), 2: 점퍼선(PA0, A0)
#define DEBOUNCE_METHOD 2    // 0: 거르지 않음, 1: 기다리기(HAL_Delay), 2: 시계 보기(HAL_GetTick)
#define DEBOUNCE_MS     20   // 떨림이 멈출 때까지 기다릴 시간(ms)
#define DRIVER_METHOD   2    // 1: HAL, 2: LL, 3: 레지스터 직접

#if INPUT_SOURCE == 1
#define INPUT_PORT  B1_GPIO_Port
#define INPUT_PIN   B1_Pin
#else
#define INPUT_PORT  TEST_IN_GPIO_Port
#define INPUT_PIN   TEST_IN_Pin
#endif
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
volatile uint32_t press_count = 0;   // "눌렸다"고 읽힌 횟수
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static GPIO_PinState Read_Input(void) {
#if DRIVER_METHOD == 1
	return HAL_GPIO_ReadPin(INPUT_PORT, INPUT_PIN);
#elif DRIVER_METHOD == 2
  return LL_GPIO_IsInputPinSet(INPUT_PORT, INPUT_PIN) ? GPIO_PIN_SET : GPIO_PIN_RESET;
#else
	return (INPUT_PORT->IDR & INPUT_PIN) ? GPIO_PIN_SET : GPIO_PIN_RESET; // IDR에서 그 핀 칸만 보기
#endif
}

static void Toggle_LED(void) {
#if DRIVER_METHOD == 1
	HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
#elif DRIVER_METHOD == 2
  LL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
#else
	uint32_t odr = LD4_GPIO_Port->ODR;                           // 지금 LED 상태 보기
	LD4_GPIO_Port->BSRR = ((odr & LD4_Pin) << 16) | (~odr & LD4_Pin); // 켜져 있으면 끄고, 꺼져 있으면 켜기
#endif
}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	/* USER CODE BEGIN 2 */
	GPIO_PinState prev_state = Read_Input();   // "아까 값"을 담는 상자
#if DEBOUNCE_METHOD == 2
	GPIO_PinState stable_state = prev_state;      // 떨림이 멈춘 뒤 "인정한 값"
	uint32_t last_change_tick = HAL_GetTick();    // 마지막으로 값이 바뀐 시각(ms)
#endif
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
		GPIO_PinState now_state = Read_Input();     // "지금 값"

#if DEBOUNCE_METHOD == 0
		/* 거르지 않음: 1 → 0 이면 바로 인정 */
		if (prev_state == GPIO_PIN_SET && now_state == GPIO_PIN_RESET) {
		  press_count++;
		  Toggle_LED();
		}

		#elif DEBOUNCE_METHOD == 1
		/* 기다리기: 1 → 0 을 보면 잠깐 기다렸다가 한 번 더 확인 */
		if (prev_state == GPIO_PIN_SET && now_state == GPIO_PIN_RESET) {
			HAL_Delay(DEBOUNCE_MS);                  // 떨림이 멈출 때까지 기다리기
			if (Read_Input() == GPIO_PIN_RESET) {    // 그래도 0이면 진짜 눌림
				press_count++;
				Toggle_LED();
			}
		}
		#elif DEBOUNCE_METHOD == 2
		/* 시계 보기: 값이 DEBOUNCE_MS 동안 그대로면 인정 (기다리지 않음) */
		if (now_state != prev_state) {                 // 값이 바뀜 (떨리는 중일 수도)
			last_change_tick = HAL_GetTick();            // 시계를 처음부터 다시
		}

		if ((HAL_GetTick() - last_change_tick) >= DEBOUNCE_MS   // 20ms 동안 조용했고
		&& now_state != stable_state) {                      // 인정한 값과 다르면
			stable_state = now_state;                   // 새 값으로 인정
			if (stable_state == GPIO_PIN_RESET) {       // 새로 인정한 값이 0 = 진짜 눌림
				press_count++;
				Toggle_LED();
			}
		}
#endif

		prev_state = now_state;   // 지금 값을 "아까 값" 상자에 옮겨 두기
		/* USER CODE END 3 */
	}
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	__HAL_FLASH_SET_LATENCY(FLASH_LATENCY_0);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV4;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	/* USER CODE BEGIN MX_GPIO_Init_1 */

	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : B1_Pin */
	GPIO_InitStruct.Pin = B1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : TEST_IN_Pin */
	GPIO_InitStruct.Pin = TEST_IN_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(TEST_IN_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : LD4_Pin */
	GPIO_InitStruct.Pin = LD4_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LD4_GPIO_Port, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */

	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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
