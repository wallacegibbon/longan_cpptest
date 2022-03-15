NUCLEI_RISCV_GCC_ROOT := /usr/local/nuclei-riscv-tools/gcc
NUCLEI_OPENOCD_ROOT := /usr/local/riscv-openocd

OPENOCD_CMD := $(NUCLEI_OPENOCD_ROOT)/bin/openocd
MY_OPENOCD_ARGS := -f interface/ftdi/sipeed-rv-debugger.cfg \
	-f target/gd32vf103.cfg

RISCV_ARCH = rv32imac
RISCV_ABI = ilp32
SOC = gd32vf103
CORE = n205

STDCLIB ?= newlib_nano
#STDCLIB ?= newlib_small

BANNER = 0

TARGET = cpptest

NUCLEI_SDK_ROOT = ./nuclei-sdk
BOARD = gd32vf103c_longan_nano

#SRCDIRS = . src
SRCDIRS = src
INCDIRS = src

include $(NUCLEI_SDK_ROOT)/Build/Makefile.base

.PHONY: tags load start_openocd

tags:
	@echo "\tGenerating ctag file..."
	@find . -regex '.*\.[ch]' -exec realpath {} \; \
		| sort | uniq | xargs ctags

load:
	@echo "\tLoad program to the target machine..."
	@$(OPENOCD_CMD) $(MY_OPENOCD_ARGS) -d1 \
		-c "program $(TARGET).elf verify reset exit"

run_openocd:
	@echo "\tStarting the OpenOCD server..."
	@$(OPENOCD_CMD) $(MY_OPENOCD_ARGS)

