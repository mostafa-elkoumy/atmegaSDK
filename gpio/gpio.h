#include <avr/io.h>
#include "../commonDefs.h"


typedef struct
{
	unsigned char dir  : 1;
	unsigned char port : 2;
	unsigned char bit  : 3;
	unsigned char lastDir  : 1;
	unsigned char val  : 1;
}pin_t;


#define PORT_A						0
#define PORT_B						1
#define PORT_C						2
#define PORT_D						3
#define PORT_VALID					4

#define DIR_IN						0
#define DIR_OUT						1
#define DIR_VALID					2

void pinInitialize(unsigned char port, unsigned char bit, pin_t* pPin);

void pinUpdate(pin_t* pPin);

void pinSetInp(pin_t* pPin);

void pinSetOut(pin_t* pPin);

void pinWriteOn(pin_t* pPin);

void pinWriteOff(pin_t* pPin);

unsigned char pinReadInp(pin_t* pPin);

int blindInit(pin_t* pPin);

unsigned char blindExecutePin(pin_t* pPin);
