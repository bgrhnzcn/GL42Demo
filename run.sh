#! /bin/bash

./bin/gl42Demo || printf "\e[31mExitted with error code $?\n\e[0m" >> /dev/stderr
clear