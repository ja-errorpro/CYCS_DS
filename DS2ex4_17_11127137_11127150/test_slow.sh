g++ DS2ex4_*.cpp -o test

start_time=$(date +%s)
./test < test1.in
end_time=$(date +%s)
cost=$[ $end_time-$start_time ]
echo "執行時間："