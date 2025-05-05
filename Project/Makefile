all: libLcd.a main.elf main-a.elf

CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -Os -I../h 
LDFLAGS 	= -L/opt/ti/msp430_gcc/include -L../lib 
#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c
AR              = msp430-elf-ar

libLcd.a: font-5x7.o lcdutils.o lcddraw.o
	$(AR) crs $@ $^

lcddraw.o: lcddraw.c lcddraw.h lcdutils.h
lcdutils.o: lcdutils.c lcdutils.h
buzzer.o: buzzer.c buzzer.h
StrLength.o: StrLength.s

install: libLcd.a
	mkdir -p ../h ../lib
	mv $^ ../lib
	cp *.h ../h

clean:
	rm -f libLcd.a *.o *.elf *.c~ *.h~

main.elf: main.o libLcd.a buzzer.o stateMachines.o p2_interrupt_handler.o switches.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ -lTimer 

main-a.elf: main.o libLcd.a buzzer.o stateMachines.o p2_interrupt_handler.o switches.o StrLength.o
	$(AS) $(CFLAGS) $(LDFLAGS) $^ -o $@ -lTimer 


load: main.elf
	msp430loader.sh $^

load-a: main-a.elf
	msp430loader.sh $^
