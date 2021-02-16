#ifndef ARDUINO
#define __IO volatile
#define uint32_t unsigned int
#define uint8_t  unsigned char
#define uint16_t unsigned short
#define __I
#endif

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

// #define TIM4                ((TIM_TypeDef *)TIM4_BASE)
#define pinNumber           13

void loop_();
void delay_(unsigned long long int  x);


int main() {
  RCC -> APB2ENR |= 16U; //Enable GPIO C Power
  GPIOC->CRH |= 0x180000U; // Set GPIO PORTC to OUTPUT Mode @50MHz with GP Push Pull 

  while(1) {loop_();}
}

void loop_() { 
  delay_(0x0A00U);
  GPIOC -> ODR ^= (1 << pinNumber);
  // delay_(0x0A00U);
  // GPIOC -> BSRR = (1 << pinNumber);
  // GPIOC -> BRR = (1 << pinNumber);
}

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