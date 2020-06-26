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

#ifndef _MAIN_HPP_
#define _MAIN_HPP_

#include <cstdint>
#include "stm32f103xb.h"

/* redefine flash memory start address in a compliler friendly way */
#ifdef FLASH_BASE
#undef FLASH_BASE
#define FLASH_BASE          0x08001000U /* 0x1000 is for the bootloader */
#endif /* FLASH_BASE */

#define VECT_TAB_OFFSET     0x00000000U

extern "C" {
    void HardFault_Handler(void);
    void SysTick_Handler(void);
    void SystemInit(void);
};

uint32_t volatile msTicks;
static uint32_t SystemCoreClock;

typedef enum {
    GPIOSet,
    GPIOReset
} GPIOPinState;

typedef enum {
    GPIOPIN_0  =((uint16_t)0x0001),  /* Pin 0 selected    */
    GPIOPIN_1  =((uint16_t)0x0002),  /* Pin 1 selected    */
    GPIOPIN_2  =((uint16_t)0x0004),  /* Pin 2 selected    */
    GPIOPIN_3  =((uint16_t)0x0008),  /* Pin 3 selected    */
    GPIOPIN_4  =((uint16_t)0x0010),  /* Pin 4 selected    */
    GPIOPIN_5  =((uint16_t)0x0020),  /* Pin 5 selected    */
    GPIOPIN_6  =((uint16_t)0x0040),  /* Pin 6 selected    */
    GPIOPIN_7  =((uint16_t)0x0080),  /* Pin 7 selected    */
    GPIOPIN_8  =((uint16_t)0x0100),  /* Pin 8 selected    */
    GPIOPIN_9  =((uint16_t)0x0200),  /* Pin 9 selected    */
    GPIOPIN_10 =((uint16_t)0x0400),  /* Pin 10 selected   */
    GPIOPIN_11 =((uint16_t)0x0800),  /* Pin 11 selected   */
    GPIOPIN_12 =((uint16_t)0x1000),  /* Pin 12 selected   */
    GPIOPIN_13 =((uint16_t)0x2000),  /* Pin 13 selected   */
    GPIOPIN_14 =((uint16_t)0x4000),  /* Pin 14 selected   */
    GPIOPIN_15 =((uint16_t)0x8000),  /* Pin 15 selected   */
    GPIOPIN_All=((uint16_t)0xFFFF)   /* All pins selected */
} GPIOPin;


/* Compatibility with stm32 includes */
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)    ((REG) & (BIT))
#define CLEAR_REG(REG)        ((REG) = (0x0))
#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
#define READ_REG(REG)         ((REG))
#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))
#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL)))

#endif /* _MAIN_HPP_ */
