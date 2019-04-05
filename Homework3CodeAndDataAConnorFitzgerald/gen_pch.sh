#!/bin/bash

find $1 -maxdepth 1 -type f \( -iname '*.cpp' -or -iname '*.hpp' \) | xargs cat | grep -P '^#\s*include\s*<[\w/.]+>' | sed -e 's/^#\s\+/#/' -e 's/[[:space:]]*$//' | sort | uniq -d > hw3.hpp
