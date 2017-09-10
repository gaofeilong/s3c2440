#CC = arm-linux-gcc
#LD = arm-linux-ld
#OD = arm-linux-objdump
#OC = arm-linux-objcopy
CC = arm-elf-gcc
LD = arm-elf-ld
OD = arm-elf-objdump
OC = arm-elf-objcopy
CFLAGS=-Wall -O2 -g -c

OBJS=start.o init.o abnormal.o serial.o nand.o boot.o mmu.o print.o 2440bsp.o \
     interrupt.o mem.o nand_driver.o fs.o driver_framework.o fs.o romfs.o

.c.o:
	$(CC) $(CFLAGS) $? -o $@
.S.o:
	$(CC) $(CFLAGS) $? -o $@
	
core.elf:$(OBJS)
	$(CC) -static -nostdlib -Tlink.lds $? -o $@ -lgcc
	$(OD) -D -m arm $@ > core.dis
	$(OC) -O binary -S $@ core.bin
	rm -rf *.o core.elf
	date
clean:
	rm -rf *.o *.elf *.bin *.dis tags
