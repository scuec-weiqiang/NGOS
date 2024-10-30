#ifndef PALTFORM_H
#define PALTFORM_H

#include "types.h"

/****************************************************************************/
#define MAXNUM_CPU 8
#define LENGTH_RAM 128*1024*1024
/****************************************************************************/
typedef struct UART_REG
{
   uint8_t RHR_THR_DLL;
   uint8_t IER_DLM;
   uint8_t FCR_ISR;
   uint8_t LCR;
   uint8_t MCR;
   uint8_t LSR;
   uint8_t MSR;
   uint8_t SPR;
}UART_REG_t;
#define UART0     (*(volatile UART_REG_t*)(0x10000000))


#endif