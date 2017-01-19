#!/bin/bash

mkdir build
cd build
# ../configure --with-llvmsrc=/home/strongcourage/llvm_giri \
			 # --with-llvmobj=/home/strongcourage/llvm_giri/build \
../configure --with-llvmsrc=$LLVM_HOME \
			 --with-llvmobj=$LLVM_HOME/build \
			 --enable-optimized \
			 --disable-debug-symbols \
			 --disable-docs \
			 --disable-terminfo \
			 --enable-targets=host-only
make
cd ..
make -C test
