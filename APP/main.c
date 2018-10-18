

/* Includes ------------------------------------------------------------------*/
//#include "main.h"
#include "stm8s.h"

#include "stm8s_gpio.h"
#include "stm8s_it.h"
#include "stm8s_conf.h"






/* Private defines -----------------------------------------------------------*/
static void Delay(uint32_t nCount);
static void SYNC_GPIO_Init();


//static void Delay_t();

/* SPI GPIO define */
#define SPI_CLOCK(a)  a(GPIOA, GPIO_PIN_1);

#define SPI_DATA(a)   a(GPIOA, GPIO_PIN_2);

#define SPI_READ_DATA ((GPIO_ReadInputData(GPIOA) >> 1) & 1);


//----------   EXT LNA   set  ----------//
#define EXT_LNA1_LOW_IP3 GPIO_WriteHigh(GPIOD,GPIO_PIN_1);
#define EXT_LNA2_LOW_IP3 GPIO_WriteHigh(GPIOD,GPIO_PIN_3);

#define EXT_LNA1_ON GPIO_WriteHigh(GPIOD,GPIO_PIN_0);
#define EXT_LNA1_OFF GPIO_WriteLow(GPIOD,GPIO_PIN_0);


#define EXT_LNA2_ON GPIO_WriteHigh(GPIOD,GPIO_PIN_2);
#define EXT_LNA2_OFF GPIO_WriteLow(GPIOD,GPIO_PIN_2);


//--------------------------------//

#define SPI_EN_1C        GPIO_WriteLow(GPIOD, GPIO_PIN_6);
#define SPI_DIS_1C       GPIO_WriteHigh(GPIOD, GPIO_PIN_6);



#define SPI_EN_2C        GPIO_WriteLow(GPIOA, GPIO_PIN_3);
#define SPI_DIS_2C       GPIO_WriteHigh(GPIOA, GPIO_PIN_3);


#define SPI_READ      GPIO_Init(GPIOA, (GPIO_Pin_TypeDef)GPIO_PIN_2, GPIO_MODE_IN_FL_NO_IT);
#define SPI_WRITE     GPIO_Init(GPIOA, (GPIO_Pin_TypeDef)GPIO_PIN_2, GPIO_MODE_OUT_PP_LOW_FAST);




void clock_cycle()
{
    SPI_CLOCK(GPIO_WriteLow);
    Delay(1);
    SPI_CLOCK(GPIO_WriteHigh);
    Delay(1);
    SPI_CLOCK(GPIO_WriteLow);
    Delay(1);
}



void rffc2071a_hw_rst()
{

}
// 1 Conver spi programming
uint16_t rffc2071a_spi_read_1C(uint8_t addr)
{
    uint16_t data =0;
    int i = 0;
    void (*pGPIO)(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins) = 0;
    SPI_WRITE;
    SPI_CLOCK(GPIO_WriteLow);
    SPI_DATA(GPIO_WriteLow);
    clock_cycle();
    SPI_EN_1C; 
    clock_cycle();
    SPI_DATA(GPIO_WriteHigh);
    clock_cycle();
    for(i= 0; i< 7;i++)
    {
        pGPIO = (addr & (1 << (6-i))) == 0?GPIO_WriteLow:GPIO_WriteHigh;
        SPI_DATA(pGPIO);
        clock_cycle();
    }
    SPI_READ;
    clock_cycle();
    for(i = 0; i < 16;i++)
    {
        clock_cycle();
        data = data << 1;
        data |= SPI_READ_DATA;
    }
    SPI_DIS_1C; 
    SPI_WRITE;
    clock_cycle();
    return data;
}

void rffc2071a_spi_write_1C(uint8_t addr, uint16_t data)
{
    int i = 0;
    void (*pGPIO)(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins) = 0;
    SPI_WRITE;
    SPI_CLOCK(GPIO_WriteLow);
    SPI_DATA(GPIO_WriteLow);
    clock_cycle();
    SPI_EN_1C; 
    clock_cycle();
    SPI_DATA(GPIO_WriteLow);
    clock_cycle();
    for(i= 0; i< 7;i++)
    {
        pGPIO = (addr & (1 << (6-i))) == 0?GPIO_WriteLow:GPIO_WriteHigh;
        SPI_DATA(pGPIO);
        clock_cycle();
    }
    for(i = 0; i < 16;i++)
    {
        pGPIO = (data & (1 << (15-i))) == 0?GPIO_WriteLow:GPIO_WriteHigh;
        SPI_DATA(pGPIO);
        clock_cycle();
    }
    SPI_DIS_1C; 
    clock_cycle();
}
//----------------------------------------------------//


// 2 Conver spi programming
uint16_t rffc2071a_spi_read_2C(uint8_t addr)
{
    uint16_t data =0;
    int i = 0;
    void (*pGPIO)(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins) = 0;
    SPI_WRITE;
    SPI_CLOCK(GPIO_WriteLow);
    SPI_DATA(GPIO_WriteLow);
    clock_cycle();
    SPI_EN_2C; 
    clock_cycle();
    SPI_DATA(GPIO_WriteHigh);
    clock_cycle();
    for(i= 0; i< 7;i++)
    {
        pGPIO = (addr & (1 << (6-i))) == 0?GPIO_WriteLow:GPIO_WriteHigh;
        SPI_DATA(pGPIO);
        clock_cycle();
    }
    SPI_READ;
    clock_cycle();
    for(i = 0; i < 16;i++)
    {
        clock_cycle();
        data = data << 1;
        data |= SPI_READ_DATA;
    }
    SPI_DIS_2C; 
    SPI_WRITE;
    clock_cycle();
    return data;
}

void rffc2071a_spi_write_2C(uint8_t addr, uint16_t data)
{
    int i = 0;
    void (*pGPIO)(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins) = 0;
    SPI_WRITE;
    SPI_CLOCK(GPIO_WriteLow);
    SPI_DATA(GPIO_WriteLow);
    clock_cycle();
    SPI_EN_2C; 
    clock_cycle();
    SPI_DATA(GPIO_WriteLow);
    clock_cycle();
    for(i= 0; i< 7;i++)
    {
        pGPIO = (addr & (1 << (6-i))) == 0?GPIO_WriteLow:GPIO_WriteHigh;
        SPI_DATA(pGPIO);
        clock_cycle();
    }
    for(i = 0; i < 16;i++)
    {
        pGPIO = (data & (1 << (15-i))) == 0?GPIO_WriteLow:GPIO_WriteHigh;
        SPI_DATA(pGPIO);
        clock_cycle();
    }
    SPI_DIS_2C; 
    clock_cycle();
}
//----------------------------------------------------//





;void main(void)
{
 
  uint16_t rb = 0;
 
 int n=0; 
  SYNC_GPIO_Init();

// Externel  LNA  set    n[
EXT_LNA1_LOW_IP3;
 EXT_LNA2_LOW_IP3;
 EXT_LNA1_ON;
 EXT_LNA2_ON;
//--------------


 for (n = 0;n<5;n++)
{
	Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
}



  SPI_DIS_1C; 
  SPI_DIS_2C; 

//---------------start set 1 conver--------------------//  
  rb = rffc2071a_spi_read_1C(0x0f); //not use  do the spi bug
  rffc2071a_spi_write_1C(0xf, rb|0x00);
//  rffc2071a_spi_write(0x00,0xbef9);
  
  rffc2071a_spi_write_1C(8, 0xff00|(127 << 8));

  rffc2071a_spi_write_1C(4, 0xacbf|(12 << 8));
  rffc2071a_spi_write_1C(5, 0xacbf|(12 << 8));
  rffc2071a_spi_write_1C(0x1e, 5|4);// TESTrgbyp = 1



  rffc2071a_spi_write_1C(0x16, 1);// set led lock
 

//------LO 450  -----------//
//P1 LO   p1:     0x0c  0x1238
//p2 LO   p2: 	  0x0f  0x123a
//-----------------------//

//------LO 430  -----------//
//P1 LO   p1:      0x0c  0x1138
//P1 LO   p1:      0x0d  0x6666
//P1 LO   p1:      0x0e  0x6600
//P1 LO   p1:      0x0f  0x113a
//P1 LO   p1:      0x10  0x6666
//P1 LO   p1:      0x11  0x6600
//-----------------------//

//------LO 1081.25  -----------//
//P1 LO   p1:      0x0c  0x15a8
//P1 LO   p1:      0x0d  0x4000
//P1 LO   p1:      0x0e  0x0000
//P1 LO   p1:      0x0f  0x15aa
//P1 LO   p1:      0x10  0x4000
//P1 LO   p1:      0x11  0x0000
//-----------------------//

//------LO 525  -----------//
//P1 LO   p1:      0x0c  0x1538
//P1 LO   p1:      0x0d  0x0000
//P1 LO   p1:      0x0e  0x0000
//P1 LO   p1:      0x0f  0x153a
//P1 LO   p1:      0x10  0x0000
//P1 LO   p1:      0x11  0x0000
//-----------------------//

//------LO 630  -----------//
//P1 LO   p1:      0x0c  0x1938
//P1 LO   p1:      0x0d  0x6666
//P1 LO   p1:      0x0e  0x6600
//P1 LO   p1:      0x0f  0x193a
//P1 LO   p1:      0x10  0x6666
//P1 LO   p1:      0x11  0x6600
//-----------------------//


//------LO 900  -----------//
//P1 LO   p1:      0x0c  0x1228
//P1 LO   p1:      0x0d  0x0000
//P1 LO   p1:      0x0e  0x0000
//P1 LO   p1:      0x0f  0x122a
//P1 LO   p1:      0x10  0x0000
//P1 LO   p1:      0x11  0x0000
//-----------------------//


//------LO 950  -----------//
//P1 LO   p1:      0x0c  0x1328
//P1 LO   p1:      0x0d  0x0000
//P1 LO   p1:      0x0e  0x0000
//P1 LO   p1:      0x0f  0x132a
//P1 LO   p1:      0x10  0x0000
//P1 LO   p1:      0x11  0x0000
//-----------------------//


//------LO 1405  -----------//
//P1 LO   p1:      0x0c  0x1c14
//P1 LO   p1:      0x0d  0x3333
//P1 LO   p1:      0x0e  0x3300
//P1 LO   p1:      0x0f  0x1c16
//P1 LO   p1:      0x10  0x3333
//P1 LO   p1:      0x11  0x3300
//-----------------------//





//   lo 
  rffc2071a_spi_write_1C(0xc,0x1238);
  rffc2071a_spi_write_1C(0xd, 0x0000);
  rffc2071a_spi_write_1C(0xe, 0x0000);
  //P2 test  
  rffc2071a_spi_write_1C(0xf, 0x123a);
  rffc2071a_spi_write_1C(0x10, 0x0000);
  rffc2071a_spi_write_1C(0x11, 0x0000);


  //loop filter
//  rffc2071a_spi_write(6, 0x0000);
//  rffc2071a_spi_write(7, 0x0000);

  //P1 low noise 314
 // rffc2071a_spi_write(0xc, ((96<<7)|  (16<<4)| (2<<2))|0x1a94);
//  rffc2071a_spi_write(0xd, 0xaa15);
//  rffc2071a_spi_write(0xe, 0x6a << 8);
  //P2 low noise 314
//  rffc2071a_spi_write(0xf, ((96<<7)|  (16<<4)| (2<<2))|0x1e84);
//  rffc2071a_spi_write(0x10, 0xaa15);
//  rffc2071a_spi_write(0x11, 0x6a << 8);
  rffc2071a_spi_write_1C(0x0b, 0x7e00);//tx rx mode
  rffc2071a_spi_write_1C(0x18, 0x0281);//tx rx mode
 //low phase noise test
  rffc2071a_spi_write_1C(0x00, 0xfff9);//
  rffc2071a_spi_write_1C(0x09,0x8228 );//pll relock
//-----------end 1 conver -------------------------//


//---------------start set 2 conver--------------------//  
	rb = rffc2071a_spi_read_2C(0x0f); //not use  do the spi bug
 	rffc2071a_spi_write_2C(0xf, rb|0x00);
//  rffc2071a_spi_write(0x00,0xbef9);
  
  rffc2071a_spi_write_2C(8, 0xff00|(127 << 8));

  rffc2071a_spi_write_2C(4, 0xacbf|(12 << 8));
  rffc2071a_spi_write_2C(5, 0xacbf|(12 << 8));
  rffc2071a_spi_write_2C(0x1e, 5|4);// TESTrgbyp = 1



  rffc2071a_spi_write_2C(0x16, 1);// set led lock
 

//------LO 450  -----------//
//P1 LO   p1:     0x0c  0x1238
//p2 LO   p2: 	  0x0f  0x123a
//-----------------------//


//------LO 1081.25  -----------//
//P1 LO   p1:      0x0c  0x15a8
//P1 LO   p1:      0x0d  0x4000
//P1 LO   p1:      0x0e  0x0000
//P1 LO   p1:      0x0f  0x15aa
//P1 LO   p1:      0x10  0x4000
//P1 LO   p1:      0x11  0x0000
//-----------------------//

//------LO 1405  -----------//
//P1 LO   p1:      0x0c  0x1c14
//P1 LO   p1:      0x0d  0x3333
//P1 LO   p1:      0x0e  0x3300
//P1 LO   p1:      0x0f  0x1c16
//P1 LO   p1:      0x10  0x3333
//P1 LO   p1:      0x11  0x3300
//-----------------------//

//------LO 1450  -----------//
//P1 LO   p1:      0x0c  0x1d14
//P1 LO   p1:      0x0d  0x0000
//P1 LO   p1:      0x0e  0x0000
//P1 LO   p1:      0x0f  0x1d16
//P1 LO   p1:      0x10  0x0000
//P1 LO   p1:      0x11  0x0000
//-----------------------//


//------LO 650  -----------//
//P1 LO   p1:      0x0c  0x1a38
//P1 LO   p1:      0x0d  0x0000
//P1 LO   p1:      0x0e  0x0000
//P1 LO   p1:      0x0f  0x1a3a
//P1 LO   p1:      0x10  0x0000
//P1 LO   p1:      0x11  0x0000
//-----------------------//


//------LO 725  -----------//
//P1 LO   p1:      0x0c  0x1d24
//P1 LO   p1:      0x0d  0x0000
//P1 LO   p1:      0x0e  0x0000
//P1 LO   p1:      0x0f  0x1d26
//P1 LO   p1:      0x10  0x0000
//P1 LO   p1:      0x11  0x0000
//-----------------------//


//------LO 800  -----------//
//P1 LO   p1:      0x0c  0x2024
//P1 LO   p1:      0x0d  0x0000
//P1 LO   p1:      0x0e  0x0000
//P1 LO   p1:      0x0f  0x2026
//P1 LO   p1:      0x10  0x0000
//P1 LO   p1:      0x11  0x0000
//-----------------------//


//------LO 875  -----------//
//P1 LO   p1:      0x0c  0x11a8
//P1 LO   p1:      0x0d  0x0000
//P1 LO   p1:      0x0e  0x0000
//P1 LO   p1:      0x0f  0x11aa
//P1 LO   p1:      0x10  0x0000
//P1 LO   p1:      0x11  0x0000
//-----------------------//





 
  //rffc2071a_spi_write_2C(0xc,0x1a38);
  //rffc2071a_spi_write_2C(0xc,0x1d24);
  //rffc2071a_spi_write_2C(0xc,0x2024);
  rffc2071a_spi_write_2C(0xc,0x11a8);
  rffc2071a_spi_write_2C(0xd, 0x0000);
  rffc2071a_spi_write_2C(0xe, 0x0000);
  //P2 test 
  //rffc2071a_spi_write_2C(0xf, 0x1a3a);
  //rffc2071a_spi_write_2C(0xf, 0x1d26);
  //rffc2071a_spi_write_2C(0xf, 0x2026);
  rffc2071a_spi_write_2C(0xf, 0x11aa);
  rffc2071a_spi_write_2C(0x10, 0x0000);
  rffc2071a_spi_write_2C(0x11, 0x0000);







  //loop filter
//  rffc2071a_spi_write(6, 0x0000);
//  rffc2071a_spi_write(7, 0x0000);

  //P1 low noise 314
 // rffc2071a_spi_write(0xc, ((96<<7)|  (16<<4)| (2<<2))|0x1a94);
//  rffc2071a_spi_write(0xd, 0xaa15);
//  rffc2071a_spi_write(0xe, 0x6a << 8);
  //P2 low noise 314
//  rffc2071a_spi_write(0xf, ((96<<7)|  (16<<4)| (2<<2))|0x1e84);
//  rffc2071a_spi_write(0x10, 0xaa15);
//  rffc2071a_spi_write(0x11, 0x6a << 8);
  rffc2071a_spi_write_2C(0x0b, 0x7e00);//tx rx mode
 //low phase noise test
  rffc2071a_spi_write_2C(0x00, 0xfff9);//
  rffc2071a_spi_write_2C(0x09,0x8228 );//pll relock


//-----------end 2 conver -------------------------//






}
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}
static void SYNC_GPIO_Init()
{

   GPIO_Init(GPIOA, (GPIO_Pin_TypeDef)GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_FAST);//SPI cs1
   GPIO_Init(GPIOA, (GPIO_Pin_TypeDef)GPIO_PIN_2, GPIO_MODE_OUT_PP_LOW_FAST);//SPI clk
   GPIO_Init(GPIOA, (GPIO_Pin_TypeDef)GPIO_PIN_1, GPIO_MODE_OUT_PP_LOW_FAST);//SPI DATA
   GPIO_Init(GPIOD, (GPIO_Pin_TypeDef)GPIO_PIN_6, GPIO_MODE_OUT_PP_LOW_FAST);//SPI cs2
   
//----------ext lna init  
	GPIO_Init(GPIOD, (GPIO_Pin_TypeDef)GPIO_PIN_0, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_Init(GPIOD, (GPIO_Pin_TypeDef)GPIO_PIN_1, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_Init(GPIOD, (GPIO_Pin_TypeDef)GPIO_PIN_2, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_Init(GPIOD, (GPIO_Pin_TypeDef)GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_FAST);
//---------------------



}


static void Delay(uint32_t nCount)
{
    /* Decrement nCount value */
    while (nCount != 0)
    {
        nCount--;
    }

}
/*
static void Delay_t()
{
  Delay(1000);
}
*/
#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
//void assert_failed(uint8_t* file, uint32_t line)
//{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
 // while (1)
 // {
 // }
//}
#endif


