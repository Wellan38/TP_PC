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

question1: primes.o question1.o
	gcc -Wall -pthread -lm -o $@ $^

question2: primes.o question2.o
	gcc -Wall -pthread -lm -o $@ $^

# add your own rules when you create new programs
%.o: %.c %.h
	gcc -Wall -pthread -o $@ -c $<

#########################
## program execution

run1: question1
	time ./question1

run2: question2
	time ./question2

#########################
## utilities

clean:
	rm -f *.o question1 question2 tiny.txt small.txt medium.txt large.txt many.txt 

