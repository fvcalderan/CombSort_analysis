all: gen load

gen:
	gcc gen_array.c -O3 -o gen -lm
load:
	gcc load_array.c -O3 -o load

clean:
	rm -f gen load
