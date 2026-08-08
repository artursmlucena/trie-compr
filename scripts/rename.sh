#!/usr/bin/env bash

for N in {1..6}; do
    echo "-> Renaming benched marks from 1e${N}..."

    cd "./1e${N}"

    mv ./benched-time-java "./benched-time-java-1e${N}"

    cd ..
done

echo "==> Done!"
