/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ST7735/st7735.h"
#include <stdlib.h>
#include <string.h>
#include <time.h> //para o rand()
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LIGA_LEDS HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3 + GPIO_PIN_4 + GPIO_PIN_5 + GPIO_PIN_6, 1)
#define DESLIGA_LEDS HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3 + GPIO_PIN_4 + GPIO_PIN_5 + GPIO_PIN_6, 0)
#define LE_BOTAO_CIMA HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12)
#define LE_BOTAO_DIREITO HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)
#define LE_BOTAO_BAIXO HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)
#define LE_BOTAO_ESQUERDO HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
int bomba_bandeira = 0;
int a1 = 2;
int contBomba = 0;
char str[12]; //usado na conversao de int para string
char strA[12];
char tabuleiro[6][4];
int  tabu_bomb[6][4];
int x = 103;
int y = 20;
int xa = 5;
int ya = 80;
int x_pixel = 10;
int y_pixel = 10;
int c = 0;
int l = 0;
int x_pixel1 = 0;
int y_pixel1 = 0;
int confirmar = 0;
int casas_abertas = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
void Start(void);
void Error(void);
void Square(void);
void Navegacao(void);
void Bomb(void);
void VerificaCasa(void);
void Bandeira(int x_pixel1, int y_pixel1);
void Perdeu(void);
void Ganhou(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
	MX_SPI1_Init();
	/* USER CODE BEGIN 2 */
	ST7735_Init();
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */


	//Square();

	while (1) {
		a1 = 2;

		Start();
		Navegacao();

		//Matriz();
		//Bomb();
		//ST7735_FillRectangle(60, 40, 10, 10, WHITE);
		//Navegacao();

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief SPI1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI1_Init(void) {

	/* USER CODE BEGIN SPI1_Init 0 */

	/* USER CODE END SPI1_Init 0 */

	/* USER CODE BEGIN SPI1_Init 1 */

	/* USER CODE END SPI1_Init 1 */
	/* SPI1 parameter configuration*/
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_1LINE;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN SPI1_Init 2 */

	/* USER CODE END SPI1_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB,
			ST7735_DC_Pin | ST7735_RES_Pin | GPIO_PIN_3 | GPIO_PIN_4
					| GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_RESET);

	/*Configure GPIO pin : ST7735_CS_Pin */
	GPIO_InitStruct.Pin = ST7735_CS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(ST7735_CS_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : ST7735_DC_Pin ST7735_RES_Pin PB3 PB4
	 PB5 PB6 */
	GPIO_InitStruct.Pin = ST7735_DC_Pin | ST7735_RES_Pin | GPIO_PIN_3
			| GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pins : PA9 PA10 PA11 PA12 */
	GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/*void Conversao(void){

 char s[] = "12345";

 int x = atoi(s);
 //itoa conversao de int para impressao da string
 }*/

/*void Conversao(void){

 char s[] = "12345";

 int x = atoi(s);
 //itoa conversao de int para impressao da string
 }*/


void Start(void) {

	ST7735_FillScreen(BLACK);
	while(a1 == 2){
	/*bomba eh uma variavel que salva a ultima alteracao, podendo ser de if ou else if*/

	ST7735_WriteString(40, 15, "MENU ESCOLHA", Font_7x10, WHITE, BLACK);
	ST7735_WriteString(4, 30, "quant de bombas: ", Font_7x10, WHITE, BLACK);
	ST7735_WriteString(4, 45, "Recomenda-se: 5", Font_7x10, WHITE, BLACK);
	ST7735_WriteString(4, 60, "quant. escolhida: ", Font_7x10, WHITE, BLACK);

	if (LE_BOTAO_CIMA == 0) {

		contBomba++;
		bomba_bandeira = contBomba;
	}

	else if (LE_BOTAO_BAIXO == 0) {

		if(contBomba >= 1){
		contBomba--;
		bomba_bandeira = contBomba;

		}
		else{

			contBomba = 0;
		}

	}



	// Converter int para string usando a função sprintf
	sprintf(str, "%d", bomba_bandeira);
	// Agora 'str' contém a representação do número como string

	ST7735_WriteString(130, 60, str, Font_7x10, WHITE, BLACK);

	 if (LE_BOTAO_DIREITO == 0) {//confirma escolha

		ST7735_FillScreen(BLACK);
		if (bomba_bandeira >= 1) {

			x = 103;
			y = 20;
			xa = 5;
			ya = 80;
			Square();
			a1 = 0;
		}
		else {
			Error();
		}
	}
	}
}
void Matriz(void){

   char tabuleiro[6][4];
  int cont = 0;
  int escolha = 1;

  	/*int npralinha = rand()%10;
  	int npracoluna = rand()%10;

  	printf(".%i.",npracoluna);
  	//printf("\n");
  	printf(".%i.",npralinha);
  	//printf("\n");
  */

  	for (int p = 0; p < 6; p++)
  	{
      	for (int i = 0; i < 4; i++)
		{
			if (cont < escolha)
			{

					tabuleiro[p][i] = '1';
					cont = cont + 1;
					printf("%i new cont: ", cont);
		    }
		        else
				{
	 				tabuleiro[p][i] = '0';
	 			}
		}
  	}

    /*printf("\n");
    for (int p = 0; p < 6; p++)
  	{
      	for (int i = 0; i < 4; i++)
		{
		    printf("(%c)",tabuleiro[p][i]);
		    //printf("\n");
		}
  	}*/


}


void Bomb(void){

	tabu_bomb[6][4];

	//inicializa o gerador de numeros aleatorios
	srand(time(NULL));

	//preenche a matriz com valores aleatorios entre 0 e 1
	for(int x = 0; x < 6; x++){
		for(int y = 0; y < 4; y++){
			tabu_bomb[x][y] = rand() % 2; // gera numeros aleatorios em posicoes aleatorias 0 e 1
		}
	}
}

void Error(void) {

	ST7735_WriteString(4, 45, "BOMBA DEVE SER < 0", Font_7x10, RED, BLACK);

	HAL_Delay(3000);
	Start();
}
void Perdeu(void) {

	ST7735_FillScreen(BLACK);
	ST7735_WriteString(4, 45, "Perdeu", Font_7x10, RED, BLACK);

	HAL_Delay(3000);
	a1 =2;

}
void Ganhou(void) {

/*	ST7735_FillScreen(BLACK);
	ST7735_WriteString(4, 45, "Ganhou", Font_7x10, RED, BLACK);

	HAL_Delay(3000);
	a1 =2;*/

}


void Square(void)
{
	for (int i = 0; i < 4;i++)//LINHAS HORIZONTAIS
		{
			ST7735_DrawLine(6, y, x, y, BLUE);
			y +=20;
		}
	for (int i = 0; i < 6;i++)// LINHAS VERTICAIS
	{
		ST7735_DrawLine(xa, 0, xa, ya+20, YELLOW);
		xa +=20;
	}
	  Bomb();
}

void Navegacao(void)
{
	  int x_pixel1 = x_pixel;
	  int y_pixel1 = y_pixel;

	  c = 0;
	  l = 0;



	  while (confirmar == 0)
  {
		  if (LE_BOTAO_CIMA == 0)
		  {
		  	  	if (tabu_bomb[c][l] == 1)
		  	  	{
		  	  		ST7735_FillRectangle(x_pixel1 -3, y_pixel1-5, 16, 15, RED);
		  	  		HAL_Delay(700);
		  	  		confirmar = 1;
		  	  	}
		  	  	else
		  	  	{
		  	  		ST7735_FillRectangle(x_pixel1 -3, y_pixel1-5, 16, 15, YELLOW);
		  	  		casas_abertas +=1;
		  	  		casas_abertas++;
		  	  	}
		  }
		  ST7735_FillRectangle(x_pixel1 -3, y_pixel1-5, 7, 7, WHITE);

	if (LE_BOTAO_DIREITO == 0)
		{
			if (/*c < 4 && l < 5 && */x_pixel1 < 90 && y_pixel1 < 80)
			{
				  ST7735_FillRectangle(x_pixel1 -3, y_pixel1-5, 7, 7, BLACK);//ANDAR PRA FRENTE

				x_pixel1 +=20;
				c +=1;
				HAL_Delay(500);//SEM O DELAY O PIXEL PERCORRE POR TODA AS CASAS FRENETICO

			}
			else if (y_pixel1 >= 70 )//VOLTAR PRO INICIO TOTAL
			{
				  ST7735_FillRectangle(x_pixel1 -3, y_pixel1-5, 7, 7, BLACK);
				c = 0;
				l = 0;
				x_pixel1 = x_pixel;
				y_pixel1 = y_pixel;
				HAL_Delay(500);
			}

			else if (x_pixel1 >= 81)// IR PRO INICIO DA PROXIMA LINHA
			{
				  ST7735_FillRectangle(x_pixel1 -3, y_pixel1-5, 7, 7, BLACK);
				x_pixel1 = x_pixel;
				y_pixel1 += 20;
				l += 1;
				c = 0;
				HAL_Delay(500);
			}
		}

		if(LE_BOTAO_BAIXO == 0){
			Bandeira(x_pixel1, y_pixel1);
		}
		int max_casas = 20;
		int ganhar = max_casas - bomba_bandeira;
		if (casas_abertas == ganhar)
		{
			Ganhou();
		}
	}
	  confirmar = 0;
	  Perdeu();


}

void Bandeira(int x_pixel1, int y_pixel1){
	/*int w_retangle = x_pixel1 + 6;
	int h_retangle = y_pixel1 + 6;*/	//colocar um desenho para imprimir para ele ficar na função
	/*    O jogador pode marcar casas como "possível bomba" usando uma
	bandeirinha. É uum palpite, e ele pode estar certo ou não. Para cada bandeirinha marcada, o contador
	de bombas na tela diminui.        */

		/* no p10 caso o jogador aperte será colorido de amarelo a casa que ele confirmou
		 * sendo assim, diminuira a quantidade de bombas*/
			//if()//se bandeira for menor que 1 nn funciona mais
			if(bomba_bandeira >= 1){

				/*para que as variaveis de x e y acompanhem o cursor p/ serem impressas será necessario colocar
				 * um ponteiro em cada para apontarem para o endereço xpixel e ypixel?*/
				ST7735_FillRectangle(x_pixel1 -5, y_pixel1-5, 16, 15, BLUE);
				bomba_bandeira = bomba_bandeira - 1;
				HAL_Delay(500);
				sprintf(strA, "%d", bomba_bandeira);
				ST7735_WriteString(130, 60, strA, Font_7x10, WHITE, BLACK);

			}

}
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
