#!/bin/bash
mkdir -p outputs
make du
for file in tests/*.txt; do
  filename=$(basename "$file")
  echo ========== TEST "$filename" ==========
  ./du < tests/"$filename" > outputs/"$filename"
  python3 check_tests.py answers/"$filename" outputs/"$filename"
done