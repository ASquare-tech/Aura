#ifndef BEAT_MODE_H
#define BEAT_MODE_H

/**************************************************************/
/*                        DEFINE & TYPEDEF                    */
/**************************************************************/

#define U_SUB(a,b) 											((a>b) ? a-b : 0)	 
#define U128_SUM(a,b) 										((a+b) > 128 ? a+b-128 : a+b)	 
#define U150_SUM(a,b) 										((a+b) > 150 ? a+b-150 : a+b)	 
#define U150_SUB(a,b) 										((a>b) ? a-b : 0)

// TODO: Adjust value for NOISE / SENSITIVTY
#define BEAT_MODE_NOISE_VALUE								0x2A	
#define BEAT_MODE_FREQUENCY_OFFSET							0x07	

#define BEAT_COUTER_THRESHOLD								0x10	

// TODO: Customize for effect
#define BRIGHTNESS_FACTOR									0x0F	
#define COLOR_FACTOR										0x0A	

/**************************************************************/
/*                        PUBLIC DATA                         */
/**************************************************************/

/**************************************************************/
/*                        PUBLIC FUNCTIONS                    */
/**************************************************************/

uint8_t SwitchingBeatModeWithCount(int *sound);
void RandomBeatMode(int *sound);
void ColorBeatMode(int *sound);
uint8_t RandomBeatModeWithCount(int *sound);
uint8_t ColorBeatModeWithCount(int *sound);

/**************************************************************/
/*                        PRIVATE FUNCTIONS                   */
/**************************************************************/
static uint8_t MaxColor(uint8_t a, uint8_t b, uint8_t c);

#endif