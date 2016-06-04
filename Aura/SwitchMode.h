#ifndef _SWITCH_MODE_H_
#define _SWITCH_MODE_H_

/**************************************************************/
/*                        DEFINE & TYPEDEF                    */
/**************************************************************/

#define TIMER_COUNTER_INIT									0x00
#define LOW_SOUND_TIMER_COUNTER_TIMEOUT						0xAF	// 3.5 Seconds


#define PEAK_SOUND_TIMER_COUNTER_TIMEOUT_1					0x32	// 1 Second
#define PEAK_SOUND_TIMER_COUNTER_TIMEOUT_2					0x50	// 1.6 Seconds

#define PEAK_COUNTER_INIT									0x00
#define PEAK_COUNTER_THRESHOLD_1							0x01
#define PEAK_COUNTER_THRESHOLD_2							0x02

#define BEAT_COUNT_LIMIT_TO_SWITCH							0x10

#define MODE_NORMAL				0x00
#define MODE_PARTY				0x01

#define SOUND_NORMAL_STATE		0x00
#define SOUND_PARTY_STATE		0x01

#define SOUND_NORMAL_LEVEL		0x32
#define SOUND_PARTY_LEVEL		0x64

#define HALF_SAMPLE_MAX_NUMBER	0x2EE
#define MIN_TOTAL_NUMBER		0x5DC
// #define HALF_SAMPLE_MAX_NUMBER	0x12C
// #define MIN_TOTAL_NUMBER		0x258

#define BEAT_COUNT_LOW_LIMIT	0x05

#define SWITCH_MODE_NOK			0x00
#define SWITCH_MODE_OK			0x01

/**************************************************************/
/*                        PUBLIC DATA                         */
/**************************************************************/

/**************************************************************/
/*                        PUBLIC FUNCTIONS                    */
/**************************************************************/

void SwitchModeInit();
uint8_t SwitchModeFromBeat(uint8_t beatCount);
uint8_t SwitchModeFromNormal(uint8_t beatCount);
uint8_t GetCurrentMode();
void SetCurrentMode(uint8_t mode);

/**************************************************************/
/*                        PRIVATE FUNCTIONS                   */
/**************************************************************/

static void SwitchModeResetValue();
static void SwitchToNewMode(uint8_t newMode);

#endif