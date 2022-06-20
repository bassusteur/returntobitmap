#!/bin/bash
rm main
g++ main.cpp -o main -lGL -lglfw -lglut
echo "done"
sleep 1
./main