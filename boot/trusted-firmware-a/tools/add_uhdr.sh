#!/bin/bash

# $1: image name
# $2: source image
# $3: output image
# $4: load address    (optional)
# $5: execute address (optional)

NAME="$1"
SRC="$2"
OUTPUT="$3"
LADDR=$4
RADDR=$5

####################
# check if mkimage is available?
MKIMAGE=./tools/mkimage   # Only our mkimage supports quickboot
TYPE=quickboot

if [ ! -f "$MKIMAGE" ];then
	echo "Error: not found file $MKIMAGE"
	exit 1
fi

function usage()
{
	echo "Usage:"
	echo "$0 image_name source_image output_image [load_addr] [exec_addr]"
}

##################
# Check arguments

if [ -z "$NAME" ];then
	echo "Missed arg1: name"
	usage
	exit 1
fi

if [ -z "$SRC" ];then
	echo "Missed arg2: source image"
	usage
	exit 1
fi

if [ -z "$OUTPUT" ];then
	echo "Missed arg3: output image"
	usage
	exit 1
fi

if [ -z "$LADDR" ];then
	LADDR=0
fi

if [ -z "$RADDR" ];then
	RADDR=0
fi


if [ ! -f "$SRC" ];then
	echo "Not found source image: $SRC"
	exit 1
fi

$MKIMAGE -A arm -O linux -T $TYPE -C none -a $LADDR -e $RADDR -n $NAME -d $SRC $OUTPUT

ls -l $OUTPUT
