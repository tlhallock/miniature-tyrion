#!/bin/bash

echo "SOURCES += \\"
find src -name '*.cpp' | sed 's/$/ \\/' | sed 's/^/        /'  | sort -u
echo " "

echo "HEADERS += \\"
find src -name '*.h' | sed 's/$/ \\/' | sed 's/^/        /' | sort -u
echo " "
