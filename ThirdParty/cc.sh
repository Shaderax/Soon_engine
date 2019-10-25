#!/bin/sh

mkdir test ;
cd test ;
cmake .. ;
make -j 4;
cd .. ;
rm -rf test
