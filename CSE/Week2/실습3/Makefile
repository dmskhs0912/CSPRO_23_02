cc=gcc
cflags = -W -g
target = main

objects = main.o String_Manipulation.o Output.o

$(target) : $(objects)
	$(cc) $(cflags) -o $(target) $(objects)

$(objects) : Header.h

.PHONY : clean
clean :
	rm $(target) $(objects)
