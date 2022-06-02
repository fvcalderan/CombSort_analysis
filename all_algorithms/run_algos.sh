#! /bin/bash

mkdir -p $ARRAYS_PATH

# execute the program for varios different arrays
for seed in {0..90..10}
do
    for size in 10 100 1000 10000 100000 1000000
    do
        for mode in {0..7}
        do
            for algo in {0..6}
            do
                printf "$seed,$size,$mode,$algo," >> outfile
                (time bin/sorts ${ARRAYS_PATH}/arr_${size}_${mode}_${seed}.bin\
                    $algo $size 0) >> outfile 2>&1
            done
        done
    done
done

# format the result as a csv file
head -n 1 outfile > temp0
awk 'f{print;f=0} /sys/{f=1}' outfile >> temp0
awk '$1 == "user" {print $2}' outfile > temp1
echo "seed,size,mode,algo,cmp,mov,time" >> out.csv
paste temp0 temp1 | sed 's/\t/,/' >> out.csv

# remove leftovers
rm temp0 temp1 outfile
