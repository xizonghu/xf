#ifndef __GPIO_H__
#define __GPIO_H__

/*
enum FW_GPIO_PORT {
    FW_GPIO_PORT_A        = (unsigned long)GPIOA,
    FW_GPIO_PORT_B        = (unsigned long)GPIOB,
    FW_GPIO_PORT_C        = (unsigned long)GPIOC,
    FW_GPIO_PORT_D        = (unsigned long)GPIOD,
    FW_GPIO_PORT_E        = (unsigned long)GPIOE,
    FW_GPIO_PORT_F        = (unsigned long)GPIOF,
    FW_GPIO_PORT_G        = (unsigned long)GPIOG,
    FW_GPIO_PORT_H        = (unsigned long)GPIOH,
};

enum FW_GPIO_PIN {
    FW_GPIO_PIN_0         = (unsigned char)0x01,
    FW_GPIO_PIN_1         = (unsigned char)0x02,
    FW_GPIO_PIN_2         = (unsigned char)0x03,
    FW_GPIO_PIN_3         = (unsigned char)0x04,
    FW_GPIO_PIN_4         = (unsigned char)0x05,
    FW_GPIO_PIN_5         = (unsigned char)0x06,
    FW_GPIO_PIN_6         = (unsigned char)0x07,
    FW_GPIO_PIN_7         = (unsigned char)0x08,
    FW_GPIO_PIN_ALL       = (unsigned char)0xff,
};

enum FW_GPIO_DATA {
    FW_GPIO_DATA_0        = (unsigned char)0x00,
    FW_GPIO_DATA_1        = (unsigned char)0x01,
    FW_GPIO_DATA_INVALID  = (unsigned char)0xff,
};

enum FW_GPIO_MODE {
    FW_GPIO_MODE_IN        = (unsigned char)0x01,
    FW_GPIO_MODE_OUT      = (unsigned char)0x02,
    FW_GPIO_MODE_IT        = (unsigned char)0x04,
    FW_GPIO_MODE_PU        = (unsigned char)0x08,  //Input pull-up
    FW_GPIO_MODE_PP        = (unsigned char)0x10,  //Output open-drain
    FW_GPIO_MODE_OD        = (unsigned char)0x20,  //Output push
    FW_GPIO_MODE_NVALID    = (unsigned char)0xff,
};

struct FW_GPIO_S {
    const char *name;
    unsigned char port;
    unsigned char pin;
    enum GPIO_MOUDLE_MODE mode;
    unsigned char data;
};

int fw_gpio_set_mode(enum FW_GPIO_PORT port, enum FW_GPIO_PIN pin, enum FW_GPIO_MODE mode);
int fw_gpio_set_data(enum FW_GPIO_PORT port, enum FW_GPIO_PIN pin, char data);
int fw_gpio_get_data(enum FW_GPIO_PORT port, enum FW_GPIO_PIN pin, char *data);
*/

#define BSP_GPIO_PORT_A           GPIOA
#define BSP_GPIO_PORT_B           GPIOB
#define BSP_GPIO_PORT_C           GPIOC
#define BSP_GPIO_PORT_D           GPIOD
#define BSP_GPIO_PORT_E           GPIOE
#define BSP_GPIO_PORT_F           GPIOF
#define BSP_GPIO_PORT_G           GPIOG
#define BSP_GPIO_PORT_H           (x)

#define BSP_GPIO_PIN_0            GPIO_Pin_0
#define BSP_GPIO_PIN_1            GPIO_Pin_1
#define BSP_GPIO_PIN_2            GPIO_Pin_2
#define BSP_GPIO_PIN_3            GPIO_Pin_3
#define BSP_GPIO_PIN_4            GPIO_Pin_4
#define BSP_GPIO_PIN_5            GPIO_Pin_5
#define BSP_GPIO_PIN_6            GPIO_Pin_6
#define BSP_GPIO_PIN_7            GPIO_Pin_7
#define BSP_GPIO_PIN_ALL          GPIO_Pin_All

#define BSP_GPIO_MODE_IN_FL       GPIO_Mode_In_FL_No_IT  //输入浮空普通IO
#define BSP_GPIO_MODE_IN_PU       GPIO_Mode_In_PU_No_IT  //输入上拉普通IO
#define BSP_GPIO_MODE_IN_FL_IT    GPIO_Mode_In_FL_IT  //输入浮空启中断IO
#define BSP_GPIO_MODE_IN_PU_IT    GPIO_Mode_In_PU_IT  //输入上拉启中断IO
#define BSP_GPIO_MODE_OUT_OD_H    GPIO_Mode_Out_OD_HiZ_Slow  //输出漏极开路高电平
#define BSP_GPIO_MODE_OUT_PP_H    GPIO_Mode_Out_PP_High_Slow  //输出推挽高电平
#define BSP_GPIO_MODE_OUT_OD_L    GPIO_Mode_Out_OD_Low_Slow  //输出漏极开路低电平
#define BSP_GPIO_MODE_OUT_PP_L    GPIO_Mode_Out_PP_Low_Slow  //输出推挽低电平

#define BSP_GPIO_IT_PIN_0         EXTI_Pin_0
#define BSP_GPIO_IT_PIN_1         EXTI_Pin_1
#define BSP_GPIO_IT_PIN_2         EXTI_Pin_2
#define BSP_GPIO_IT_PIN_3         EXTI_Pin_3
#define BSP_GPIO_IT_PIN_4         EXTI_Pin_4
#define BSP_GPIO_IT_PIN_5         EXTI_Pin_5
#define BSP_GPIO_IT_PIN_6         EXTI_Pin_6
#define BSP_GPIO_IT_PIN_7         EXTI_Pin_7

#define BSP_GPIO_IT_HIGH          EXTI_Trigger_Rising  //高电平触发
#define BSP_GPIO_IT_LOW           EXTI_Trigger_Falling_Low  //低电平触发
#define BSP_GPIO_IT_EDGE          EXTI_Trigger_Rising_Falling  //边沿触发
#define BSP_GPIO_IT_RISEING       EXTI_Trigger_Rising  //上升沿触发
#define BSP_GPIO_IT_FALLING       EXTI_Trigger_Falling  //下降沿触发

#define BSP_GPIO_DATA_HIGH SET
#define BSP_GPIO_DATA_LOW  RESET  //

#define bsp_gpio_set_mode(port, pin, mode)   GPIO_Init(port, pin, mode)
#define bsp_gpio_set_high(port, pin)         GPIO_SetBits(port, pin)
#define bsp_gpio_set_low(port, pin)          GPIO_ResetBits(port, pin)
#define bsp_gpio_get_data(port, pin)         GPIO_ReadInputDataBit(port, pin)
#define bsp_gpio_set_it(port, pin, mode)     EXTI_SetPinSensitivity(pin, mode)
//#define bsp_gpio_enable_it(port, pin)    


extern int bsp_gpio_init();
extern int bsp_gpio_exit();
#endif
