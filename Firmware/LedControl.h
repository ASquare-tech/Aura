#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include "FastLED.h"                                          // FastLED library. Preferably the latest copy of FastLED 2.1.

/**************************************************************/
/*                        DEFINE & TYPEDEF                    */
/**************************************************************/

#define LED_PIN                                              10
#define LED_DT 	                                             LED_PIN

#define HEIGHT 		                                           0x0F
#define WIDTH                                                0x0A
#define WIDTH_PER_FACE 		                                   0x05
#define NUM_LEDS                                             HEIGHT * WIDTH
#define NUM_LEDS_PER_FACE 	                                 HEIGHT * WIDTH_PER_FACE

#define LED_TYPE    			                                   WS2812B
#define COLOR_ORDER 			                                   GRB
#define FRAMES_PER_SECOND  		                               0x3C
#define LED_CONTROL_TIME_OUT	                               0x05DC

/* How hot is "hot"? Increase for brighter fire */
#define COOLING                                              0x5A
#define HOT                                                  0xB4
#define MAXHOT                                               HOT*HEIGHT

#define FPS                                                  0x14
#define FPS_DELAY                                            1000/FPS

#define BRIGHTNESS_MIN                                       0x00
#define BRIGHTNESS_BOOT                                      BRIGHTNESS_MIN
#define BRIGHTNESS_HALF                                      0x7F
#define BRIGHTNESS_MAX                                       0xFF
#define BRIGHTNESS_DECREASE                                  0x30

#define SATURATION_MAX                                       0xFF

#define LED_COLOR_CSV_RED                                    0x00
#define LED_COLOR_CSV_ORANGE                                 0x20
#define LED_COLOR_CSV_YELLOW                                 0x40
#define LED_COLOR_CSV_GREEN                                  0x80
#define LED_COLOR_CSV_CYAN                                   0xA0
#define LED_COLOR_CSV_BLUE                                   0xC0
#define LED_COLOR_CSV_PINK                                   0xF0
#define LED_COLOR_CSV_LIGHT_PINK                             0xC8
#define LED_COLOR_CSV_DARK_PINK                              0xFF

#define MAX_DIMENSION                                        ((WIDTH>HEIGHT) ? WIDTH : HEIGHT)

typedef struct cordinate_t
{
  uint16_t x;
  uint16_t y;
  uint16_t z;
}cordinate_s;

typedef struct LedInformation_t
{
  CRGB          leds[NUM_LEDS];
  int           Brightness;
  uint8_t       gHue; 
  CRGBPalette16 currentPalette;
  uint8_t       noise[MAX_DIMENSION][MAX_DIMENSION]; 
  cordinate_s   coordinate;
  uint8_t       ExternaLight;
} LedInformation_s;

/**************************************************************/
/*                        PUBLIC DATA                         */
/**************************************************************/

extern LedInformation_s LedRunningInfo;

/**************************************************************/
/*                        PUBLIC FUNCTIONS                    */
/**************************************************************/

void InitLeds();
void PowerLeds();
void VuMeterLeds(int *soundMeasure);
void VuMeterLedsTest(int value);


/**************************************************************/
/*                        PRIVATE FUNCTIONS                   */
/**************************************************************/

#endif