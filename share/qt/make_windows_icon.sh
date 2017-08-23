#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/FidChain.ico

convert ../../src/qt/res/icons/FidChain-16.png ../../src/qt/res/icons/FidChain-32.png ../../src/qt/res/icons/FidChain-48.png ${ICON_DST}
