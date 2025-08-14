/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include <stdint.h>
#include "stm32f0xx.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define MAX_ITER 100
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
//TODO: Define and initialise the global varibales required
/*
  start_time
  end_time
  execution_time 
  checksum: should be uint64_t
  initial width and height maybe or you might opt for an array??
*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
uint64_t calculate_mandelbrot_fixed_point_arithmetic(int width, int height, int max_iterations);
uint64_t calculate_mandelbrot_double(int width, int height, int max_iterations);


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static const int image_dimensions[] = {128,160,192,224,256};
volatile uint64_t globalCheckSum = 0;
volatile uint32_t globalStartTime = 0;
volatile uint32_t globalEndTime = 0;
volatile uint32_t executionTime = 0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
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
  //TODO: Turn on LED 0 to signify the start of the operation
  

  //TODO: Record the start time
  
  
  //TODO: Call the Mandelbrot Function and store the output in the checksum variable defined initially
  

  //TODO: Record the end time
  

  //TODO: Calculate the execution time
  

  //TODO: Turn on LED 1 to signify the end of the operation
  

  //TODO: Hold the LEDs on for a 1s delay
  

  //TODO: Turn off the LEDs


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  for(int i = 0; i < (sizeof(image_dimensions)/sizeof(image_dimensions[0])); i++){
	  	  int dim = image_dimensions[i];


	  	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
	  	  globalStartTime = HAL_GetTick();
	  	  globalCheckSum = calculate_mandelbrot_fixed_point_arithmetic(image_dimensions[i], image_dimensions[i],MAX_ITER);
	  	  globalEndTime = HAL_GetTick();
	  	  executionTime = globalEndTime - globalStartTime;
	  	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
	  	  HAL_Delay(1000);
	  	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1, GPIO_PIN_RESET);



	  	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET); // Turn on LED 1 for double test
		  globalStartTime = HAL_GetTick();
		  globalCheckSum = calculate_mandelbrot_double(dim, dim, MAX_ITER);
		  globalEndTime = HAL_GetTick();
		  executionTime = globalEndTime - globalStartTime;
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET); // Turn off LED 1
		  HAL_Delay(1000); // Pause for 1s

	    }
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB0 PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
//TODO: Mandelbroat using variable type integers and fixed point arithmetic
uint64_t calculate_mandelbrot_fixed_point_arithmetic(int width, int height, int max_iterations){
	uint64_t sum = 0;

	    int FRACT = 29;                                // number of fractional bits
	    long long scale_factor = (1LL << FRACT);       // fixed-point scaling factor
	    long long FOUR = (4LL << FRACT);               // 4.0 in fixed-point

	    // ranges in fixed-point
	    long long x_min   = -((5LL * scale_factor) >> 1);   // -2.5
	    long long x_range = (7LL * scale_factor) >> 1;      // 3.5
	    long long y_min   = -(1LL * scale_factor);          // -1.0
	    long long y_range =  (2LL * scale_factor);          // 2.0

	    // step sizes (still one division here, but only once per dimension, not per pixel)
	    long long step_x = x_range / width;
	    long long step_y = y_range / height;

	    for (int y = 0; y < height; y++) {
	        long long y0 = y_min + (long long)y * step_y;

	        long long x0 = x_min;
	        for (int x = 0; x < width; x++) {
	            long long xi = 0, yi = 0;
	            long long xi2 = 0, yi2 = 0;
	            int iter = 0;

	            while (iter < max_iterations && (xi2 + yi2) <= FOUR) {
	                long long temp = ((xi * xi) >> FRACT) - ((yi * yi) >> FRACT) + x0;
	                yi = ((2LL * xi * yi) >> FRACT) + y0;
	                xi = temp;

	                xi2 = (xi * xi) >> FRACT;
	                yi2 = (yi * yi) >> FRACT;

	                iter++;
	            }

	            sum += (uint64_t)iter;
	            x0 += step_x;
	        }
	    }

	    return sum;
}

//TODO: Mandelbroat using variable type double
uint64_t calculate_mandelbrot_double(int width, int height, int max_iterations){
	uint64_t sum = 0;

	    double x_min   = -2.5;
	    double x_range =  3.5;
	    double y_min   = -1.0;
	    double y_range =  2.0;

	    // step sizes (computed once per dimension)
	    double step_x = x_range / (double)width;
	    double step_y = y_range / (double)height;

	    for (int y = 0; y < height; y++) {
	        double y0 = y_min + (double)y * step_y;

	        double x0 = x_min;
	        for (int x = 0; x < width; x++) {
	            double xi = 0.0, yi = 0.0;
	            int iter = 0;

	            while (iter < max_iterations && (xi*xi + yi*yi) <= 4.0) {
	                double temp = (xi * xi) - (yi * yi) + x0;
	                yi = (2.0 * xi * yi) + y0;
	                xi = temp;
	                iter++;
	            }

	            sum += (uint64_t)iter;
	            x0 += step_x;
	        }
	    }

	    return sum;
}

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
