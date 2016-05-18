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

	while(1)
	{
		EVERY_N_MILLISECONDS(20)
		{
			SwitchModeTick();
			mode = getActualMode();
			switch (mode) 
 	 		{
 	 		    case MODE_NORMAL:
 	 		    	RunWaterEffect();

 	 		    	/* Others Modes */
 	 		    	//RunWaterEffectWithColor(LED_COLOR_CSV_PINK);
 	 		    	//BackgroundMode(BACKGROUND_RED);
 	 		    break;
 	 		    
 	 		    case MODE_PARTY:
 	 		     	ProcessSoundAnalysisTable(SoundMeasure);
					RandomBeatMode(SoundMeasure);		
					
					/* Others Modes */
					//ColorBeatMode(SoundMeasure);		
					//VuMeterSound();
 	 		    break;
		 	}
		}
		PowerLeds();
	}
}
