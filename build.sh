#! /bin/bash

clear
cmake -S . -B build && make -C build/ -j4 2> build/error.log || (printf "\e[31mCompiler or Linker Error!\n\e[0m" && cat build/error.log)
