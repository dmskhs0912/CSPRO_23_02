cc = gcc
target = Hello_world
objects = main.o He.o llo.o blank.o World.o

$(target): $(objects)
	$(cc) -o $(target) $(objects)

$(objects): header.h

.PHONY : clean
clean :
	rm $(target) $(objects)
