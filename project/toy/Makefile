# makfile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: toy.elf 

#additional rules for files
toy.elf: ${COMMON_OBJECTS} p2_interrupt_handler.o led.o switches.o main.o wdInterruptHandler.o stateMachines.o buzzer.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: toy.elf
	msp430loader.sh toy.elf

clean:
	rm -f *.o *.elf
led.o: led.c led.h

wdInterruptHandler.o: stateMachines.h buzzer.h led.h switches.h 

stateMachines.o: led.h buzzer.h stateMachines.h 

buzzer.o: buzzer.h

switches.o: switches.h led.h

main.o: led.h buzzer.h switches.h 

