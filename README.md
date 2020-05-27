# How to compile 

Please run following commands to get source code:
```bash
git clone https://github.com/sunplus-plus1/SP7021.git
cd SP7021
git submodule update --init --recursive
git submodule update --remote --merge
git submodule foreach --recursive git checkout master
make clean
make config
```
then show
```bash
Select boards:
[1] SP7021 Ev Board
[2] LTPP3G2 Board
[3] SP7021 Demo Board (V1/V2)
[4] SP7021 Demo Board (V3)
[5] BPi-F2S Board
[6] BPi-F2P Board
```
```bash
Select configs (C chip).
[1] eMMC
[2] SD Card
```
please select your board and boot device. after make config is completed. then,
```bash
make all
```
finally, please get image file from `out` folder 

Note:
The defconfig of LTPP3G2 is composite by many modules, the content is vary from modules to modules. So if you want to build it,  please be sure you have deconfig that you are using and to replace `linux/kernel/arch/arm/configs/sp7021_chipC_ltpp3g2_defconfig`
