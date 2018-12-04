#!/bin/bash

echo "Copy player1.cpp"
cp compile/playerNum1.cpp src/playerNum.cpp
echo "Making player1.cpp"
make -j16
echo "copying player1"
cp -r -f bin/rosendal ~/player1/rosendal1

echo "Copy player2.cpp"
cp compile/playerNum2.cpp src/playerNum.cpp
echo "Making player2.cpp"
make -j16
echo "copying player2"
cp -r -f bin/rosendal ~/player2/rosendal2
