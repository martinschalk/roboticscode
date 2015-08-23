/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#ifndef GLOBAL_H
#define GLOBAL_H

#include <project.h>


//#define TEST_UART


#if (defined(__C51__))
	#define BIG_ENDIAN
	// 0x1A2B3C4D =  1A 2B 3C 4D 
#else /* PSoC 5 */
	#define LITTLE_ENDIAN
	// 0x1A2B3C4D =  4D 3C 2B 1A
	#define lowByte(x) ((uint8)(x))
	#define highByte(x) ((uint8)(x<<1))
#endif


#define NULLPTR ((void *)0)
#define SIZE_OF_ARRAY(x)  (sizeof(x) / sizeof(x[0]))
#define SUCCESS	0
#define BIT(b) (1UL << (b))
#define TRUE 0x1
#define FALSE 0x0
#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105

#endif /* GLOBAL_H */

