/*
 * misc.h
 *
 *  Created on: Sep 14, 2020
 *      Author: danielbraun
 */

/*
 * (c) Daniel Braun 2020
 * ---------------------
 * available under GPLv3 http://www.gnu.org/licenses/gpl-3.0.html
 *
 */

#ifndef TRAINCTL_MISC_H_
#define TRAINCTL_MISC_H_

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#define _UNUSED_ __attribute__((unused))






#define SIGNOF(_v) (((_v)<0) ? -1 : 1)
#define SIGNOF0(_v) (((_v)<0) ? -1 : (((_v)>0) ? 1 : 0))

static inline int signof0(int v)
{
    if (v>0) return 1;
    if (v<0) return -1;
    return 0;
}

#ifndef MIN
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#endif

/* ================================================================= */

/* ================================================================= */



#if 0

// useful everywhere for profiling and logging, even
// in files that do not need to include HAL

uint32_t HAL_GetTick(void);
/
static inline uint32_t GetCurrentMicro(void)
{
  uint32_t m0 = HAL_GetTick();
  uint32_t u0 = SysTick->LOAD - SysTick->VAL;
  uint32_t m1 = HAL_GetTick();
  uint32_t u1 = SysTick->LOAD - SysTick->VAL;

  if (!SysTick->LOAD) return m0*1000;

  if (m1 > m0) {
    return ( m1 * 1000 + (u1 * 1000) / SysTick->LOAD);
  } else {
    return ( m0 * 1000 + (u0 * 1000) / SysTick->LOAD);
  }
}
#endif

void long_isr(uint32_t dur);


//
// https://electronics.stackexchange.com/questions/76098/high-resolution-system-timer-in-stm32
//
uint64_t GetCycleCount64(void);
void startCycleCounter(void);


#if 0
#define BEGIN_ISR \
	volatile uint32_t isr_tm0 = GetCurrentMicro();

#define END_ISR do { \
	uint32_t isr_tm1 = GetCurrentMicro(); \
	if (isr_tm1 - isr_tm0 > 1000) { long_isr(isr_tm1-isr_tm0); } \
} while (0)
#else

#define BEGIN_ISR \
	volatile uint64_t isr_tm0 = GetCycleCount64();

#define END_ISR do { \
		uint64_t isr_tm1 = GetCycleCount64(); \
	if (isr_tm1 - isr_tm0 > 48000) { long_isr(isr_tm1-isr_tm0); } \
} while (0)

/* 96MHz : 1ms = 96000 cycles
 * long = 500us 48000 cycles */
#endif

// ---------------------------------------------
extern int tsktick_freqhz;	// freq (derived from pwm freq) where most tasklet (ctrl) are called






#endif /* TRAINCTL_MISC_H_ */
