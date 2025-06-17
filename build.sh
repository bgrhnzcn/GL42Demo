#! /bin/bash

clear
export USER=$(users)
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=ON && make -C build/ 2> build/error.log || (printf "\e[31mCompiler or Linker Error!\n\e[0m" && cat build/error.log)
