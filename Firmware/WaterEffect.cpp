#include "LedControl.h"
#include "WaterEffect.h"

/**************************************************************/
/*                         PUBLIC DATA                        */
/**************************************************************/


/**************************************************************/
/*                         PRIVATE DATA                       */
/**************************************************************/

WandBWater_s bandwInfo;

/**************************************************************/
/*                         PUBLIC FUNCTIONS                   */
/**************************************************************/

void SetupWaterEffect()
{
  	bandwInfo.speed = 50; // speed is set dynamically once we've started up
  	bandwInfo.scale = 15; // scale is set dynamically once we've started up
  	bandwInfo.kMatrixSerpentineLayout = true;
  	LedRunningInfo.coordinate.x = random16();
    LedRunningInfo.coordinate.y = random16();
    LedRunningInfo.coordinate.z = random16();	

  	fill_solid(LedRunningInfo.currentPalette, 16, CRGB::Black);// 'black out' all 16 palette entries...

  	LedRunningInfo.currentPalette[0] = CRGB::White;
  	LedRunningInfo.currentPalette[4] = CRGB::White;
  	LedRunningInfo.currentPalette[8] = CRGB::White;
  	LedRunningInfo.currentPalette[12] = CRGB::White;
    FastLED.setBrightness(0xFF);
    set_max_power_in_volts_and_milliamps(5, 2500);
}

void StopWaterEffect()
{
  fill_solid(LedRunningInfo.currentPalette, 16, CRGB::Black);
}

void RunWaterEffect() 
{
  LedRunningInfo.currentPalette[0] = CRGB::White;
  LedRunningInfo.currentPalette[4] = CRGB::White; 
  LedRunningInfo.currentPalette[8] = CRGB::White;
  LedRunningInfo.currentPalette[12] = CRGB::White;

  FillNoise();
  MapNoiseToLed();
  FastLED.show();
  bandwInfo.speed = 1; 
}

void RunWaterEffectWithColor(uint8_t color) 
{
  uint8_t newSpeed;

  LedRunningInfo.currentPalette[0] = CHSV(color, 255, 255);
  LedRunningInfo.currentPalette[4] = CHSV(color, 255, 255);
  LedRunningInfo.currentPalette[8] = CHSV(color, 255, 255);
  LedRunningInfo.currentPalette[12] = CHSV(color, 255, 255);

  FillNoise();  // generate noise data
  MapNoiseToLed(); // using the current palette
  FastLED.show();
  bandwInfo.speed = 1; 
}

static uint8_t defineNewSpeed(uint8_t music)
{
  uint8_t result;

  result = music * 5 - 13;

  return result;   
}

/**************************************************************/
/*                         PRIVATE FUNCTIONS                  */
/**************************************************************/
static void MapNoiseToLed()
{
  static uint8_t ihue=0;
  
  for(int i = 0; i < WIDTH; i++) 
  {
    for(int j = 0; j < HEIGHT; j++) 
    {
      // We use the value at the (i,j) coordinate in the noise
      // array for our brightness, and the flipped value from (j,i)
      // for our pixel's index into the color palette.

      uint8_t index = LedRunningInfo.noise[j][i];
      uint8_t bri =   LedRunningInfo.noise[i][j];
      // brighten up, as the color palette itself often contains the 
      // light/dark dynamic range desired
      if( bri > 127 ) 
      {
       	bri = 255;
      } 
      else 
      {
        bri = dim8_raw( bri * 2);
      }

      CRGB color = ColorFromPalette(LedRunningInfo.currentPalette, index, bri);
      LedRunningInfo.leds[XY(i,j)] = color;
    }
  }
  ihue+=1;
}

static void FillNoise() 
{
  // If we're runing at a low "speed", some 8-bit artifacts become visible
  // from frame-to-frame.  In order to reduce this, we can do some fast data-smoothing.
  // The amount of data smoothing we're doing depends on "speed".
  uint8_t dataSmoothing = 0;
  if(bandwInfo.speed < 50) 
  {
    dataSmoothing = 200 - (bandwInfo.speed * 4);
  }
  for(int i = 0; i < MAX_DIMENSION; i++) 
  {
    int ioffset = bandwInfo.scale * i;
    for(int j = 0; j < MAX_DIMENSION; j++) 
    {
      int joffset = bandwInfo.scale * j;
      
      uint8_t data = inoise8(LedRunningInfo.coordinate.x + ioffset,LedRunningInfo.coordinate.y + joffset,LedRunningInfo.coordinate.z);

      // The range of the inoise8 function is roughly 16-238.
      // These two operations expand those values out to roughly 0..255
      // You can comment them out if you want the raw noise data.
      data = qsub8(data,16);
      data = qadd8(data,scale8(data,39));

      if( dataSmoothing ) 
      {
        uint8_t olddata = LedRunningInfo.noise[i][j];
        uint8_t newdata = scale8(olddata, dataSmoothing) + scale8(data, 256 - dataSmoothing);
        data = newdata;
      }
      
      LedRunningInfo.noise[i][j] = data;
    }
  }
  
  LedRunningInfo.coordinate.z += bandwInfo.speed;
  
  // apply slow drift to X and Y, just for visual variation.
  LedRunningInfo.coordinate.x += bandwInfo.speed >> 3;
  LedRunningInfo.coordinate.y -= bandwInfo.speed >> 4;
}
//
// Mark's xy coordinate mapping code.  See the XYMatrix for more information on it.
//
static uint16_t XY( uint8_t x, uint8_t y)
{
  uint16_t i;
  if(bandwInfo.kMatrixSerpentineLayout == false) 
  {
    i = (y * WIDTH) + x;
  }
  if(bandwInfo.kMatrixSerpentineLayout == true) 
  {
    if( y & 0x01) 
    {
      // Odd rows run backwards
      uint8_t reverseX = (WIDTH - 1) - x;
      i = (y * WIDTH) + reverseX;
    } 
    else 
    {
      // Even rows run forwards
      i = (y * WIDTH) + x;
    }
  }
  return i;
}
