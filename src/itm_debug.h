/*
 * itm_debug.h
 *
 *  Created on: Apr 17, 2021
 *      Author: danielbraun
 */

#ifndef UTILS_ITM_DEBUG_H_
#define UTILS_ITM_DEBUG_H_

#define USE_ITM 0
#if USE_ITM
extern uint32_t debug_flags;

#define DBG_TIM  	(1UL<<0)
#define DBG_MSG		(1UL<<1)
#define DBG_SIG		(1UL<<2)


#define DBG_ERR		(1UL<<31)


/*
 * inline func for debug msg using ITM macrocell (SWO output)
 * messages shall be very short (12 chars) to limit stack usage and SWO bandwidth
 * (SWO async traces are supposed to have a light overweight (compared to uart or usb) but....
 * using traces in IRQ is possible, but the amount of msg shall be strictly limited
 */

void _itm_debug3(int err, const char *msg, int32_t v1, int32_t v2, int32_t v3, int n);


static inline void itm_debug1(uint32_t f, const char *msg, int32_t v)
{
	if (f & debug_flags) _itm_debug3(f & DBG_ERR, msg, v, 0, 0, 1);
}
static inline void itm_debug2(uint32_t f, const char *msg, int32_t v1, int32_t v2)
{
	if (f & debug_flags) _itm_debug3(f & DBG_ERR, msg, v1, v2, 0, 2);
}
static inline void itm_debug3(uint32_t f, const char *msg, int32_t v1, int32_t v2, int32_t v3)
{
	if (f & debug_flags) _itm_debug3(f & DBG_ERR, msg, v1, v2, v3, 3);
}


void itm_write(const char *str, int len);

#ifdef TRAIN_SIMU
char* itoa ( int32_t  value,  char str[],  int radix);
#endif

#else //0


#define itm_debug1(_f, _m, _v1) do {} while(0)
#define itm_debug2(_f, _m, _v1, _v2) do {} while(0)
#define itm_debug3(_f, _m, _v1, _v2, _v3) do {} while(0)

#endif //0


#endif /* UTILS_ITM_DEBUG_H_ */
