#!/bin/bash
echo "Compilation Started..."
gcc ipc.c Practical_Q_1f.o -lm
echo "Compilation Finished!"
echo "Running..."
time ./a.out
echo "Finished!"


