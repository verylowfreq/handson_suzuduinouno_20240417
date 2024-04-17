#include <ch32v20x_conf.h>

void setup() {
  Delay_Init();

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  GPIO_InitTypeDef GPIOInitStructure = { 0 };
  GPIOInitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIOInitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIOInitStructure);
}

void loop() {
  GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);
  Delay_Ms(250);
  GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET);
  Delay_Ms(250);
}
