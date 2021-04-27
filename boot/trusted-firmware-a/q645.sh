#!/bin/bash

# Project build does not use this script.
# This script is to build in this directory for convenience.

opt=$1   # clean first
dbg=$2   # 0=release, 1=debug

TC="../../crossgcc/gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu/bin/"
export PATH="$TC:$PATH"

if [ "$dbg" = "" ];then
	dbg=0
else
	dbg=1
fi

# log level
#LOG_LEVEL_NOTICE                U(20)
#LOG_LEVEL_WARNING               U(30)
#LOG_LEVEL_INFO                  U(40)
#LOG_LEVEL_VERBOSE               U(50)
log_arg="LOG_LEVEL=40"


# this is our final target
BL31_IMG=build/bl31.img

if [ "$dbg" = "1" ];then
	BL31_BIN=build/q645/debug/bl31.bin
else
	BL31_BIN=build/q645/release/bl31.bin
fi

echo "Build $BL31_BIN ..."

if [ "$opt" = "0" ];then
	make CROSS_COMPILE=aarch64-none-linux-gnu- PLAT=q645 DEBUG=$dbg $log_arg clean
	exit 1
fi
make CROSS_COMPILE=aarch64-none-linux-gnu- PLAT=q645 DEBUG=$dbg $log_arg $target

if [ $? -ne 0 ];then
	echo "bl31 build failed"
	exit 1
fi

ls -l $BL31_BIN

echo "Gen $BL31_IMG ..."
./tools/add_uhdr.sh "BL31" $BL31_BIN $BL31_IMG 0x1fffc0 0x200000
if [ $? -ne 0 ];then
	echo "bl31 gen failed"
	exit 1
fi
