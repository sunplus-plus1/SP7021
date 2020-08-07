# How to compile 
Before you compile, please install some packages for compiling.
```bash
sudo apt-get install openssl libssl-dev bison flex
```
Please run following commands to get source code:
```bash
git clone https://github.com/sunplus-plus1/SP7021.git
cd SP7021
echo "export PATH=\$PATH:"`pwd`/boot/uboot/tools >> ~/.bashrc
source ~/.bashrc
git submodule update --init --recursive
git submodule update --remote --merge
git submodule foreach --recursive git checkout master
### current linux kernel branch is kernel 5.4, if you want to build kernel 4.19, please
cd linux/kernel 
git checkout kernel_4.19
cd -
###
make config
```
then show
```bash
Select boards:
[1] SP7021 Ev Board               [11] I143 Ev Board
[2] LTPP3G2 Board                 [12] I143 Zebu (zmem)
[3] SP7021 Demo Board (V1/V2)
[4] SP7021 Demo Board (V3)
[5] BPi-F2S Board
[6] BPi-F2P Board
```
if you select [1] or [11], please select chip.
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
after make config is completed. then,
```bash
make or make all
```
finally, please get image file from `out` folder 

if you choose
* eMMC:
  * Copy out/ISPBOOOT.BIN in out folder to USB stick (FAT32)
  * Update USB stick to eMMC -> (Power off, set SW1 to ON, SW2 to OFF, power on)
  * Boot kernel -> (Power off, set SW1 to OFF, SW2 to OFF, power on)
* SD Card:
  * get out/boot2linux_SDcard/ISP_SD_BOOOT.img
  * copy to sdcard -> (sudo dd if=ISP_SD_BOOOT.img of=/dev/sdx bs=1M, /dev/sdx is your sdcard address)
  * put your sdcard to board and boot -> (Power off, set SW1 to ON, SW2 to ON, power on)

For more infomation, please visit [here](https://sunplus-tibbo.atlassian.net/wiki/spaces/doc/pages/375783435/SP7021+Application+Note)

Note:
The defconfig of LTPP3G2 is composite by many modules, the content is vary from modules to modules. So if you want to build it,  please be sure you have deconfig that you are using and to replace `linux/kernel/arch/arm/configs/sp7021_chipC_ltpp3g2_defconfig`
