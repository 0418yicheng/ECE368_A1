# ***
# *** DO NOT modify this file 
# ***

WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 

SRCS = a1.c
OBJS = $(SRCS:%.c=%.o)

a1: $(OBJS) 
	$(GCC) $(OBJS) -o a1

.c.o: 
	$(GCC) -c ./$*.c 

test0:
	./a1.exe ./testcase_0.txt
	diff output.txt output_0.txt

clean: # remove all machine generated files
	rm -f hw02 *.o output?? sum_output.txt