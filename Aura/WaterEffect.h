#ifndef WATER_EFFECT_H
#define WATER_EFFECT_H

/**************************************************************/
/*                        DEFINE & TYPEDEF                    */
/**************************************************************/

typedef struct WandBWater_t
{
	uint16_t speed; 
	uint16_t scale;
	bool kMatrixSerpentineLayout;
} WandBWater_s;

#define BLANC_AND_WHITE_WATER_DELAY 10

/**************************************************************/
/*                        PUBLIC DATA                         */
/**************************************************************/

/**************************************************************/
/*                        PUBLIC FUNCTIONS                    */
/**************************************************************/

void SetupWaterEffect();
void StopWaterEffect();
void RunWaterEffect();
void RunWaterEffectWithColor(uint8_t color);

/**************************************************************/
/*                        PRIVATE FUNCTIONS                   */
/**************************************************************/

static void FillNoise();
static void MapNoiseToLed();
static uint16_t XY( uint8_t x, uint8_t y);

#endif
