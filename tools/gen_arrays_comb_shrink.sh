#! /bin/bash

mkdir -p $ARRAYS_PATH

for seed in {0..99990..10}
do
    array_generator/gen ${ARRAYS_PATH}/arr_10000_7_${seed}.bin\
        10000 7 $seed
done
