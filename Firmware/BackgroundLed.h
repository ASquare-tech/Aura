#ifndef BACKGROUND_LED_H
#define BACKGROUND_LED_H

/**************************************************************/
/*                        DEFINE & TYPEDEF                    */
/**************************************************************/

#define BACKGROUND_RED										0x00
#define BACKGROUND_ORANGE									0x20
#define BACKGROUND_YELLOW 									0x40
#define BACKGROUND_GREEN									0x80
#define BACKGROUND_CYAN										0xA0
#define BACKGROUND_BLUE										0xC0
#define BACKGROUND_PINK										0xF0


/**************************************************************/
/*                        PUBLIC DATA                         */
/**************************************************************/

/**************************************************************/
/*                        PUBLIC FUNCTIONS                    */
/**************************************************************/

void BackgroundMode(uint8_t color);
void BackgroundModePerFace(uint8_t firstColor, uint8_t secondColor);

/**************************************************************/
/*                        PRIVATE FUNCTIONS                   */
/**************************************************************/

#endif