#include "Arduino.h"
#include "BackgroundLed.h"
#include "Aura.h"
#include "SoundAnalysis.h"
#include "LedControl.h"
#include "WaterEffect.h"
#include "BeatMode.h"
#include "VuMeter.h"
#include "SwitchMode.h"

void setup() 
{
  InitSoundAnalysis();
  InitLeds();
  InitVuMeter();
  SwitchModeInit();
  SetupWaterEffect();
  #if DEBUG == 1
  Serial.begin(57600);
  #endif
}


void loop() 
{
	int SoundMeasure[FHT_SAMPLE_NUMBER];
	uint8_t mode;
	uint8_t beatCounter;

	while(1)
	{
		EVERY_N_MILLISECONDS(20)
		{
			mode = GetCurrentMode();
			ProcessSoundAnalysisTable(SoundMeasure);

			switch (mode) 
 	 		{
 	 		    case MODE_NORMAL:
 	 		    	/* Choose the effect you want:
 	 		    	 * - RunWaterEffect();
 	 		    	 * - RunWaterEffectWithColor(LED_COLOR_CSV_PINK);
 	 		    	 * - BackgroundMode(BACKGROUND_RED);
 	 		    	 * - BackgroundModePerFace(BACKGROUND_RED, BACKGROUND_GREEN);
 	 		    	 */
 	 		    	RunWaterEffect();
 	 		    	beatCounter = SwitchingBeatModeWithCount(SoundMeasure);
					SwitchModeFromNormal(beatCounter);
 	 		    break;
 	 		    
 	 		    case MODE_PARTY:
					/* Choose the effect you want:
 	 		    	 * - ColorBeatModeWithCount(SoundMeasure);
 	 		    	 */
					beatCounter = RandomBeatModeWithCount(SoundMeasure);		
					SwitchModeFromBeat(beatCounter);
 	 		    break;
		 	}
		}
		PowerLeds();
	}
}
