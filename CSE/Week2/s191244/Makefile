cc = gcc
target = HW2
objects = main.o input.o count.o output.o

$(target): $(objects)
	$(cc) $(objects) -o $(target) -lm

$(objects): header.h

.PHONY : clean
clean :
	rm $(target) $(objects)