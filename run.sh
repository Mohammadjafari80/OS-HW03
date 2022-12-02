#!/bin/bash
echo "Compilation Started..."
gcc ipc.c Practical_Q_1f.o -lm
echo "Compilation Finished!"
echo "Running..."
/usr/bin/time --format='%C took %e seconds' ./a.out
echo "Finished!"


