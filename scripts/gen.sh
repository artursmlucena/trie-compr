#!/usr/bin/env bash

set -euo pipefail

echo "-> Generating cases for 8e${1}..."

mv ./operation_generator.py "8e${1}/"

cd "./8e${1}"

python3 ./operation_generator.py > ./gen-cases-seed.txt

mv ./operation_generator.py ..


cd ..

echo "==> Done!"
