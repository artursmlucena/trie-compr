#!/usr/bin/env bash

record=""

for N in {1..6}; do
    cd "1e$N" || exit 1

    record+=$(tail -n 1 stats)
    record+=$'\n'

    cd ..
done

printf "%s" "$record" > table_stats
