#! /bin/bash

# execute the program for varios different arrays
for seed in {0..99990..10}
do
    for shrink in 1.05 1.1 1.15 1.2 1.25 1.3 1.35 1.4 1.45 1.5 1.55 1.6 1.65 1.7 1.75 1.8 1.85 1.9 1.95 2
    do
        printf "$seed,10000,7," >> outfile
        (time comb_shrink/comb_shrink ${ARRAYS_PATH}/arr_10000_7_${seed}.bin\
            $shrink 10000 0) >> outfile 2>&1
    done
done

# format the result as a csv file
head -n 1 outfile > temp0
awk 'f{print;f=0} /sys/{f=1}' outfile >> temp0
awk '$1 == "user" {print $2}' outfile > temp1
echo "seed,size,mode,shrink,cmp,mov,time" >> out.csv
paste temp0 temp1 | sed 's/\t/,/' >> out.csv

# remove leftovers
rm temp0 temp1 outfile
