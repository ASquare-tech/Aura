#include "Arduino.h"
#include "LedControl.h"
#include "BeatMode.h"
#include "SoundAnalysis.h"
#include <FHT.h>


/**************************************************************/
/*                        PUBLIC DATA                         */
/**************************************************************/

/**************************************************************/
/*                        PRIVATE DATA                        */
/**************************************************************/

static int SoundLevel;
static int SoundVolume[VOLUME_SAMPLES];
static uint8_t volumeIndex;
static uint16_t MinLevelAvg;                                              // For dynamic adjustment of graph low & high
static uint16_t MaxLevelAvg;
static uint8_t color;
static uint8_t randomIndex;

/**************************************************************/
/*                        PUBLIC FUNCTIONS                    */
/**************************************************************/

void InitSoundAnalysis()
{
  // Because we power Sound Detector with 3.3 Volts
  analogReference(EXTERNAL);

  SoundLevel  = 12;
  MinLevelAvg = 0;
  MaxLevelAvg = 512;
}

int GetSoundLevel(uint16_t *minLvlAvg, uint16_t *maxLvlAvg)
{
  int measure;
  uint8_t i;
  uint16_t minLvl, maxLvl;

  measure = analogRead(0);
  measure = abs(measure - DIFF_TO_BUILD_SIGNED_INT - DC_OFFSET);

  measure = REMOVE_NOISE(measure, NOISE);
  SoundLevel = ((SoundLevel * 7) + measure) >> 3;

  SoundVolume[volumeIndex] = measure;                                     
  if (++volumeIndex >= VOLUME_SAMPLES)
  {
    volumeIndex = 0x00;
  } 
 
  // Get volume range of prior frames
  minLvl = SoundVolume[0];
  maxLvl = SoundVolume[0];
  for(i = 1; i < VOLUME_SAMPLES; i++) 
  {
    if (SoundVolume[i] < minLvl)
    {
      minLvl = SoundVolume[i];
    }      
    else if (SoundVolume[i] > maxLvl) 
    { 
      maxLvl = SoundVolume[i];
    }
  }
  if((maxLvl - minLvl) < TOP)
  {
    maxLvl = minLvl + TOP;
  }
  MinLevelAvg = (MinLevelAvg * 63 + minLvl) >> 6;                
  MaxLevelAvg = (MaxLevelAvg * 63 + maxLvl) >> 6;

  *minLvlAvg = MinLevelAvg;
  *maxLvlAvg = MaxLevelAvg;

  return (SoundLevel);
}

void ProcessSoundAnalysis()
{
  int i;
  cli();  
  for (i = 0; i < FHT_SAMPLE_NUMBER; i++)
  {
    fht_input[i] = analogRead(SOUND_SENSOR_PIN) - SOUND_SENSOR_ANALOG_OFFSET;
  }
  // Apply FHT 
  fht_window(); 
  fht_reorder(); 
  fht_run();
  fht_mag_log();
  sei();
}

void ProcessSoundAnalysisTable(int *soundMeasure)
{
  int i;
  cli();  
  for (i = 0 ; i < FHT_SAMPLE_NUMBER ; i++)
  {
    fht_input[i] = analogRead(SOUND_SENSOR_PIN) - SOUND_SENSOR_ANALOG_OFFSET;
  } 
  sei();
  // Apply FHT
  fht_window(); 
  fht_reorder(); 
  fht_run();
  fht_mag_log();

  for(i = 0; i < FHT_SAMPLE_NUMBER; i++)
  {
    soundMeasure[i] = fht_log_out[i];
  }
}

uint16_t MeanSoundAnalysis()
{
  uint8_t i;
  uint16_t total = 0;
  cli();
  SoundAcquisition();
  SoundProcessing();
  sei(); 

  for(i = 0; i < FHT_HALF_SAMPLE_NUMBER; i++)
  {
    total += fht_log_out[i];
  }
  total = total / FHT_HALF_SAMPLE_NUMBER;

  return (total);
}

/**************************************************************/
/*                        PRIVATE FUNCTIONS                   */
/**************************************************************/

static void SoundAcquisition()
{
  uint8_t adcLow, adcHigh;
	uint8_t i;
  int measure;
	for (i = 0 ; i < FHT_SAMPLE_NUMBER ; i++) 
  { 
    while(!(ADCSRA & 0x10));      // Waiting for ADC Ready
    ADCSRA = 0xF5;
    adcLow = ADCL; 
    adcHigh = ADCH;
    measure = (adcHigh << 8) | adcLow;
    measure -= DIFF_TO_BUILD_SIGNED_INT; 	
    measure <<= FACTOR_TO_BUILD_SIGNED_SHORT; 
    fht_input[i] = measure; 
  }
}

static void SoundProcessing()
{
	  // Apply FHT
	  fht_window(); 
    fht_reorder(); 
    fht_run();
    fht_mag_log(); 
}

// To Read with processing
static void SoundDisplay()
{
	Serial.write(255);
  Serial.write(fht_log_out, FHT_HALF_SAMPLE_NUMBER); 
}
