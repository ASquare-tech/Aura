#include "SoundAnalysis.h"
#include "LedControl.h"
#include "BeatMode.h"

//#include <FHT.h>

/**************************************************************/
/*                         PUBLIC DATA                        */
/**************************************************************/


/**************************************************************/
/*                         PRIVATE DATA                       */
/**************************************************************/

static uint8_t Color;

/**************************************************************/
/*                        PUBLIC FUNCTIONS                    */
/**************************************************************/

uint8_t SwitchingBeatModeWithCount(int *sound)
{
    uint8_t i;
    uint8_t beat;
    uint8_t newColor;
    uint8_t beatCounter;
    uint8_t newBrightness;

    beatCounter = 0;
    Color++;
    for(i = 0; i < NUM_LEDS_PER_FACE; i++) 
    {                               
        beat = U_SUB(sound[i+BEAT_MODE_FREQUENCY_OFFSET], BEAT_MODE_NOISE_VALUE);    // Removing Noise, but keep > 0     

        if (beat > BEAT_COUTER_THRESHOLD)
        {
            beatCounter++;    
        }                                
    }
    return (beatCounter);
}

void RandomBeatMode(int *sound)
{
	uint8_t i;
    uint8_t beat;
    uint8_t newColor;
    uint8_t newBrightness;

	Color++;
	for( i= 0; i < NUM_LEDS_PER_FACE; i++) 
	{                               
     	beat = U_SUB(sound[i+BEAT_MODE_FREQUENCY_OFFSET], BEAT_MODE_NOISE_VALUE);    // Removing Noise, but keep > 0     

        if (beat > (LedRunningInfo.leds[i].r + LedRunningInfo.leds[i].g + LedRunningInfo.leds[i].b))           // Refresh an LED only when the intensity is low
    	{    
            newColor      = beat * COLOR_FACTOR + Color;         // Get a Random Color for current leds[i]
            newBrightness = beat * BRIGHTNESS_FACTOR;            // Higher the Beat => Higher the brightness
            LedRunningInfo.leds[i]                   = CHSV(newColor, SATURATION_MAX, newBrightness);
            LedRunningInfo.leds[i+NUM_LEDS_PER_FACE] = CHSV(newColor, SATURATION_MAX, newBrightness);
        }
        LedRunningInfo.leds[i].nscale8(224);                                     
    	LedRunningInfo.leds[i+NUM_LEDS_PER_FACE].nscale8(224);                                     
    }
}

uint8_t RandomBeatModeWithCount(int *sound)
{
    uint8_t i;
    uint8_t beat;
    uint8_t newColor;
    uint8_t beatCounter;
    uint8_t newBrightness;

    beatCounter = 0;
    Color++;
    for( i= 0; i < NUM_LEDS_PER_FACE; i++) 
    {                               
        beat = U_SUB(sound[i+BEAT_MODE_FREQUENCY_OFFSET], BEAT_MODE_NOISE_VALUE);    // Removing Noise, but keep > 0     

        if (beat > (LedRunningInfo.leds[i].r + LedRunningInfo.leds[i].g + LedRunningInfo.leds[i].b))           // Refresh an LED only when the intensity is low
        {
            beatCounter++;    
            newColor      = beat * COLOR_FACTOR + Color;         // Get a Random Color for current leds[i]
            newBrightness = beat * BRIGHTNESS_FACTOR;            // Higher the Beat => Higher the brightness
            LedRunningInfo.leds[i]                   = CHSV(newColor, SATURATION_MAX, newBrightness);
            LedRunningInfo.leds[i+NUM_LEDS_PER_FACE] = CHSV(newColor, SATURATION_MAX, newBrightness);
        }
        LedRunningInfo.leds[i].nscale8(224);                                     
        LedRunningInfo.leds[i+NUM_LEDS_PER_FACE].nscale8(224);                                     
    }
    return (beatCounter);
}

void ColorBeatMode(int *sound)
{
	uint8_t i;
    uint8_t beat;
    uint8_t currentColor;
    uint8_t newBrightness;

	Color++;
	for(i= 0; i < NUM_LEDS_PER_FACE; i++) 
	{                                    
     	beat = U_SUB(sound[i+BEAT_MODE_FREQUENCY_OFFSET], BEAT_MODE_NOISE_VALUE);
        currentColor = MaxColor(LedRunningInfo.leds[i].r, LedRunningInfo.leds[i].g, LedRunningInfo.leds[i].b);
    	if (beat > 3 * currentColor)  
    	{    
            newBrightness = beat * BRIGHTNESS_FACTOR;            // Higher the Beat => Higher the brightness
            LedRunningInfo.leds[i]                   = CHSV(Color, SATURATION_MAX, newBrightness);
            LedRunningInfo.leds[i+NUM_LEDS_PER_FACE] = CHSV(Color, SATURATION_MAX, newBrightness);
        }                                     
        LedRunningInfo.leds[i].nscale8(224);                                     
    	LedRunningInfo.leds[i+NUM_LEDS_PER_FACE].nscale8(224);                                     
    }
}

uint8_t ColorBeatModeWithCount(int *sound)
{
    uint8_t i;
    uint8_t beat;
    uint8_t currentColor;
    uint8_t beatCounter;
    uint8_t newBrightness;

    beatCounter = 0;
    Color++;
    for(i= 0; i < NUM_LEDS_PER_FACE; i++) 
    {                               
        beat = U_SUB(sound[i+BEAT_MODE_FREQUENCY_OFFSET], BEAT_MODE_NOISE_VALUE);    // Removing Noise, but keep > 0     
        currentColor = MaxColor(LedRunningInfo.leds[i].r, LedRunningInfo.leds[i].g, LedRunningInfo.leds[i].b);
        if (beat > 3 * currentColor)  
        {    
            beatCounter++;
            newBrightness = beat * BRIGHTNESS_FACTOR;            // Higher the Beat => Higher the brightness
            LedRunningInfo.leds[i]                   = CHSV(Color, SATURATION_MAX, newBrightness);
            LedRunningInfo.leds[i+NUM_LEDS_PER_FACE] = CHSV(Color, SATURATION_MAX, newBrightness);
        }
        LedRunningInfo.leds[i].nscale8(224);                                     
        LedRunningInfo.leds[i+NUM_LEDS_PER_FACE].nscale8(224);                                     
    }
    return (beatCounter);
}

/**************************************************************/
/*                        PRIVATE FUNCTIONS                   */
/**************************************************************/

static uint8_t MaxColor(uint8_t a, uint8_t b, uint8_t c)
{
    if(a > b)
    {
        if (a > c)
        {
            return(a);
        }
        else 
        {
            return(c);
        }
    }
    else
    {
        if (b > c)
        {
            return(b);
        }
        else 
        {
            return(c);
        }
    }
}