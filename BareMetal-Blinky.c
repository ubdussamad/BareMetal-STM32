/**
 * @file BareMetal-Blinky.c
 * @author Mohammad Samad (alias:ubdussamad) (ubdussamad@gmail.com)
 * @brief Most Barebone Version of Blinky Possible.
 * @version 0.1
 * @date 2021-02-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#define __IO volatile
#define uint32_t unsigned int
#define uint8_t  unsigned char
#define uint16_t unsigned short

#define GPIO_PORT_C_ADDR  0x40011000U
#define RCC_ADDR          0x40021000U

typedef struct
{
  __IO uint32_t CRL;
  __IO uint32_t CRH;
  __IO uint32_t IDR;
  __IO uint32_t ODR;
  __IO uint32_t BSRR;
  __IO uint32_t BRR;
  __IO uint32_t LCKR;
} GPIO_TypeDef;

typedef struct
{
  __IO uint32_t CR;
  __IO uint32_t CFGR;
  __IO uint32_t CIR;
  __IO uint32_t APB2RSTR;
  __IO uint32_t APB1RSTR;
  __IO uint32_t AHBENR;
  __IO uint32_t APB2ENR;
  __IO uint32_t APB1ENR;
  __IO uint32_t BDCR;
  __IO uint32_t CSR;
} RCC_TypeDef;

#define GPIOC               ((GPIO_TypeDef *) GPIO_PORT_C_ADDR)
#define RCC                 ((RCC_TypeDef *)  RCC_ADDR)
#define pinNumber           13

void loop_();
void delay_(unsigned long long int  x);


int main() {
  RCC -> APB2ENR |= 16U; //Enable GPIO C Power
  GPIOC->CRH |= 0x180000U; // Set GPIO PORTC to OUTPUT Mode @50MHz in Push Pull Mode 

  while(1) {loop_();}
}

void loop_() { 
  delay_(0x0A00U);
  GPIOC -> ODR ^= (1 << pinNumber); // Toggles the ODR (Output data Register by XORing it with 1)
}

/**
 * @brief This is the crudest way to creating a
 * delay (Please don't do this in production),
 * as for a proper timer based delay routine I've
 * had to setup NVIC and what not, thus I decided
 * to create a delay this way. Since it's supposed to be 
 * a barebone program, it's not unholy to use it here.
 * @param x How long to delay for. Figure out the timing 
 * youselves. For me, x=0x0A00 gives around 300ms. (CPU@72MHz)
 */
void delay_(unsigned long long int  x) {
  int i = 0;
  volatile static int arr[10] = {1,2,3,4,5,6,7,8,9,0};
  for (i = 0; i < x; i++) {
    arr[i%10] *= arr[(i%10)];
    arr[i%10] += arr[(i%10)];
    arr[i%10] -= arr[(i%10)];
    arr[i%10] /= arr[(i%10)];
  }
}