/*
 * Copyright 2020 Denis Meltsaykin
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "main.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_bus.h"

/*
 *  This is running on early stages after startup.s but before main.
 *  It sets up a 8Mhz external oscilator with corresponding PLL and USB dividers
 *  and multipliers settings to get 72Mhz core frequency and 48Mhz for USB.
 */
void SystemInit(void){
    /* Reset the RCC clock configuration to the default reset state(for debug purpose) */
    /* Set HSION bit */
    RCC->CR |= 0x00000001U;
    /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
    RCC->CFGR &= 0xF8FF0000U;
    /* Reset HSEON, CSSON and PLLON bits */
    RCC->CR &= 0xFEF6FFFFU;
    /* Reset HSEBYP bit */
    RCC->CR &= 0xFFFBFFFFU;
    /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
    RCC->CFGR &= 0xFF80FFFFU;
    /* Disable all interrupts and clear pending bits  */
    RCC->CIR = 0x009F0000U;
    /* Set Vtable address */
    SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET;

    /* Set flash latency and check it back*/
    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_1);
    if ((uint32_t)(READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY)) != FLASH_ACR_LATENCY_1){
        HardFault_Handler();
    };
    /* Enable HSE */
    SET_BIT(RCC->CR, RCC_CR_HSEON);
    /* Wait until HSE is ready */
    while ((READ_BIT(RCC->CR, RCC_CR_HSERDY) == (RCC_CR_HSERDY)) != 1 ) {};
    /* Configure PLL for SYSCLK */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL,
        ((RCC_CFGR_PLLSRC | 0x00000000U) & (RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE)) | RCC_CFGR_PLLMULL9);
    /* Enable PLL */
    SET_BIT(RCC->CR, RCC_CR_PLLON);
    /* Wait for PLL to be ready */
    while ((READ_BIT(RCC->CR, RCC_CR_PLLRDY) == (RCC_CR_PLLRDY)) != 1) {};
    /* AHB Prescaler */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, RCC_CFGR_HPRE_DIV1);
    /* APB1 Prescaler */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, RCC_CFGR_PPRE1_DIV2);
    /* APB2 Prescaler */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, RCC_CFGR_PPRE2_DIV1);
    /* Set SYSCLK Source */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
    /* Wait for SYSCLK is ready */
    while((uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_SWS)) != RCC_CFGR_SWS_PLL) {};

    SystemCoreClock = 72000000U;
    // Set USB Clock as PLL div 1.5
    MODIFY_REG(RCC->CFGR, RCC_CFGR_USBPRE, 0x00000000U);
    // Setup SysTick at 1ms resolution (from core_cm3.h CMSIS)
    SysTick_Config(SystemCoreClock / 1000);
};

void HardFault_Handler(void) {
    /* Hard Fault Handler */
	while(1){};
};

/* SysTick Interrupt Handler */
void SysTick_Handler (void) {
    msTicks++;
}

void Sleep(uint32_t time){
    uint32_t start = msTicks;
    time += 1U; // weird part from HAL
    while (msTicks - start < time){
        __WFI();
    };
};

/* ===== Initialization end =====  */


const void DelayCycles(uint32_t cycles){
    while (--cycles){
        asm volatile ("nop");
    }
};

int main(){
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);

    LL_GPIO_InitTypeDef PortBInit = {0};
    PortBInit.Pin = LL_GPIO_PIN_ALL;
    PortBInit.Mode = LL_GPIO_MODE_OUTPUT;
    PortBInit.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    PortBInit.Speed = LL_GPIO_SPEED_FREQ_LOW;
    LL_GPIO_Init(GPIOB, &PortBInit);
    PortBInit.Pin = LL_GPIO_PIN_ALL;
    PortBInit.Mode = LL_GPIO_MODE_OUTPUT;
    PortBInit.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    PortBInit.Speed = LL_GPIO_SPEED_FREQ_LOW;
    LL_GPIO_Init(GPIOA, &PortBInit);

    while (1){
        LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_12);
        Sleep(1000);
    };
    return 0;
};
