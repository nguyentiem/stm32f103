
#include "main.h"
#include <string.h>
#define WIDTH 128
#define HEIGHT 64
#define WIRE_MAX 32 
#define addr_oled 0x78
#define TW_START 0x08 // start 
#define  TW_REP_START  0x10    // repeat start 
#define  TW_MT_SLA_ACK 0x18   // truyen slave addr de ghi co ack   
#define  TW_MT_SLA_NACK 0x20 //  truyen slave addr de ghi  ko co ack 
#define  TW_MR_SLA_ACK 0x40   // truyen slave addr de doc co ack 
#define  TW_MT_DATA_ACK 0x28 // gui dl co ack 
#define  TW_MT_DATA_NACK 0x30  // nhan dl khong co ack
#define SSD1306_COLUMNADDR          0x21 ///< See datasheet
#define SSD1306_PAGEADDR            0x22        ///< See datasheet
#define BUFF_SIZE WIDTH*HEIGHT/8
unsigned char buffer[BUFF_SIZE]; 
I2C_HandleTypeDef hi2c1;
uint8_t logo_bmp[] =
{ 0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x1f,0xff,0xff,0xf0,
  0x00,0x00,0x3f,0xff,0xff,0xf0,
  0x00,0x00,0x3f,0xff,0xff,0xf0,
  0x00,0x00,0x3f,0xff,0xff,0xf0,
  0x00,0x00,0x3e,0x6f,0xe4,0xf0,
  0x00,0x00,0x3e,0xa7,0x20,0xf0,
  0x00,0x40,0x3e,0x0b,0x21,0xf0,
  0x01,0xf0,0x3e,0x83,0x20,0xf0,
  0x00,0xe0,0x3e,0x53,0x64,0xf0,
  0x00,0xe0,0x3f,0xff,0xff,0xf0,
  0x00,0x00,0x3f,0xff,0xff,0xf0,
  0x00,0x00,0x3f,0xff,0xff,0xf0,
  0x00,0x00,0x3f,0xff,0xef,0xf0,
  0x00,0x00,0x3f,0xfc,0xff,0xf0,
  0x00,0x00,0x3f,0xff,0x5f,0xf0,
  0x00,0x00,0x3f,0xef,0xbf,0xf0,
  0x00,0x00,0x3f,0xff,0xbf,0xf0,
  0x00,0x00,0x3f,0x73,0xef,0xf0,
  0x00,0x00,0x3d,0xdb,0xff,0xf0,
  0x00,0x00,0x3b,0x7e,0xff,0xf0,
  0x00,0x00,0x0d,0xfd,0xff,0xf0,
  0x00,0x00,0x1b,0xef,0xff,0xf0,
  0x00,0x00,0x6f,0xfb,0xff,0xf0,
  0x00,0x00,0xbf,0xdf,0xff,0xf0,
  0x00,0x00,0x3f,0xff,0xff,0xf0,
  0x00,0x00,0x3f,0xaf,0xff,0xf0,
  0x00,0x00,0x3f,0xff,0xff,0xf0,
  0x00,0x00,0x3f,0x5f,0xff,0xf0,
  0x00,0x00,0x3f,0xbf,0xff,0xf0,
  0x00,0x00,0x3e,0xff,0xff,0xf0,
  0x00,0x00,0xef,0xef,0xff,0xf0,
  0x00,0x00,0xfc,0xff,0xff,0xf0,
  0x00,0x01,0x3f,0xff,0xff,0xf0,
  0x00,0x14,0x39,0xff,0xff,0xf0,
  0x00,0x18,0x3b,0xff,0xff,0xf0,
  0x00,0x30,0x37,0xff,0xff,0xf0,
  0x00,0x10,0x37,0xff,0xff,0xf0,
  0x00,0x00,0x2f,0xff,0xff,0xf0,
  0x00,0x00,0x0f,0xff,0xff,0xf0,
  0x00,0x00,0x1f,0xff,0xff,0xf0,
  0x00,0x00,0x3f,0xff,0xff,0xf0,
  0x00,0x10,0x3f,0xff,0xff,0xf0,
  0x00,0x30,0x3f,0xff,0xff,0xf0,
  0x00,0x38,0x3f,0xff,0xff,0xf0,
  0x00,0x18,0x3f,0xff,0xff,0xf0,
  0x00,0x00,0x3f,0xff,0xff,0xf0,
  0x00,0x01,0x3f,0xff,0xff,0xf0,
  0x00,0x00,0xef,0xff,0xff,0xf0,
  0x00,0x00,0xef,0xff,0xff,0xf0,
  0x00,0x00,0x3f,0xff,0xff,0xf0,
  0x00,0x00,0x3f,0xff,0xff,0xf0,
  0x00,0x00,0x3f,0xff,0xff,0xf0,
  0x00,0x00,0x1f,0xff,0xff,0xf0,
  0x3f,0xff,0xdf,0xff,0xff,0xf0,
  0x3f,0xdf,0xff,0xff,0xff,0xf0,
  0x3f,0xdf,0xff,0xff,0xff,0xf0,
  0x30,0x88,0x13,0x02,0x04,0x70,
  0x30,0x88,0x13,0x02,0x04,0x70,
  0x30,0x89,0x03,0x10,0x04,0x70,
  0x30,0x89,0x83,0x10,0x04,0x70,
  0x30,0x00,0x13,0x02,0x00,0x30,
  0x30,0x20,0x13,0x02,0x01,0x30,
  0x3b,0xac,0xb7,0xea,0xcf,0x70,
  0x3f,0xff,0xff,0xff,0xff,0xf0,
  0x3f,0xff,0xff,0xff,0xff,0xf0,
  0x00,0x00,0x00,0x00,0x00,0x00,

};

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);

void initBuff(){
     memset(buffer,0,BUFF_SIZE);
}

void write_cmd1(uint8_t c ){
	  buffer[0]= 0x00; 
	  buffer[1] = c; 
    HAL_I2C_Master_Transmit(&hi2c1,addr_oled,buffer,2,100 );
}

void cmd_list(unsigned char*c, int n){
	 
      unsigned char  bytesOut = 1;
     	memset(buffer,0,WIRE_MAX+1);
      
       while(n--) {
        if(bytesOut >= WIRE_MAX) {
					HAL_I2C_Master_Transmit(&hi2c1,addr_oled,buffer,WIRE_MAX,1000 );
         	memset(buffer,0,WIRE_MAX+1);
          bytesOut = 1;
        }
      buffer[bytesOut] = *c++;  
      bytesOut++;
    }
     if(bytesOut>0){
			 HAL_I2C_Master_Transmit(&hi2c1,addr_oled,buffer,bytesOut,1000 );
		 }
}

void initDisplay()
{
   
    write_cmd1(0xAE);          // 0xAE // display off  
    write_cmd1(0xD5);          // 0xD5 // set display clock division
    write_cmd1(0x80);          // the suggested ratio 0x80 
    write_cmd1(0xA8);          // 0xA8 set multiplex
    write_cmd1(63);            // set height    
    write_cmd1(0xD3);          // set display offset
    write_cmd1(0x00);           // no offset 
    write_cmd1(0x40);            // line #0 setstartline
    write_cmd1(0x8D);          // 0x8D // chargepump 
    write_cmd1(0x14);    //?? 0x10
    write_cmd1(0x20);          // memory mode
    write_cmd1(0x00);          // 0x0 act like ks0108
    write_cmd1(0xA1);           // segremap  
    write_cmd1(0xC8);          // comscandec
    write_cmd1(0xDA);          // 0xDA set com pins
    write_cmd1(0x12); 
    write_cmd1(0x81);          // 0x81 // set contract
    write_cmd1(0xCF);      //??  0x9F
    write_cmd1(0xD9);          // 0xd9 set pre-charge
    write_cmd1(0xF1);         //0x22
    write_cmd1(0xDB);          // SSD1306_SETVCOMDETECT
    write_cmd1(0x40);
    write_cmd1(0xA4);          // 0xA4 // display all on resume
    write_cmd1(0xA6);          // 0xA6 // normal display
    write_cmd1(0x2E);          // deactivate scroll
    write_cmd1(0xAF);          // --turn on oled panel

}

void display()
{
	uint8_t tembuff[2]; 
	 int  count = WIDTH * ((HEIGHT + 7) / 8);
    uint8_t *ptr   = buffer; 
    unsigned char bytesOut = 1;
	unsigned char dlist1[] = {
     SSD1306_PAGEADDR,
     0,                         // Page start address
     0xFF,                      // Page end (not really, but works here)
     SSD1306_COLUMNADDR,
     0 }; 
	// Column start address
	cmd_list(dlist1, sizeof(dlist1));
	 write_cmd1(WIDTH - 1); 
		memset(buffer,0,WIRE_MAX+1);
		 buffer[0] = 0x40; 
		 while(count--) {
      if(bytesOut >= WIRE_MAX) {
				HAL_I2C_Master_Transmit(&hi2c1,addr_oled,buffer,WIRE_MAX,1000 );
				memset(buffer,0,WIRE_MAX+1);
				 buffer[0] = 0x40; 
        bytesOut = 1;
      }
			 buffer[bytesOut] =*ptr++ ; 
       bytesOut++;
    }  
		 if(bytesOut>0){
			 	HAL_I2C_Master_Transmit(&hi2c1,addr_oled,buffer,bytesOut,1000 );
		 }
}

void drawpixel(int x, int y ){
    
  if((x >= 0) && (x <WIDTH) && (y >= 0) && (y < HEIGHT)) {
    buffer[x + (y/8)*WIDTH] |=  (1 << (y&7)); // 
   }
}

void drawBitmap(int x, int y, unsigned char bitmap[], int w, int  h) {
   int i, j; 
   int byteWidth= (w+7)/8; 
   int  byte = 0;
  for ( j = 0; j < h; j++) {
    for ( i = 0; i < w; i++) { 

          if (i & 7)
          byte <<= 1;
          else
          byte = bitmap[j * byteWidth + i / 8];
         if(byte & 0x80){
            drawpixel(x + i,y+j);
         }
    
    }
  }
}

void drawImage(unsigned char bitmap[],int  LOGO_HEIGHT,int  LOGO_WIDTH){
    drawBitmap(
    (WIDTH  - LOGO_WIDTH ) / 2,
    (HEIGHT - LOGO_HEIGHT) / 2,
    bitmap, LOGO_WIDTH, LOGO_HEIGHT);
}

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
  MX_I2C1_Init();
 initBuff();
 initDisplay(); 
 drawImage(logo_bmp,67,45);
  display(); 
  while (1)
  {
   
  }
 
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

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
