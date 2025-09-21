/*
 * sequencer.h
 *
 *  Created on: Sep 20, 2025
 *      Author: francois
 */

#ifndef INC_SEQUENCER_H_
#define INC_SEQUENCER_H_

#include "stm32f4xx_hal.h"

#define GPIO_PIN_ADC1 1
#define GPIO_PIN_DAC1 2
#define GPIO_PIN_ADC2 3
#define GPIO_PIN_DAC2 4

#define GPIO_PIN_ROTA 5
#define GPIO_PIN_ROTB 6
#define GPIO_PORT_ROTB GPIOA
#define GPIO_PIN_SWITCH 7
#define GPIO_PIN_ROTSWITCH 8

typedef enum {
	PLAY, EDIT
} Mode;

typedef enum {
	TRUE, FALSE
} Bool;

static Mode currentMode = PLAY;
static int currentStep = 0;
static Bool updateBPM = FALSE;
static int BPM = 80;

static float stepValues[8];
static float envelope;

void play(void);

void edit(void);

void onTimerInterruption(TIM_HandleTypeDef *htim);

void onExternalInterruption(uint16_t pin);

void changeBPM(uint16_t ROTB);

void resetEnvelope(void);

float readADC(uint16_t pin);

void writeDAC(float value, uint16_t);

void Seq_Error_Handler(void);

#endif /* INC_SEQUENCER_H_ */
