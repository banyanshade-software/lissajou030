/*
 * itm_debug.c
 *
 *  Created on: Apr 17, 2021
 *      Author: danielbraun
 */


// ITM helpers
// -------------------------------------------------------------------------

#include <stdint.h>
#include <memory.h>
#include <stdlib.h>


#include "itm_debug.h"
#include "misc.h"

#if USE_ITM
#include "stm32g4xx.h"


/* debug flags */
uint32_t debug_flags = DBG_ERR|  DBG_TIM;


#define DBG_
#ifdef TRAIN_SIMU
char* itoa ( int32_t  value,  char str[],  int radix)
{
    char        buf [66];
    char*       dest = buf + sizeof(buf);
    int8_t     sign = 0;

    if (value == 0) {
        memcpy (str, "0", 2);
        return str;
    }

#if 0
    if (radix < 0) {
        radix = -radix;
        if (value < 0) {
            value = -value;
            sign = 1;
        }
    }
#else
    if (value < 0) {
        sign = 1;
        value = -value;
    }
#endif

    *--dest = '\0';

    switch (radix)
    {
    case 16:
        while (value) {
            * --dest = '0' + (value & 0xF);
            if (*dest > '9') *dest += 'A' - '9' - 1;
            value >>= 4;
        }
        break;
    case 10:
        while (value) {
            *--dest = '0' + (value % 10);
            value /= 10;
        }
        break;

    case 8:
        while (value) {
            *--dest = '0' + (value & 7);
            value >>= 3;
        }
        break;

    case 2:
        while (value) {
            *--dest = '0' + (value & 1);
            value >>= 1;
        }
        break;

    default:            // The slow version, but universal
        while (value) {
            *--dest = '0' + (value % radix);
            if (*dest > '9') *dest += 'A' - '9' - 1;
            value /= radix;
        }
        break;
    }

    if (sign) *--dest = '-';

    memcpy (str, dest, buf +sizeof(buf) - dest);
    return str;
}
#endif





static void write_num(char *buf, uint32_t v, int ndigit)
{
	for (;ndigit>0; ndigit--) {
		buf[ndigit-1] = '0'+ (v % 10);
		v = v/10;
	}
}
#if 0
#ifndef TRAIN_SIMU
int _write(_UNUSED_ int32_t file, uint8_t *ptr, int32_t len)
{
	for (int i = 0; i < len; i++)
	{
		ITM_SendChar(*ptr++);
	}
	return len;
}
#endif
#endif

static inline void mywrite(const char *ptr, int32_t len)
{
#ifndef TRAIN_SIMU
	for (int i = 0; i < len; i++)
	{
		ITM_SendChar(*ptr++);
	}
#else
    ssize_t  write(int fildes, const void *buf, size_t nbyte);
    write(1, ptr, len);
#endif
}

// itm_write : simply a public wrapper for mywrite
void itm_write(const char *str, int len)
{
	mywrite(str, len);
}



/*
 * before: StartCtrlTask max 858
 */

void _itm_debug3(int err, const char *msg, int32_t v1, int32_t v2, int32_t v3, int n)
{
	char buf[12];
	memset(buf, 0, sizeof(buf));
    uint32_t tck = HAL_GetTick();
	write_num(buf, tck, 7);
	buf[7] = err ? '@' : ':';
	mywrite(buf, 8);
	int l = MIN(12, (int)strlen(msg));
	mywrite(msg, l);
	if (!n--) goto done;

	buf[0] = '/';
	itoa(v1, buf+1, 10);
    l = MIN(12, (int)strlen(buf));
    mywrite(buf, l);
	if (!n--) goto done;

	buf[0] = '/';
	itoa(v2, buf+1, 10);
    l = MIN(12, (int)strlen(buf));
    mywrite(buf, l);
	if (!n--) goto done;

	buf[0] = '/';
	itoa(v3, buf+1, 10);
    l = MIN(12, (int)strlen(buf));
    mywrite(buf, l);
	if (!n--) goto done;

done:
	mywrite("\n", 1);
}


#endif
