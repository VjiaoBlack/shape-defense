rm CMakeCache.txt
rm -r CMakeFiles/

CC=gcc CXX=g++ cmake .

make -j8

./Defense

gprof Defense gmon.out > gmon.data
