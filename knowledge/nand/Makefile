objs := head.o init.o nand.o main.o

nand.bin : $(objs)
	arm-linux-ld -Tlink.lds	-o nand.elf $^
	arm-linux-objcopy -O binary -S nand.elf $@
	arm-linux-objdump -D -m arm  nand.elf > nand.dis
	rm -rf *.o *.dis *.elf		
%.o:%.c
	arm-linux-gcc -Wall -c -O2 -o $@ $<

%.o:%.S
	arm-linux-gcc -Wall -c -O2 -o $@ $<

clean:
	rm -f  nand.dis nand.bin nand.elf *.o
