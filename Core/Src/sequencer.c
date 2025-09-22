/*
 * sequencer.c
 *
 *  Created on: Sep 20, 2025
 *      Author: francois
 */

#include "sequencer.h"

void play()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	do {

	} while(currentMode == PLAY);
	edit();
}

void edit()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	do {

	} while(currentMode == EDIT);
	play();
}

void onTimerInterruption(TIM_HandleTypeDef *htim)
{

	if(currentMode == PLAY) {
		++currentStep;
	}
	resetEnvelope();

	if(updateBPM == TRUE)
	{
		htim->Init.Period = (1965679/BPM)-1;
		if (HAL_TIM_Base_Init(htim) != HAL_OK)
		{
			Seq_Error_Handler();
		}
		HAL_TIM_Base_Start_IT(htim);
		updateBPM = FALSE;
	}
}

void onExternalInterruption(uint16_t pin)
{
	switch(pin) {

	case GPIO_PIN_10: // ROTSWITCH : CHANGE MODE
		if(currentMode == PLAY) {
			currentMode = EDIT;
		}
		else {
			currentMode = PLAY;
		}
	break;

	case GPIO_PIN_ROTA: // ROTA : CHANGE BPM
		changeBPM(GPIO_PIN_ROTB);
	break;

	case GPIO_PIN_8: // SW : CHANGE STEP WHEN EDITING
		if(currentMode == EDIT) {
			++currentStep;
			currentStep %= 8;
		}
	break;
	}
}

void changeBPM(uint16_t ROTB)
{
	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_ROTB) && BPM < 300) {
		++BPM;
		updateBPM = TRUE;
	}
	else if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_ROTB) && BPM > 30) {
		--BPM;
		updateBPM = TRUE;
	}

}

void writeDAC(float value, uint16_t)
{

}

void updateSequencerValues(uint32_t *buffer)
{
	envelope = buffer[1];
	if (currentMode == EDIT) {
		stepValues[currentStep] = buffer[0];
	}
}

void Seq_Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
  /* USER CODE END Error_Handler_Debug */
}
