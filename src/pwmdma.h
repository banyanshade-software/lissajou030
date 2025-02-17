/*
 * pwmdma.h
 *
 *  Created on: Jan 9, 2025
 *      Author: danielbraun
 */

#ifndef PWMDMA_H_
#define PWMDMA_H_


/// timer interrupt handler
/// (called from main.c), every TIM1 overflow (50kHz)
void pwm_tim_it(void);

/// default task body
/// currently only perform init, then everything is done in interrupt handler
/// @param argument unused
void sigGenTask(void const * argument);

#endif /* PWMDMA_H_ */
