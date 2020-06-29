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

#include "stm32f103xb.h"

/* redefine flash memory start address in a compliler friendly way */
#ifdef FLASH_BASE
#undef FLASH_BASE
#define FLASH_BASE          0x08001000U /* 0x1000 is for the bootloader */
#endif /* FLASH_BASE */

#define VECT_TAB_OFFSET     0x00000000U

extern void HardFault_Handler(void);
extern void SysTick_Handler(void);
extern void SystemInit(void);

uint32_t volatile msTicks;
static uint32_t SystemCoreClock;

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
