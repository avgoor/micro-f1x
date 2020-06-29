#ifndef _GPIO_H_
#define _GPIO_H_

#include "stm32f103xb.h"

#define GPIOPIN_0  	0x0001  /* Pin 0 selected    */
#define GPIOPIN_1  	0x0002  /* Pin 1 selected    */
#define GPIOPIN_2  	0x0004  /* Pin 2 selected    */
#define GPIOPIN_3  	0x0008  /* Pin 3 selected    */
#define GPIOPIN_4  	0x0010  /* Pin 4 selected    */
#define GPIOPIN_5  	0x0020  /* Pin 5 selected    */
#define GPIOPIN_6  	0x0040  /* Pin 6 selected    */
#define GPIOPIN_7  	0x0080  /* Pin 7 selected    */
#define GPIOPIN_8  	0x0100  /* Pin 8 selected    */
#define GPIOPIN_9  	0x0200  /* Pin 9 selected    */
#define GPIOPIN_10 	0x0400  /* Pin 10 selected   */
#define GPIOPIN_11 	0x0800  /* Pin 11 selected   */
#define GPIOPIN_12 	0x1000  /* Pin 12 selected   */
#define GPIOPIN_13 	0x2000  /* Pin 13 selected   */
#define GPIOPIN_14 	0x4000  /* Pin 14 selected   */
#define GPIOPIN_15 	0x8000  /* Pin 15 selected   */
#define GPIOPIN_All	0xFFFF  /* All pins selected */

#define GPIOSet     0x1U
#define GPIOReset   0x0U

#endif /* _GPIO_H_ */
