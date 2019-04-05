#!/bin/bash

set -x

find $MESON_SOURCE_ROOT -type f \( -iname '*.cpp' -or -iname '*.hpp' \) | xargs cat | grep -P '^#\s*include\s*<[\w/.]+>' | sed -e 's/^#\s\+/#/' -e 's/[[:space:]]*$//' | sort | uniq -d > $MESON_BUILD_ROOT/hw3.hpp
