/*
* @Author: Alexis Lutun
* @Date:   2016-05-14 13:32:38
* @Last Modified by:   Alexis Polegato
* @Last Modified time: 2016-06-04 15:55:43
*/

#include "Arduino.h"
#include "Aura.h"
#include "SoundAnalysis.h"
#include "WaterEffect.h"

#include "SwitchMode.h"

/**************************************************************/
/*                         PUBLIC DATA                        */
/**************************************************************/

/**************************************************************/
/*                         PRIVATE DATA                       */
/**************************************************************/

uint8_t CurrentMode;
uint8_t LowSoundTimingCounter;
uint8_t PeakSoundTimingCounter;
uint8_t PeakCounter;

/**************************************************************/
/*                         PUBLIC FUNCTIONS                   */
/**************************************************************/

void SwitchModeInit()
{
	LowSoundTimingCounter  = TIMER_COUNTER_INIT;
	PeakSoundTimingCounter = TIMER_COUNTER_INIT;
	PeakCounter 		   = PEAK_COUNTER_INIT;
	CurrentMode 	  	   = MODE_NORMAL;
}

uint8_t SwitchModeFromBeat(uint8_t beatCount)
{
	if(beatCount < BEAT_COUNT_LOW_LIMIT)
	{
		LowSoundTimingCounter++;
		if(LowSoundTimingCounter == LOW_SOUND_TIMER_COUNTER_TIMEOUT)
		{
			LowSoundTimingCounter = TIMER_COUNTER_INIT;
			CurrentMode = MODE_NORMAL;
			return (SWITCH_MODE_OK);
		}
	}
	else
	{
		LowSoundTimingCounter = TIMER_COUNTER_INIT;
		CurrentMode = MODE_PARTY;
	}
	return (SWITCH_MODE_NOK);
}

uint8_t SwitchModeFromNormal(uint8_t beatCount)
{
	PeakSoundTimingCounter++;
	if(beatCount > BEAT_COUNT_LIMIT_TO_SWITCH)
	{
		PeakCounter++;
	}
	if(PeakSoundTimingCounter == PEAK_SOUND_TIMER_COUNTER_TIMEOUT_1)
	{
		if(PeakCounter == PEAK_COUNTER_THRESHOLD_1)
		{
			PeakSoundTimingCounter++;
		}
		else if(PeakCounter >= PEAK_COUNTER_THRESHOLD_2)
		{
			SwitchToNewMode(MODE_PARTY);
			return (SWITCH_MODE_OK);
		}
		else
		{
			SwitchModeResetValue();
		}
	}
	if(PeakSoundTimingCounter == PEAK_SOUND_TIMER_COUNTER_TIMEOUT_2)
	{
		if(PeakCounter >= PEAK_COUNTER_THRESHOLD_2)
		{
			SwitchToNewMode(MODE_PARTY);
			return (SWITCH_MODE_OK);
		}
		else
		{
			SwitchModeResetValue();
		}
	}
	CurrentMode = MODE_NORMAL;

	return (SWITCH_MODE_NOK);
}

uint8_t GetCurrentMode()
{
	return(CurrentMode);
}

void SetCurrentMode(uint8_t mode)
{
	CurrentMode = mode;
}

/**************************************************************/
/*                         PRIVATE FUNCTIONS                  */
/**************************************************************/

static void SwitchModeResetValue()
{
	LowSoundTimingCounter  = TIMER_COUNTER_INIT;
	PeakSoundTimingCounter = TIMER_COUNTER_INIT;
	PeakCounter 		   = PEAK_COUNTER_INIT;
}


static void SwitchToNewMode(uint8_t newMode)
{
	SwitchModeResetValue();
	CurrentMode = newMode;
}
