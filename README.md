# How to compile demo board v3 (bpi-f2s)

Please run following commands to get source code:
```bash
git clone https://github.com/sunplus-plus1/demo-board.git
cd demo-board 
git submodule update --init --recursive
git submodule update --remote --merge
git submodule foreach --recursive git checkout master
make bpi-f2s
```
then show
```bash
Q628 configs.
[1] Pentagram B chip (EMMC), revB IC
[2] Pentagram B chip (SPI-NAND), revB IC
[3] Pentagram B chip (NOR/romter), revB IC
[4] Pentagram B chip (SDCARD), revB IC
[5] Pentagram B chip (TFTP), revB IC
[6] Pentagram B chip (USB), revB IC
[7] Pentagram A chip (EMMC), revB IC
[8] Pentagram A chip (SPI-NAND), revB IC
[9] Pentagram A chip (NOR/romter), revB IC
[10] Pentagram A chip (SDCARD), revB IC
[11] Pentagram A chip (TFTP), revB IC
[12] Pentagram A chip (USB), revB IC
[13] others
```
please choose [7]~[12] for this board and get image file from out folder after make.