#!/bin/bash

# Run tests

make all

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

for i in {1..8}
do

    echo "Running test strqueue_test_$i"
    ./strqueue_test_"${i}"_nodbg
    result=$?
    if [ $result -eq 0 ]; then
        echo -e "${GREEN}Test strqueue_test_${i}_nodbg passed${NC}"
    else
        echo -e "${RED}Test strqueue_test_${i}_nodbg failed with exit code $result${NC}"
    fi


    ./strqueue_test_"${i}"_dbg 2> my"${i}"log.log
    result=$?
    if [ $result -eq 0 ]; then
        if ! diff -q my"${i}"log.log logs/strqueue_test_"${i}".log; then
            echo -e "${RED}Test strqueue_test_${i}_dbg failed with wrong log output${NC}"
        else
            echo -e "${GREEN}Test strqueue_test_${i}_dbg passed${NC}"
        fi
    else
        echo -e "${RED}Test strqueue_test_${i}_dbg failed with exit code $result${NC}"
    fi


done

rm my*log.log