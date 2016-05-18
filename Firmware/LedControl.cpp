#include "Arduino.h"
#include "LedControl.h"
#include "SoundAnalysis.h"


#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

/**************************************************************/
/*                        PUBLIC DATA                         */
/**************************************************************/

CRGBPalette16 gPal;
LedInformation_s LedRunningInfo;


/**************************************************************/
/*                        PRIVATE DATA                        */
/**************************************************************/

/**************************************************************/
/*                        PUBLIC FUNCTIONS                    */
/**************************************************************/

void InitLeds()
{
  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(LedRunningInfo.leds, NUM_LEDS);
  FastLED.setBrightness(0xFF);
  //FastLED.setBrightness(128);
  // FastLED.setBrightness(BRIGHTNESS_HALF);
  set_max_power_in_volts_and_milliamps(5, 2500);  // TODO Ajust this value ??
  //FastLED.delay(1000);
  
}

void PowerLeds()
{
  //FastLED.show();
  show_at_max_brightness_for_power();
}





/**************************************************************/
/*                        PRIVATE FUNCTIONS                   */
/**************************************************************/