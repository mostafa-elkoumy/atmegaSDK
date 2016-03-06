/*
 * commonDefs.h
 *
 * Created: 2/10/2016 3:20:14 PM
 *  Author: Mostafa
 */ 


#ifndef COMMONDEFS_H_
#define COMMONDEFS_H_

#define SET_BIT(byte, bit) 			(byte |= (1<<bit))
#define CLR_BIT(byte, bit)			(byte &= ~(1<<bit))

#define MASK(nBits)					((1<<nBits) - 1)


#endif /* COMMONDEFS_H_ */