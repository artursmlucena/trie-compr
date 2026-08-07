#!/usr/bin/env bash

for N in {1..6}; do
    echo "-> Wiping benched marks from 1e${N}..."

    cd "./1e${N}"

    rm ./benched-time-c
    rm ./benched-time-java
    rm ./benched-time-java-a
    rm ./benched-time-python
    rm ./benched-time-rust

    cd ..
done

echo "==> Done!"
