g++ -fopenmp bubbleSortParallel.cpp -o bp
g++ bubbleSortSerial.cpp -o bs
./bs < in.txt > bs.txt
./bp < in.txt > bp.txt
diff bs.txt bp.txt