#!/bin/bash

mkdir build
cd build
# ../configure --with-llvmsrc=/home/strongcourage/llvm_giri \
			 # --with-llvmobj=/home/strongcourage/llvm_giri/build \
             ../configure --with-llvmsrc=/home/ubuntu/llvm-giri \
             --with-llvmobj=/home/ubuntu/llvm-giri/build \
			 --enable-optimized \
			 --disable-debug-symbols \
			 --disable-docs \
			 --disable-terminfo \
			 --enable-targets=host-only
make
cd ..
make -C test
