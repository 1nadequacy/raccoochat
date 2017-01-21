#!/bin/bash

echo 'Start to clean folders.'

rm -r bin/
rm -r CMakeFiles/
rm -r test/
rm -r Testing/

rm cmake_install.cmake
rm CMakeCache.txt
rm CTestTestfile.cmake
rm Makefile

cd raccoochat/gen-cpp
rm RaccooChat_server.skeleton.cpp
cd ..
rm RaccooChatClient.pyc
cd ..

echo 'Cleaning has bone.'
