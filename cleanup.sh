#!/bin/bash

echo 'Start to clean folders.'

rm -r bin/
rm -r CMakeFiles/
rm -r test/
rm -r Testing/

rm -r *.pyc

rm cmake_install.cmake
rm CMakeCache.txt
rm CTestTestfile.cmake
rm libraccoochat.a
rm Makefile

cd ..
rm RaccooChatClient.pyc
cd ..

echo 'Cleaning has bone.'
