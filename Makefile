default: help

help:
	@echo Useful targets:
	@echo "  small.txt medium.txt large.txt many.txt:  generate some input files "
	@echo "  question1 question2: compile your programs"
	@echo "  run1 run2:  run your programs through the 'time' utility"
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
	gcc -Wall -pthread -lm -o $@ $^

# add your own rules when you create new programs
%.o: %.c
	gcc -Wall -pthread -o $@ -c $<

primes.o: primes.c primes.h
	gcc -Wall -pthread -o $@ -c $<

#########################
## program execution

run%: question%
	time ./question$*


#########################
## utilities

clean:
	rm -f *.o question* tiny.txt small.txt medium.txt large.txt many.txt 

