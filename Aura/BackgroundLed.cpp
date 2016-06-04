#include "LedControl.h"
#include "BackgroundLed.h"

/**************************************************************/
/*                         PUBLIC DATA                        */
/**************************************************************/



/**************************************************************/
/*                         PRIVATE DATA                       */
/**************************************************************/

/**************************************************************/
/*                        PUBLIC FUNCTIONS                    */
/**************************************************************/

void BackgroundMode(uint8_t color)
{
  uint8_t i;

  for(i = 0; i < NUM_LEDS; i++) 
  {                              
    LedRunningInfo.leds[i] = CHSV(color, SATURATION_MAX, BRIGHTNESS_MAX);                                                                  
  }
}

void BackgroundModePerFace(uint8_t firstColor, uint8_t secondColor)
{
  uint8_t i;

  for(i = 0; i < NUM_LEDS_PER_FACE; i++) 
  {                              
    LedRunningInfo.leds[i] = CHSV(firstColor, SATURATION_MAX, BRIGHTNESS_MAX);                                                                  
  }
  for(i = NUM_LEDS_PER_FACE; i < NUM_LEDS; i++) 
  {                              
    LedRunningInfo.leds[i] = CHSV(secondColor, SATURATION_MAX, BRIGHTNESS_MAX);                                                                  
  }
}

/**************************************************************/
/*                        PRIVATE FUNCTIONS                   */
/**************************************************************/