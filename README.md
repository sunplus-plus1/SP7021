# How to compile 
Before you compile, please make sure these packages are installed:
```bashl
sudo apt-get install openssl libssl-dev bison flex git make u-boot-tools libmpc-dev libgmp-dev python3-pip mtd-utils
pip install pycryptodomex pyelftools Crypto
```
Fetch the source code:
```bash
git clone https://github.com/sunplus-plus1/SP7021.git
cd SP7021
git submodule update --init --recursive
git submodule foreach git checkout master
```
Configure the build:
```bash
make config
```
Select your board:
```bash
Select boards:
[1] SP7021 Ev Board     [11] I143 Ev Board      [21] Q645 Ev Board      [31] SP7350 Ev Board
[2] LTPP3G2 Board       [12] I143 Zebu (ZMem)   [22] Q645 Zebu (ZMem)   [32] SP7350 Zebu (ZMem)
[3] SP7021 Demo Brd V2
[4] SP7021 Demo Brd V3
[5] BPI-F2S Board
[6] BPI-F2P Board
[7] LTPP3G2 Board (S+)
```
If you selected [1] or [11], please select the chip:
```bash
Select chip.
[1] Chip C
[2] Chip P
```
```bash
Select configs (C chip).
[1] eMMC
[2] SD Card
```
```bash
Select rootfs:
[1] BusyBox
[2] Full
```
>If you want to change the kernel configuration, run:
```
make kconfig
```
>after make config has completed. 
>
>**Note 0:** Please don't enter the `linux/kernel` folder and run "`make menuconfig`"
>
>**Note 1:** For USB gadget support, please refer to [here](https://github.com/sunplus-plus1/usb_gadget)

Build the kernel:
```
make
```
If your local LANG is not english, please run
```
LANG=c make
```
When the build completes, you will find the image file in the `out` folder.

If you chose
* eMMC:
  * Copy `out/ISPBOOOT.BIN` to a USB stick, which should be a FAT32 filesystem
  * Update the eMMC from the USB stick:  power off, set SW1 to on, SW2 to off, power on
  * Boot the kernel: power off, set SW1 to off, SW2 to off, power on
* SD Card:
  * the image file is `out/boot2linux_SDcard/ISP_SD_BOOOT.img`
  * write it to the sdcard: `sudo dd if=ISP_SD_BOOOT.img of=/dev/sdX bs=1M`, where /dev/sdX is your sdcard device
  * insert your sdcard in the board and boot: power off, set SW1 to on, SW2 to on, power on

For more information, please visit [here](https://sunplus-tibbo.atlassian.net/wiki/spaces/doc/pages/375783435/SP7021+Application+Note)

