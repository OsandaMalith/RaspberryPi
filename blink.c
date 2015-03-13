// ***** 1. Pre-processor Directives Section *****
#include "TExaS.h"
#include "tm4c123gh6pm.h"

// ***** 2. Global Declarations Section *****

// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Delay100ms(unsigned long time); //wait 100 ms

// ***** 3. Subroutines Section *****

// PE0, PB0, or PA2 connected to positive logic momentary switch using 10 k ohm pull down resistor
// PE1, PB1, or PA3 connected to positive logic LED through 470 ohm current limiting resistor
// To avoid damaging your hardware, ensure that your circuits match the schematic
// shown in Lab8_artist.sch (PCB Artist schematic file) or 
// Lab8_artist.pdf (compatible with many various readers like Adobe Acrobat).
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define GPIO_PORTE_DATA_R				(*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R				(*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R			(*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_DEN_R				(*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_AMSEL_R			(*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R			(*((volatile unsigned long *)0x4002452C))

unsigned long in, out;
int main(void){
	unsigned long volatile delay;
	
	SYSCTL_RCGC2_R |= 0x10;           // Port E clock
	delay = SYSCTL_RCGC2_R;           // wait 3-5 bus cycles
	GPIO_PORTE_DIR_R |= 0x02;					// PE1 output
	GPIO_PORTE_DIR_R &= ~0x01;				// PE0 input
	GPIO_PORTE_AFSEL_R &= ~0x03;			// turn off alternative functions
	GPIO_PORTE_AMSEL_R &= ~0x03;			// turn off analog
	GPIO_PORTE_PCTL_R &= ~0x03;
	GPIO_PORTE_DEN_R |= 0x03;					// enable pins 0 and 1 on port e
	
//**********************************************************************
// The following version tests input on PE0 and output on PE1
//**********************************************************************
  TExaS_Init(SW_PIN_PE0, LED_PIN_PE1);  // activate grader and set system clock to 80 MHz
  
	
  EnableInterrupts();           // enable interrupts for the grader
	
	GPIO_PORTE_DATA_R |= 0x02;		// start with LED on
	
  while(1){
		// wait 100 ms
		Delay100ms(1);
		in = GPIO_PORTE_DATA_R&0x01;
		out = GPIO_PORTE_DATA_R&0x02;
		
		//if switch is pressed
		if(in) {
			//toggle LED
			if(out) {
				GPIO_PORTE_DATA_R &= ~0x02;
			}
			else {
				GPIO_PORTE_DATA_R |= 0x02;
			}
		}
			//else turn on LED
    else{
			GPIO_PORTE_DATA_R |= 0x02;   //turns LED on
		}
  }
  
}

void Delay100ms(unsigned long time){
	unsigned long i;
	while(time > 0){
		i = 1333333;
		while(i > 0){
			i = i - 1;
		}
		time = time - 1;
	}
}
