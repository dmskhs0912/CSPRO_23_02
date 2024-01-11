cc=g++
cflags = -g
target = HW3

objects = main.o str.o

$(target) : $(objects)
	$(cc) $(cflags) -o $(target) $(objects)

$(objects) : Str.h

.PHONY : clean
clean :
	rm $(target) $(objects)
