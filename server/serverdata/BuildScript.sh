#!/bin/bash
g++ -o $2.so -fPIC -shared -Wl,-soname,$2.so -std=c++0x -x c++ -Iserver/serverdata/scripts -Iserver/INCLUDE -Icommon/Include -include script_commands.h -include mlscript.h $1
