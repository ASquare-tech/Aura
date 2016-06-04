#ifndef SOUND_ANALYSIS_H
#define SOUND_ANALYSIS_H

/* Be Careful 1 Must be declare before FHT include 			  */
// TODO Put to 0x01 the one we use
#define OCTAVE                         						0x00
#define LOG_OUT 											0x01 

#include "Arduino.h"

/**************************************************************/
/*                        DEFINE & TYPEDEF                    */
/**************************************************************/

#define U_SUB(a,b) 											((a>b) ? a-b : 0)
#define BEAT_SUB(a,b) 										((a>b) ? a-b : 0)
#define U128_SUM(a,b) 										((a+b) > 128 ? 64 : a+b)
#define REMOVE_NOISE(sound,noise) 							((noise > sound) ? 0 : sound-noise)

#define SOUND_SENSOR_PIN									0

#define SOUND_SENSOR_ANALOG_OFFSET							0x200									

#define DIFF_TO_BUILD_SIGNED_INT							0x200
#define FACTOR_TO_BUILD_SIGNED_SHORT						0x06

#define DC_OFFSET  											32 
#define NOISE												0x64	

// TODO: Adjust value for NOISE / SENSITIVTY
#define NOISE_VALUE											0x2A
#define VOLUME_SAMPLES										0x48	

#define TOP 												17 
//#define TOP 										(HEIGHT + 2)  


#define FHT_OCTAVE_NUMBER 									0x08 
//#define FHT_SAMPLE_NUMBER 									256 
#define FHT_SAMPLE_NUMBER 									128 
#define FHT_HALF_SAMPLE_NUMBER 								FHT_SAMPLE_NUMBER/2 

#define MEAN_SOUND_THS										0x05

#define MUSIC_ON											0x00
#define MUSIC_OFF											0x01

#define STATE_MUSIC_OFF										0x00
#define STATE_MUSIC_PAUSE									0x01
#define STATE_MUSIC_ON										0x02	



/**************************************************************/
/*                        PUBLIC DATA                         */
/**************************************************************/

/**************************************************************/
/*                        PUBLIC FUNCTIONS                    */
/**************************************************************/

void fhtsound();
void GetFHT();

void InitSoundAnalysis();
int GetSoundLevel(uint16_t *minLvlAvg, uint16_t *maxLvlAvg);
void ProcessSoundAnalysis();
void ProcessSoundAnalysisTable(int *soundMeasure);
uint16_t MeanSoundAnalysis();

/**************************************************************/
/*                        PRIVATE FUNCTIONS                   */
/**************************************************************/

static void SoundAcquisition();
static void SoundProcessing();
static void SoundDisplay();


/*#ifdef __cplusplus
}
#endif*/

#endif
