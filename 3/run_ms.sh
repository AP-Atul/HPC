g++ -fopenmp mergeSortParallel.cpp -o mp
g++ mergeSortSerial.cpp -o ms
./ms < in.txt > ms.txt
./mp < in.txt > mp.txt
diff mp.txt ms.txt
