#!/bin/bash

while true; do
    echo "Enter the filename to save your stats (e.g., highscore.txt):"
    read filename

    if [ -z "$filename" ]; then
        echo "Filename cannot be empty. Please try again."
        continue
    fi

    if [ "$filename" == "stats.txt" ]; then
        echo "Filename cannot be stats.txt. Please try again."
        continue
    fi

    if [ -f "$filename" ]; then
        echo "File already exists. Do you want to overwrite it? (Type \"yes\" or \"no\")"
        read answer
        if [ "$answer" != "yes" ]; then
            echo "Stats not saved. Please try again."
            continue
        fi
    fi

    touch "$filename"
    if [ $? -ne 0 ]; then
        echo "Error creating file. Please try again."
        continue
    fi

    cat stats.txt > "$filename"
    echo "Stats saved to $filename."
    break
done
