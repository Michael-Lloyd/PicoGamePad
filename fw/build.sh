#!/bin/bash

PROJDIR=$(pwd)
BUILDDIR="${PROJDIR}/build"
SRCDIR="${SRCDIR}/src"
cmake -S $SRCDIR -B $BUILDDIR   
cd build 
make 
