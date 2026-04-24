#!/bin/bash
if [ ! -f "stats.txt" ]; then
    touch stats.txt
    echo "100 0 0" > stats.txt
    fi
if [ ! -f ".hide_splash.txt" ]; then
    touch .hide_splash.txt
    echo "0" > .hide_splash.txt
    fi
if [ ! -f main ]; then
    g++ main.cpp -o main
    fi

./main