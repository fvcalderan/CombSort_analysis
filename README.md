# CombSort_analysis
An analysis of the Comb Sort algorithm

## Article link

This repository contains the source code for [this article](https://fvcalderan.github.io/myworks/articles/comb_sort.pdf).

## Abstract

 Comb Sort is an unstable sorting algorithm that betters Bubble Sort by first comparing elements that are far apart and by progressively reducing this gap until the compared elements are directly adjacent to one another. At this point, it behaves exactly like the Bubble Sort. The purpose of adding said gap is to eliminate small values at the end of the array (assuming an ascending sort), since they are accountable for the biggest slowdowns in a Bubble Sort. An analysis of the algorithm shows its average performance is significantly better than Bubble Sort's. This paper also exhibits many tests that display how Comb Sort stacks up against 6 other algorithms: Bubble Sort, Heap Sort, Insertion Sort, Merge Sort, Quick Sort and Selection Sort using different array sizes and starting distributions.

## Project Solution
```
.
├── LICENSE
├── README.md
├── all_algorithms
│   ├── include
│   │   └── sorts.h
│   ├── makefile
│   ├── run_algos.sh
│   └── src
│       ├── main.c
│       └── sorts.c
└── tools
    ├── array_generator
    │   ├── gen_array.c
    │   ├── load_array.c
    │   └── makefile
    ├── comb_shrink
    │   ├── comb_shrink.c
    │   └── makefile
    ├── gen_arrays_algos.sh
    ├── gen_arrays_comb_shrink.sh
    └── run_comb_shrink.sh
```

## How the project is structured

Inside **all_algorithms** folder lies the source code to run the comparison between Comb Sort, Insertion Sort, Selection Sort, Bubble Sort, Heap Sort, Merge Sort and Quick Sort. The main function can be found inside **src/main.c** and the algorithms can be found inside **src/sorts.c**. The **sorts.h** header file contains function prototypes and the `sort` abstract data type.

The **tools** folder contains helper programs. The **array_generator** folder contains programs to generate arrays (**gen_arrays**) and to read them afterwards (**load_array**). The **comb_shrink** folder contains the program to run Comb Sort with a customized shrink constant value.

## Compile the program

Go to each one of these folders:
- all_algorithms
- tools/array_generator
- tools/comb_shrink

and run:
```
make
```

## Run the program

### Using scripts

Before proceeding, make sure you have **Bash** installed and that `/bin/bash` is not a symlink to another shell, like **Zsh**. Although other shells may be able to run the scripts, they were not tested.

The first step is generating arrays to feed the programs. There are two different pre-made array generation Bash scripts: **gen_arrays_algos.sh** and **gen_arrays_comb_shrink.sh**. The first one generates arrays to run with the main program, while the second one generates arrays to run with the **comb_shrink** program. To choose the folder to where the arrays will be saved, export `ARRAYS_PATH` variable, like so:
```bash
export ARRAYS_PATH="/path/to/arrays"
```

Once the output folder has been chosen, make the scripts executable with:
```
chmod +x gen_arrays_algos.sh
chmod +x gen_arrays_comb_shrink.sh
```

Then you may run the scripts.

**Be careful to not run both scripts with the same array path!** I suggest doing the following:

```bash
export ARRAYS_PATH="algos_arrays"
./gen_arrays_algos.sh
export ARRAYS_PATH="shrink_arrays"
./gen_arrays_comb_shrink.sh
```
Or doing step by step if `nohup` is needed. You can always check the environment variables exported running `printenv`.

Having generated the arrays, there are two scripts to run: **run_algos.sh** inside **all_algorithms** and **run_comb_shrink.sh** inside **tools**. Before running the scripts, make sure to have the correct `ARRAYS_PATH` set (each time) and that the scripts are executable. Both scripts will take a while to run, so using `nohup` and launching in the background is a good idea:
```
nohup ./run_algos.sh &
```
The output of **run_algos.sh** and **run_comb_shrink.sh** are CSV files that can be used to generate tables and plots using your favorite software. I, personlly, used **Python** + **Pandas** + **Matplotlib** to generate the plots.

If you want to generate and/or run a different set of arrays, you can modify the `for` loops inside the Bash scripts or execute the C programs manually.

### Manually running the programs

To run the programs yourself, specific sets of arguments are needed for each program:
```
./gen file_name size mode seed
./load file_name size
./comb_shrink file_name shrink size print
./sorts file_name method size print
```
The arguments should be intuitive to understand by their names, but you can always check the source code to verify what they mean. For instance: the `mode` argument of the `gen` program is a number that defines the rules to generate the elements inside the generated array:
- 0 - ordered unique
- 1 - inversely ordered unique
- 2 - almost ordered unique
- 3 - random unique
- 4 - ordered
- 5 - inversely ordered
- 6 - almost ordered
- 7 - random

and the `method` argument of the `sorts` program is a number the represents which sorting algorithm will be used:
- 0 - insertion sort
- 1 - selection sort
- 2 - bubble sort
- 3 - heap sort
- 4 - merge sort
- 5 - quick sort
- 6 - comb sort

So to run the **Comb Sort** algorithm to sort an array which file is named **arrays/my_array.bin** of size **1000000** and **print** the sorted elements to the screen, you may run something like:
```bash
./sorts arrays/my_array.bin 6 1000000 1
```
And, of course, to get the CPU time, you would actually run something like:
```bash
time ./sorts arrays/my_array.bin 6 1000000 1
```
Finally, you can completely ignore the **array_generator** and generate the binary files yourself using your programming language or hex editor of choice. The only restriction is that the elements must be C signed integers.

## License

```
BSD 3-Clause License

Copyright (c) 2022, fvcalderan
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
```