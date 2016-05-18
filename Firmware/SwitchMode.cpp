/*
* @Author: Alexis Lutun
* @Date:   2016-05-14 13:32:38
* @Last Modified by:   Alexis Lutun
* @Last Modified time: 2016-05-14 23:52:21
*/

#include "Arduino.h"
#include "Aura.h"
#include "SoundAnalysis.h"
#include "WaterEffect.h"

#include "SwitchMode.h"

/**************************************************************/
/*                         PUBLIC DATA                        */
/**************************************************************/

switchInfo_s switchInfo;
	
/**************************************************************/
/*                         PRIVATE DATA                       */
/**************************************************************/

/**************************************************************/
/*                         PUBLIC FUNCTIONS                   */
/**************************************************************/

void SwitchModeInit()
{
	switchInfo.timerSecond           = TIMER_ONE_SECOND_RESET;  
	switchInfo.timerMs               = TIMER_MS_RESET;  
	switchInfo.currentMode           = MODE_NORMAL;
	switchInfo.currentSoundState     = SOUND_NORMAL_STATE;
	switchInfo.timerSecondSoundLevel = TIMER_ONE_SECOND_RESET;
}

void SwitchModeTick()
{
	short  	trash;
	char 	valueSound;

		if (updateTimer() == 1)
		{
			// Serial.println("NUMBER OF SAMPLE IS : ");	
			// Serial.println((int)switchInfo.sampleNumber);
			// Serial.println("SUM IS : ");	
			// Serial.println(switchInfo.totalSampleValue);
			checkIfModeShouldSwitch();
			resetSoundValue();
	}
	 	else
		{
	 		valueSound = GetSoundLevel((uint16_t*)&trash, (uint16_t*)&trash);
				if (valueSound != 0)
				{		
					switchInfo.sampleNumber += 0x01;
					switchInfo.totalSampleValue += valueSound;
				}
	 	}
}


char getActualMode()
{
	return(switchInfo.currentMode);	
}
/**************************************************************/
/*                         PRIVATE FUNCTIONS                  */
/**************************************************************/

static void resetSoundValue()
{
	switchInfo.sampleNumber = 0x00;
	switchInfo.totalSampleValue = 0x00;
}

static void switchToNewMode(char newMode)
{
	if (switchInfo.currentMode != newMode)
	{
		if (newMode == MODE_NORMAL)
		{
			SetupWaterEffect();
		}				
		else if (newMode == MODE_PARTY)
		{				
			//init party mode
		}	
		switchInfo.timerSecondSoundLevel = TIMER_ONE_SECOND_RESET;
		switchInfo.currentMode           = newMode;
	}	
}

static void checkIfModeShouldSwitch()
{
	if (switchInfo.sampleNumber >= HALF_SAMPLE_MAX_NUMBER && switchInfo.totalSampleValue >= MIN_TOTAL_NUMBER)
	{
		#if DEBUG == 1
		Serial.println("PARTY");
		#endif	
		switchToNewMode(MODE_PARTY);
	}	
	else
	{
		#if DEBUG == 1
		Serial.println("QUIET");
		#endif
		SetupWaterEffect();
		switchToNewMode(MODE_NORMAL);
	}	
}	
static char updateTimer()
{
  	switchInfo.timerMs += 0x01;
  	if (switchInfo.timerMs > TIMER_MS_ONE_SECOND)
	{
		switchInfo.timerMs = TIMER_MS_RESET;
		switchInfo.timerSecond += TIMER_ONE_SECOND;
		return (0);
	}
	if (switchInfo.timerSecond == TIMER_THRITY_SECOND)
	{
		switchInfo.timerSecond = TIMER_ONE_SECOND_RESET;
		return (1);
	}
	else
	{
		return (0);
	}
}
