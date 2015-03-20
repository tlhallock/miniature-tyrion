#!/bin/bash


rm -f gmon.out outfile && make -j9 && LD_LIBRARY_PATH=opencv/prefix/lib/ ./LastIde

