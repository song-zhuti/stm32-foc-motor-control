#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdint.h>
#include <stdio.h>

#define CLAMP(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))
#define PI        3.1415926f
#define TWO_PI    6.2831852f      // 2¦Ð
#define PI_2      1.5707963f      // ¦Ð/2
#define PI_3      1.0471976f      // ¦Ð/3
#define TWO_PI_3  2.0943952f      // 2¦Ð/3
#define FOUR_PI_3 4.1887903f      // 4¦Ð/3

extern volatile uint32_t Tim3_tick;

#endif /* __MAIN_H__ */
