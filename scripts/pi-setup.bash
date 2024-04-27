#! /usr/bin/env bash

PI_TARGET=${HOME}/projects/targets/pi
mkdir -p  ${PI_TARGET}
rsync -rzLR --safe-links  aaron@192.168.1.14:/usr/lib/aarch64-linux-gnu  ${PI_TARGET}
rsync -rzLR --safe-links  aaron@192.168.1.14:/usr/lib/gcc/aarch64-linux-gnu ${PI_TARGET}
rsync -rzLR --safe-links  aaron@192.168.1.14:/usr/include ${PI_TARGET}
rsync -rzLR --safe-links aaron@192.168.1.14:/lib/aarch64-linux-gnu/  ${PI_TARGET} 


# /opt/homebrew/opt/llvm/bin/clang++ \
#     --target=arm-linux-gnueabihf \
#     --sysroot=build/sysroot/sysroot \
#     -isysroot=build/sysroot/sysroot \
#     -isystem=build/sysroot/sysroot/usr/include/c++/12 \
#     -isystem=build/sysroot/usr/include/aarch64-linux-gnu/c++/12 \
#     -Lbuild/sysroot/lib/gcc/aarch64-linux-gnu \
#     -Bbuild/sysroot/lib/gcc/aarch64-linux-gnu \
#     -o build/rr_nn_test \
#     src/test/test_rr_nn.cpp 