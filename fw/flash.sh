#!/bin/bash

PROGNAME="main"
PROJDIR=$(pwd)
BUILDDIR="${PROJDIR}/build"
FLASHDIR="${PROJDIR}/flash"
SRCDIR="${SRCDIR}/src"

cp "${BUILDDIR}/${PROGNAME}.uf2" "${FLASHDIR}"  

FLASHTARGET="${FLASHDIR}/$PROGNAME.uf2"

picotool load $FLASHTARGET;
picotool reboot 
