#include "Aura.h"
#include "SoundAnalysis.h"
#include "LedControl.h"
#include "VuMeter.h"

/**************************************************************/
/*                         PUBLIC DATA                        */
/**************************************************************/


/**************************************************************/
/*                         PRIVATE DATA                       */
/**************************************************************/

uint8_t Peak;
uint8_t DotCount;

/**************************************************************/
/*                        PUBLIC FUNCTIONS                    */
/**************************************************************/

void InitVuMeter()
{
	Peak 	 = 0x00;
	DotCount = 0x00;
}

void VuMeterSound()
{
	int soundLevel;
	int height;
	uint8_t i;
	uint16_t minLvl;
	uint16_t maxLvl;

	soundLevel = GetSoundLevel(&minLvl, &maxLvl);

	height = TOP * (soundLevel - minLvl) / (long)(maxLvl - minLvl);

	if (height < 0L)
	{
	    height = 0;
  	}
  	else if (height > TOP)
  	{
  		height = TOP;
  	}
  	if (height > Peak)
  	{
  		Peak = height;
  	}

  	for (i=0; i<HEIGHT; i++) 
  	{
	    if (i >= height)   
	    {
	      LedRunningInfo.leds[i + 0*HEIGHT].setRGB(0, 0, 0);
	      LedRunningInfo.leds[i + 2*HEIGHT].setRGB(0, 0, 0);
	      LedRunningInfo.leds[i + 4*HEIGHT].setRGB(0, 0, 0);
	      LedRunningInfo.leds[i + 6*HEIGHT].setRGB(0, 0, 0);
	      LedRunningInfo.leds[i + 8*HEIGHT].setRGB(0, 0, 0);
	    }
	    else
	    {
	      LedRunningInfo.leds[i + 0*HEIGHT] = CHSV(map(i, 0, HEIGHT - 1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
	      LedRunningInfo.leds[i + 2*HEIGHT] = CHSV(map(i, 0, HEIGHT - 1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
	      LedRunningInfo.leds[i + 4*HEIGHT] = CHSV(map(i, 0, HEIGHT - 1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
	      LedRunningInfo.leds[i + 6*HEIGHT] = CHSV(map(i, 0, HEIGHT - 1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
	      LedRunningInfo.leds[i + 8*HEIGHT] = CHSV(map(i, 0, HEIGHT - 1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
	    }
	}

	for(i=HEIGHT; i>0; i--)
	{
	    if ((HEIGHT - i) >= height)   
	    {
	      LedRunningInfo.leds[i + 1*HEIGHT].setRGB(0, 0, 0);
	      LedRunningInfo.leds[i + 3*HEIGHT].setRGB(0, 0, 0);
	      LedRunningInfo.leds[i + 5*HEIGHT].setRGB(0, 0, 0);
	      LedRunningInfo.leds[i + 7*HEIGHT].setRGB(0, 0, 0);
	      LedRunningInfo.leds[i + 9*HEIGHT].setRGB(0, 0, 0);
	    }
	    else
	    {
	      LedRunningInfo.leds[i + 1*HEIGHT] = CHSV(map(HEIGHT - i, 0, HEIGHT - 1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
	      LedRunningInfo.leds[i + 3*HEIGHT] = CHSV(map(HEIGHT - i, 0, HEIGHT - 1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
	      LedRunningInfo.leds[i + 5*HEIGHT] = CHSV(map(HEIGHT - i, 0, HEIGHT - 1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
	      LedRunningInfo.leds[i + 7*HEIGHT] = CHSV(map(HEIGHT - i, 0, HEIGHT - 1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
		  LedRunningInfo.leds[i + 9*HEIGHT] = CHSV(map(HEIGHT - i, 0, HEIGHT - 1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
	    }
	}

	if ((Peak > 3) && (Peak <= HEIGHT-1))
	{
		// One side
		LedRunningInfo.leds[Peak - 1] 				= CHSV(map(Peak, 0, HEIGHT-1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
		LedRunningInfo.leds[Peak + 2*HEIGHT] 		= CHSV(map(Peak, 0, HEIGHT-1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
		LedRunningInfo.leds[Peak - 1 +4*HEIGHT] 	= CHSV(map(Peak, 0, HEIGHT-1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
		// Other side
	  	LedRunningInfo.leds[Peak - 1 + 6*HEIGHT] 	= CHSV(map(Peak, 0, HEIGHT-1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
	  	LedRunningInfo.leds[Peak - 1 + 8*HEIGHT] 	= CHSV(map(Peak, 0, HEIGHT-1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
	}
	if (++DotCount >= PEAK_FALL) 
	{                            // fall rate 
      	if(Peak > 0) 
      	{
      		Peak--;
      	}
      DotCount = 0;
    }
}

void TryToReachTheTop()
{
	int soundLevel;
	int height;
	uint8_t i;
	uint16_t minLvl;
	uint16_t maxLvl;

	soundLevel = GetSoundLevel(&minLvl, &maxLvl);

	height = TOP * (soundLevel - minLvl) / (long)(maxLvl - minLvl);

	if (height < 0L)
	{
	    height = 0;
  	}
  	else if (height > TOP)
  	{
  		height = TOP;
  	}
  	if (height > Peak)
  	{
  		Peak = height;
  	}

  	for (i=0; i<HEIGHT; i++) 
  	{
	    if (i >= height)   
	    {
	      LedRunningInfo.leds[i + 0*HEIGHT].setRGB(0, 0, 0);
	      LedRunningInfo.leds[i + 2*HEIGHT].setRGB(0, 0, 0);
	      LedRunningInfo.leds[i + 4*HEIGHT].setRGB(0, 0, 0);
	      LedRunningInfo.leds[i + 6*HEIGHT].setRGB(0, 0, 0);
	      LedRunningInfo.leds[i + 8*HEIGHT].setRGB(0, 0, 0);
	    }
	    else
	    {
	      LedRunningInfo.leds[i + 0*HEIGHT] = CHSV(map(i, 0, HEIGHT - 1, LED_COLOR_CSV_DARK_PINK, LED_COLOR_CSV_LIGHT_PINK), SATURATION_MAX, BRIGHTNESS_MAX);
	      LedRunningInfo.leds[i + 2*HEIGHT] = CHSV(map(i, 0, HEIGHT - 1, LED_COLOR_CSV_DARK_PINK, LED_COLOR_CSV_LIGHT_PINK), SATURATION_MAX, BRIGHTNESS_MAX);
	      LedRunningInfo.leds[i + 4*HEIGHT] = CHSV(map(i, 0, HEIGHT - 1, LED_COLOR_CSV_DARK_PINK, LED_COLOR_CSV_LIGHT_PINK), SATURATION_MAX, BRIGHTNESS_MAX);
	      LedRunningInfo.leds[i + 6*HEIGHT] = CHSV(map(i, 0, HEIGHT - 1, LED_COLOR_CSV_DARK_PINK, LED_COLOR_CSV_LIGHT_PINK), SATURATION_MAX, BRIGHTNESS_MAX);
	      LedRunningInfo.leds[i + 8*HEIGHT] = CHSV(map(i, 0, HEIGHT - 1, LED_COLOR_CSV_DARK_PINK, LED_COLOR_CSV_LIGHT_PINK), SATURATION_MAX, BRIGHTNESS_MAX);
	    }
	}

	for(i=HEIGHT; i>0; i--)
	{
	    if ((HEIGHT - i) >= height)   
	    {
	      LedRunningInfo.leds[i + 1*HEIGHT].setRGB(0, 0, 0);
	      LedRunningInfo.leds[i + 3*HEIGHT].setRGB(0, 0, 0);
	      LedRunningInfo.leds[i + 5*HEIGHT].setRGB(0, 0, 0);
	      LedRunningInfo.leds[i + 7*HEIGHT].setRGB(0, 0, 0);
	      LedRunningInfo.leds[i + 9*HEIGHT].setRGB(0, 0, 0);
	    }
	    else
	    {
	      LedRunningInfo.leds[i + 1*HEIGHT] = CHSV(map(HEIGHT - i, 0, HEIGHT - 1, LED_COLOR_CSV_DARK_PINK, LED_COLOR_CSV_LIGHT_PINK), SATURATION_MAX, BRIGHTNESS_MAX);
	      LedRunningInfo.leds[i + 3*HEIGHT] = CHSV(map(HEIGHT - i, 0, HEIGHT - 1, LED_COLOR_CSV_DARK_PINK, LED_COLOR_CSV_LIGHT_PINK), SATURATION_MAX, BRIGHTNESS_MAX);
	      LedRunningInfo.leds[i + 5*HEIGHT] = CHSV(map(HEIGHT - i, 0, HEIGHT - 1, LED_COLOR_CSV_DARK_PINK, LED_COLOR_CSV_LIGHT_PINK), SATURATION_MAX, BRIGHTNESS_MAX);
	      LedRunningInfo.leds[i + 7*HEIGHT] = CHSV(map(HEIGHT - i, 0, HEIGHT - 1, LED_COLOR_CSV_DARK_PINK, LED_COLOR_CSV_LIGHT_PINK), SATURATION_MAX, BRIGHTNESS_MAX);
	      LedRunningInfo.leds[i + 9*HEIGHT] = CHSV(map(HEIGHT - i, 0, HEIGHT - 1, LED_COLOR_CSV_DARK_PINK, LED_COLOR_CSV_LIGHT_PINK), SATURATION_MAX, BRIGHTNESS_MAX);
	    }
	}

	if ((Peak > 3) && (Peak <= HEIGHT-1))
	{
		// One side
		LedRunningInfo.leds[Peak - 1] 				   = CHSV(map(Peak, 0, HEIGHT-1, LED_COLOR_CSV_DARK_PINK, LED_COLOR_CSV_LIGHT_PINK), SATURATION_MAX, BRIGHTNESS_MAX);
		LedRunningInfo.leds[Peak + 2*HEIGHT] 		 = CHSV(map(Peak, 0, HEIGHT-1, LED_COLOR_CSV_DARK_PINK, LED_COLOR_CSV_LIGHT_PINK), SATURATION_MAX, BRIGHTNESS_MAX);
		LedRunningInfo.leds[Peak - 1 +4*HEIGHT]  = CHSV(map(Peak, 0, HEIGHT-1, LED_COLOR_CSV_DARK_PINK, LED_COLOR_CSV_LIGHT_PINK), SATURATION_MAX, BRIGHTNESS_MAX);
		// Other side
	  LedRunningInfo.leds[Peak - 1 + 6*HEIGHT] = CHSV(map(Peak, 0, HEIGHT-1, LED_COLOR_CSV_DARK_PINK, LED_COLOR_CSV_LIGHT_PINK), SATURATION_MAX, BRIGHTNESS_MAX);
	  LedRunningInfo.leds[Peak - 1 + 8*HEIGHT] = CHSV(map(Peak, 0, HEIGHT-1, LED_COLOR_CSV_DARK_PINK, LED_COLOR_CSV_LIGHT_PINK), SATURATION_MAX, BRIGHTNESS_MAX);
	}
	if (++DotCount >= PEAK_FALL) 
	{                            // fall rate 
      	if(Peak > 0) 
      	{
      		Peak--;
      	}
      	DotCount = 0;
    }
}

// TODO AP 
void VuMeterFrequency(int *soundMeasure)
{
  int i, j;
  int top[WIDTH_PER_FACE] = {0x00, 0x00, 0x00, 0x00, 0x00};

/*  top[0] = ((soundMeasure[0] + soundMeasure[1]) >> 1) / 32;
  top[1] = ((soundMeasure[2] + soundMeasure[3]) >> 1) / 32;
  top[3] = ((soundMeasure[4] + soundMeasure[5]) >> 1) / 32;
  top[4] = ((soundMeasure[6] + soundMeasure[7]) >> 1) / 32;
  top[2] = (top[1] + top[3]) >> 1;
*/
/*  top[0] = soundMeasure[3] / 32;
  top[1] = soundMeasure[4] / 32;
  top[2] = soundMeasure[5] / 32;
  top[3] = soundMeasure[6] / 32;
  top[4] = soundMeasure[7] / 32;*/

/*  for(i = 5; i < 55; i++)
  {
  	top[0] += soundMeasure[i];
  	top[1] += soundMeasure[i + 1 * 55];
  	top[2] += soundMeasure[i + 2 * 55];
  	top[3] += soundMeasure[i + 3 * 55];
  	top[4] += soundMeasure[i + 4 * 55];
  }*/

  for(i = 0; i < 12; i++)
  {
  	top[0] += soundMeasure[i];
  	top[1] += soundMeasure[i + 1 * 12];
  	top[2] += soundMeasure[i + 2 * 12];
  	top[3] += soundMeasure[i + 3 * 12];
  	top[4] += soundMeasure[i + 4 * 12];
  }
  top[0] /= 12;
  top[1] /= 12;
  top[2] /= 12;
  top[3] /= 12;
  top[4] /= 12;
/*
  top[0] /= 8;
  top[1] /= 8;
  top[2] /= 8;
  top[3] /= 8;
  top[4] /= 8;*/

  #if DEBUG == 1
  for(i = 0; i < 128; i++)
  {
    Serial.print("Sound Mesure ");
    Serial.print(i);
    Serial.print(" = ");
    //Serial.println(soundMeasure[i]);
  }
  //Serial.println();
  for(i = 0; i < WIDTH_PER_FACE; i++)
  {
    Serial.print("Top de");
    Serial.print(i);
    Serial.print(" = ");
    //Serial.println(top[i]);
  }
  #endif

  for(i = 0; i < HEIGHT; i++)
  {
  	for(j = 0; j < WIDTH_PER_FACE; j++)
  	{
	    if(i > top[j])
	    {  
/*	      LedRunningInfo.leds[i+0*HEIGHT].setRGB(0, 0, 0);
	      LedRunningInfo.leds[i+2*HEIGHT].setRGB(0, 0, 0);
	      LedRunningInfo.leds[i+4*HEIGHT].setRGB(0, 0, 0);
	      LedRunningInfo.leds[i+6*HEIGHT].setRGB(0, 0, 0);
	      LedRunningInfo.leds[i+8*HEIGHT].setRGB(0, 0, 0);
*/	      LedRunningInfo.leds[i+2*j*HEIGHT].setRGB(0, 0, 0);
	    }
	    else
	    {
	      LedRunningInfo.leds[i+2*j*HEIGHT] = CHSV(map(i, 0, HEIGHT-1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
	    }
	}
  }

  for(i = HEIGHT; i > 0; i--)
  {
  	for(j = 0; j < WIDTH_PER_FACE; j++)
  	{
	    if ((HEIGHT - i) >= top[j])   
	    {
/*	      LedRunningInfo.leds[i+1*HEIGHT].setRGB( 0, 0,0);
	      LedRunningInfo.leds[i+3*HEIGHT].setRGB( 0, 0,0);
	      LedRunningInfo.leds[i+5*HEIGHT].setRGB( 0, 0,0);
	      LedRunningInfo.leds[i+7*HEIGHT].setRGB( 0, 0,0);
	      LedRunningInfo.leds[i+9*HEIGHT].setRGB( 0, 0,0);*/
	      LedRunningInfo.leds[i+(2*j+1)*HEIGHT].setRGB(0, 0, 0);
	    }
	    else
	    {
/*	      LedRunningInfo.leds[i+1*HEIGHT] = CHSV(map(HEIGHT - i,0,HEIGHT-1,LED_COLOR_CSV_RED,LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
	      LedRunningInfo.leds[i+3*HEIGHT] = CHSV(map(HEIGHT - i,0,HEIGHT-1,LED_COLOR_CSV_RED,LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
	      LedRunningInfo.leds[i+5*HEIGHT] = CHSV(map(HEIGHT - i,0,HEIGHT-1,LED_COLOR_CSV_RED,LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
	      LedRunningInfo.leds[i+7*HEIGHT] = CHSV(map(HEIGHT - i,0,HEIGHT-1,LED_COLOR_CSV_RED,LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
	      LedRunningInfo.leds[i+9*HEIGHT] = CHSV(map(HEIGHT - i,0,HEIGHT-1,LED_COLOR_CSV_RED,LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);*/
	      LedRunningInfo.leds[i+(2*j+1)*HEIGHT] = CHSV(map(HEIGHT - i,0,HEIGHT-1,LED_COLOR_CSV_RED,LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
	    }
	}
  }
}

void VuMeterLedsTest(int value)
{
  int i;
/*  for(i = 0; i < 8; i++)
  {
    Serial.print("Sound Mesure ");
    Serial.print(i);
    Serial.print(" = ");
    //Serial.println(soundMeasure[i]);
  }
  //Serial.println();
  for(i = 0; i < WIDTH_PER_FACE; i++)
  {
    Serial.print("Top de");
    Serial.print(i);
    Serial.print(" = ");
    //Serial.println(top[i]);
  }*/
  for(i = 0; i < HEIGHT; i++)
  {
    if(i > value)
    {  
      LedRunningInfo.leds[i+0*HEIGHT].setRGB(0, 0, 0);
      LedRunningInfo.leds[i+2*HEIGHT].setRGB(0, 0, 0);
      LedRunningInfo.leds[i+4*HEIGHT].setRGB(0, 0, 0);
      LedRunningInfo.leds[i+6*HEIGHT].setRGB(0, 0, 0);
      LedRunningInfo.leds[i+8*HEIGHT].setRGB(0, 0, 0);
    }
    else
    {
      LedRunningInfo.leds[i+0*HEIGHT] = CHSV(map(i, 0, HEIGHT-1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
      LedRunningInfo.leds[i+2*HEIGHT] = CHSV(map(i, 0, HEIGHT-1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
      LedRunningInfo.leds[i+4*HEIGHT] = CHSV(map(i, 0, HEIGHT-1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
      LedRunningInfo.leds[i+6*HEIGHT] = CHSV(map(i, 0, HEIGHT-1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
      LedRunningInfo.leds[i+8*HEIGHT] = CHSV(map(i, 0, HEIGHT-1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
    }
  }

  for(i = HEIGHT; i > 0; i--)
  {
    if ((HEIGHT - i) >= value)   
    {
      LedRunningInfo.leds[i+1*HEIGHT].setRGB(0, 0, 0);
      LedRunningInfo.leds[i+3*HEIGHT].setRGB(0, 0, 0);
      LedRunningInfo.leds[i+5*HEIGHT].setRGB(0, 0, 0);
      LedRunningInfo.leds[i+7*HEIGHT].setRGB(0, 0, 0);
      LedRunningInfo.leds[i+9*HEIGHT].setRGB(0, 0, 0);
    }
    else
    {
      LedRunningInfo.leds[i+1*HEIGHT] = CHSV(map(HEIGHT - i, 0, HEIGHT - 1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
      LedRunningInfo.leds[i+3*HEIGHT] = CHSV(map(HEIGHT - i, 0, HEIGHT - 1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
      LedRunningInfo.leds[i+5*HEIGHT] = CHSV(map(HEIGHT - i, 0, HEIGHT - 1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
      LedRunningInfo.leds[i+7*HEIGHT] = CHSV(map(HEIGHT - i, 0, HEIGHT - 1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
      LedRunningInfo.leds[i+9*HEIGHT] = CHSV(map(HEIGHT - i, 0, HEIGHT - 1, LED_COLOR_CSV_RED, LED_COLOR_CSV_CYAN), SATURATION_MAX, BRIGHTNESS_MAX);
    }
  }
}

/**************************************************************/
/*                        PRIVATE FUNCTIONS                   */
/**************************************************************/