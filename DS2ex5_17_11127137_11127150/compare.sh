#!/bin/bash

read -p "Input Cpp File Name: " file_name

rm -f test

g++ $file_name -o test

if [ ! -f test ]; then
    echo -e "\033[1;31mCompile Error\033[0m"
    exit 1
fi

CPUTIME=$(time ./test < test1.in)

file_num=(501 502 503 504 505 506)
result=0
echo "===================="
for i in ${file_num[@]};
do
    echo "正在測試: $i"
    DIFF1=$(diff ordered$i.bin ordered"$i"_ans.bin)
    result=$((result + $?))
    if [ $result -ne 0 ]; then
        echo "WA"
        echo "$DIFF1"
    fi
    DIFF2=$(diff ordered$i.bin ordered"$i"_ans.bin)
    if [ $result -ne 0 ]; then
        echo "WA"
        echo "$DIFF2"
    fi
    result=$((result + $?))
    echo "===================="
done

if [ $result -eq 0 ]; then
    echo -e "\033[1;32mAC, exit code: $result \033[0m"
else
    echo -e "\033[1;31mWA, exit code: $result \033[0m"
fi
