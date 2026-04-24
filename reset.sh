#!/bin/bash

rm stats.txt .hide_splash.txt main

echo "Game reset successfully. All stats and progress have been cleared."

echo "Do you want to reset the high score as well? (Type \"yes\" or \"no\")"
read answer
if [ "$answer" == "yes" ]; then
    rm $(cat filenames.txt)
    echo "High score reset successfully."
    rm filenames.txt
    fi
