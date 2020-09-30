# How to compile 
>Before you compile, please install some packages for compiling.
```bash
sudo apt-get install openssl libssl-dev bison flex
```
>Get source code and make config
```bash
git clone https://github.com/sunplus-plus1/SP7021.git
cd SP7021
echo "export PATH=\$PATH:"`pwd`/boot/uboot/tools >> ~/.bashrc
source ~/.bashrc
git submodule update --init --recursive
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
>if you want to enable usb gadget (mass storage, CDC), please run ...
```bash
# in order to easy to config, we would rather use 'merge_config' than 'make menuconfig'
cat <<EOT >> gadget_config
#
# USB Physical Layer drivers
#
CONFIG_USB_GADGET=y
CONFIG_SUNPLUS_USB_PHY=y
CONFIG_USB_SUNPLUS_OTG=y
CONFIG_USB_GADGET=y
CONFIG_GADGET_USB0=y
CONFIG_USB_GADGET_VBUS_DRAW=2
CONFIG_USB_GADGET_STORAGE_NUM_BUFFERS=2
#
# USB Peripheral Controller
#
CONFIG_USB_GADGET_SUNPLUS=y
CONFIG_USB_LIBCOMPOSITE=m
CONFIG_USB_F_SS_LB=m
CONFIG_USB_U_ETHER=m
CONFIG_USB_F_NCM=m
CONFIG_USB_F_ECM=m
CONFIG_USB_F_SUBSET=m
CONFIG_USB_F_RNDIS=m
CONFIG_USB_F_MASS_STORAGE=m
CONFIG_USB_CONFIGFS=m
CONFIG_USB_CONFIGFS_NCM=y
CONFIG_USB_CONFIGFS_ECM=y
CONFIG_USB_CONFIGFS_RNDIS=y
CONFIG_USB_CONFIGFS_MASS_STORAGE=y
CONFIG_USB_ZERO=m
CONFIG_USB_ETH=m
CONFIG_USB_ETH_RNDIS=y
CONFIG_USB_G_NCM=m
CONFIG_USB_GADGETFS=m
CONFIG_USB_MASS_STORAGE=m
CONFIG_CONFIGFS_FS=m
# CONFIG_USB_CONFIGFS_F_PRINTER is not set
# CONFIG_USB_CONFIGFS_F_UVC is not set
# CONFIG_USB_CONFIGFS_F_HID is not set
# CONFIG_USB_CONFIGFS_F_FS is not set
# CONFIG_USB_CONFIGFS_F_LB_SS is not set
# CONFIG_USB_CONFIGFS_EEM is not set
# CONFIG_USB_CONFIGFS_ECM_SUBSET is not set
# CONFIG_USB_CONFIGFS_OBEX is not set
# CONFIG_USB_CONFIGFS_ACM is not set
# CONFIG_USB_CONFIGFS_SERIAL is not set
# CONFIG_FSL_UTP is not set
# CONFIG_USB_ETH_EEM is not set
EOT

cd linux/kernel
scripts/kconfig/merge_config.sh -m .config ../../gadget_config
cd ../..
```
>after make config is completed. then,
```bash
make or make all
```
>About how to enable gedget, please refer to [here](https://github.com/sunplus-plus1/usb_gadget)

>finally, please get image file from `out` folder 

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


