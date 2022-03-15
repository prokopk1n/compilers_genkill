#!/bin/bash
mkdir -p outputs
for file in tests/*.txt; do
  filename=$(basename "$file")
  echo ========== TEST "$filename" ==========
  ./gk < tests/"$filename" > outputs/"$filename"
  python3 check_tests.py answers/"$filename" outputs/"$filename"
done