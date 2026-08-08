#!/usr/bin/env bash

set -euo pipefail

for N in {1..6}; do
    echo "-> Processing 1e${N}..."

    mv ./bench_time.sh ./stats.py "1e${N}/"

    cd "./1e${N}"

    for i in {1..100}; do
        ./bench_time.sh
    done

    mv ./benched_time ./benched-time-java

    python3 ./stats.py > ./stats

    mv ./bench_time.sh ./stats.py ..

    cd ..
done

echo "==> Done!"
