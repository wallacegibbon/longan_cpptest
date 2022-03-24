NUCLEI_RISCV_GCC_ROOT := /usr/local/nuclei-riscv-tools/gcc
NUCLEI_OPENOCD_ROOT := /usr/local/riscv-openocd

OPENOCD_CMD := $(NUCLEI_OPENOCD_ROOT)/bin/openocd
MY_OPENOCD_ARGS := -f interface/ftdi/sipeed-rv-debugger.cfg -f target/gd32vf103.cfg

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
SRCDIRS = src screen-util
INCDIRS = . src

include $(NUCLEI_SDK_ROOT)/Build/Makefile.base

.PHONY: load run_openocd

load:
	$(OPENOCD_CMD) $(MY_OPENOCD_ARGS) -d1 -c "program $(TARGET).elf verify reset exit"

run_openocd:
	$(OPENOCD_CMD) $(MY_OPENOCD_ARGS)

