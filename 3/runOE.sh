g++ -fopenmp oddEvenParallel.cpp -o op
g++ oddEvenSerial.cpp -o os
./op < in.txt > op.txt
./os < in.txt > os.txt
diff op.txt os.txt