#! /bin/bash

./bin/gl42Demo || (exitcode=$?; printf "\e[31mExitted with error code $exitcode\n\e[0m" >> /dev/stderr; exit $exitcode)

