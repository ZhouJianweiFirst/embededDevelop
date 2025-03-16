CC 		= arm-linux-gcc
LD 		= arm-linux-ld
OBJCOPY = arm-linux-objcopy
OBJDUMP = arm-linux-objdump
AR		= arm-linux-ar

INCDIR := $(shell pwd)
#预编译器FLAG
CPPFLAGS := -nostdlib -nostdinc -I$(INCDIR)/include
#编译器FLAG
CFLAGS := -Wall -O2 -fno-builtin

#以下变量导出到全局，提供给子文件夹下面的Makefile文件使用
export CC LD OBJCOPY OBJDUMP AR CPPFLAGS CFLAGS


objs := start.o led.o clock.o uart.o main.o
objs += lib/libc.a

uart.bin: $(objs)
	$(LD) -Tlink.lds -o uart.elf $^
	$(OBJCOPY) -O binary uart.elf uart.bin
	$(OBJDUMP) -D uart.elf > uart_elf.dis
	gcc mkv210_image.c -o mkx210
	./mkx210 uart.bin 210.bin
	
lib/libc.a:
	cd lib/; make; cd ../
	
%.o : %.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< -c

%.o : %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< -c

clean:
	rm *.o *.elf *.bin *.dis mkx210 -f
	cd lib/; make clean; cd ../

	
	
