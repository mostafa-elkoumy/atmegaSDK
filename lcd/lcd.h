#include <avr/io.h>

#define LCD_PORT					PORTB
#define LCD_DDR						DDRB
#define LCD_RS_OFFSET				1
#define LCD_EN_OFFSET				3
#define LCD_DATA_OFFSET				4
#define LCD_RW_OFFSET				2

#define CMD_CLR_SCREEN				0x01
#define CMD_RETURN_HOME				0x02
#define CMD_DEC_CURSOR				0x04
#define CMD_SHIFT_DISP_RIGHT		0x05
#define CMD_INC_CURSOR				0x06
#define CMD_SHIFT_DISP_LEFT			0x07
#define CMD_ALL_OFF					0x08
#define CMD_DISP_OFF_CUR_ON			0x0A
#define CMD_DISP_ON_CUR_OFF			0x0C
#define CMD_DISP_ON_CUR_BLINK		0x0C
#define CMD_4BIT_MODE_COMM			0x28
#define CMD_8BIT_MODE_COMM			0x38
#define LINE1_START_OFFSET			0x80
#define LINE2_START_OFFSET			0xC0

void lcdInitialize(void);
void lcdGoToXY(unsigned char x, unsigned char y);
void lcdSendByte(unsigned char date);