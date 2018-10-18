/**
  ******************************************************************************
  * @file    EXTI_InterruptPriority\main.h
  * @author  MCD Application Team
  * @version V2.0.1
  * @date    18-November-2011
  * @brief   This file contains the external declaration for main.c file.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */   

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Evalboard I/Os configuration */
#define TUNER_SPI_PORT  (GPIOB)
#define BUTTON (GPIOC)


#define CtrlData  (GPIO_PIN_2)
#define CtrlClk  (GPIO_PIN_1)
#define CtrlEn  (GPIO_PIN_0)
#define ButtonBit (GPIO_PIN_4)



#define SET_CE_OUT()	{GPIO_Init(TUNER_SPI_PORT, (GPIO_Pin_TypeDef)CtrlEn, GPIO_MODE_OUT_PP_LOW_FAST );}//Output push-pull, low level, 10MHz 

#define SET_SCL_OUT()	{GPIO_Init(TUNER_SPI_PORT, (GPIO_Pin_TypeDef)CtrlClk, GPIO_MODE_OUT_PP_LOW_FAST );}

#define SET_SDA_OUT()	{GPIO_Init(TUNER_SPI_PORT, (GPIO_Pin_TypeDef)CtrlData, GPIO_MODE_OUT_PP_LOW_FAST );}

//static int push_flag = 0;




/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

#endif /* __MAIN_H__ */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
