#! /bin/bash

mkdir -p $ARRAYS_PATH

for size in 10 100 1000 10000 100000 1000000
do
    for mode in {0..7}
    do
        for seed in {0..90..10}
        do
            array_generator/gen ${ARRAYS_PATH}/arr_${size}_${mode}_${seed}.bin\
                $size $mode $seed
        done
    done
done
