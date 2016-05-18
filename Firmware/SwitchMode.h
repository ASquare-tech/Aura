#ifndef _SWITCH_MODE_H_
#define _SWITCH_MODE_H_

/**************************************************************/
/*                        DEFINE & TYPEDEF                    */
/**************************************************************/

#define TIMER_MS_ONE_SECOND		0x32
#define TIMER_MS_RESET			0x00
#define TIMER_ONE_SECOND_RESET	0x00000000
#define TIMER_ONE_SECOND		0x00000001
#define TIMER_SECONE_MINUTE		0x00000E10
#define TIMER_THRITY_SECOND		0x1E
#define MINUTE_DELAY_SWITCH		0x01 

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

typedef struct switchInfo_t	
{
  int 		timerSecond;
  char  	timerMs;
  char 		currentMode;
  char 		currentSoundState;
  int 		timerSecondSoundLevel;
  int		sampleNumber;
  int 		totalSampleValue;
}switchInfo_s;

/**************************************************************/
/*                        PUBLIC DATA                         */
/**************************************************************/

extern switchInfo_s switchInfo;

/**************************************************************/
/*                        PUBLIC FUNCTIONS                    */
/**************************************************************/

void SwitchModeTick();
void SwitchModeInit();
char getActualMode();

/**************************************************************/
/*                        PRIVATE FUNCTIONS                   */
/**************************************************************/

static void switchToNewMode(char newMode);
static void checkIfModeShouldSwitch();
static void SwitchModeWhenNormal();
static void SwitchModeWhenParty();
static void SwitchModeWhenOff();
static void updateSoundLevel();
static char updateTimer();
static void resetSoundValue();

#endif