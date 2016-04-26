default: help

help:
	@echo Useful targets:
	@echo "  small.txt medium.txt large.txt many.txt:  generate some input files "
	@echo "  question%: compile your programs for basic questions"
	@echo "  race: compile the program for the race challenge"
	@echo "  run%:  run your programs through the 'time' utility"
	@echo "  clean:  delete all generated files"

#########################
# workload generation

tiny.txt:
	./generator.cs 20 20 0 > $@

small.txt:
	./generator.cs 20 32 50 > $@

medium.txt:
	./generator.cs 20 50 50 > $@

large.txt:
	./generator.cs 20 64 50 > $@

many.txt:
	./generator.cs 1000 50 75 > $@

#########################
## program compilation

question%: primes.o question%.o
	gcc -Wall -pthread -lm -o $@.exe $^

test_alex: primes.o test_alex.o hash.o
	gcc -Wall -pthread -lm -o $@.exe $^
	
lenstra: lenstra.o primes.o
	gcc -Wall -pthread -lm -o $@.exe $^
	
race: speed.o primes.o hash.o
	gcc -Wall -pthread -lm -o $@.exe $^

# add your own rules when you create new programs
%.o: %.c
	gcc -Wall -pthread -o $@ -c $<
	
question10: hash.o

primes.o: primes.c primes.h
	gcc -Wall -pthread -o $@ -c $<

hash.o: hash.c hash.h
	gcc -Wall -pthread -o $@ -c $<

#########################
## program execution

run%: question%
	time ./question$*


#########################
## utilities

clean:
	rm -f *.o *.exe tiny.txt small.txt medium.txt large.txt many.txt 

