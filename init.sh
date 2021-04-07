#!/bin/bash

cd crossgcc

cd gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu/aarch64-none-linux-gnu/bin
tar jxvf ld.gold.bz2
cd -

cd gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu/aarch64-none-linux-gnu/lib64
tar jxvf libstdc++.a.bz2
cd -

cd gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu/bin
tar jxvf aarch64-none-linux-gnu-gdb.bz2
cd -

cd gcc-arm-9.2-2019.12-x86_64-arm-none-eabi/bin
tar jxvf arm-none-eabi-gdb.bz2
cd -

cd gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu/libexec/gcc/aarch64-none-linux-gnu/9.2.1
tar jxvf cc1.bz2
tar jxvf cc1plus.bz2
tar jxvf f951.bz2
tar jxvf lto1.bz2

