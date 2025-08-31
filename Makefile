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

# test0:
# 	a1 .\testcases\input\testcase_0.txt
# 	diff ./output.txt .\testcases\expected/output_0.txt
test0:
	a1 .\testcases\input\testcase_0.txt
	powershell -Command "(Get-Content output.txt) -replace '`r' | Set-Content output_unix.txt"
	diff output_unix.txt output_0.txt

test1:
	a1 ./testcases/input/testcase_1.txt
	diff ./output.txt ./testcases/expected/output_1.txt

test2:
	a1 ./testcases/input/testcase_2.txt
	diff ./output.txt ./testcases/expected/output_2.txt

test3:
	a1 ./testcases/input/testcase_3.txt
	diff ./output.txt ./testcases/expected/output_3.txt

clean:
	rm -f *.o a1 output.txt *.exe