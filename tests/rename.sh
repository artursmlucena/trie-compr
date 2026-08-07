#!/usr/bin/env bash

for N in {1..5}; do
    echo "-> Renaming benched marks from 8e${N}..."

    cd "./8e${N}"

    mv ./benched-time-python "./benched-time-python-8e${N}"

    cd ..
done

echo "==> Done!"
