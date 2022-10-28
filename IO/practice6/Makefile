libmymath.a:add.o sub.o
	ar -rc $@ $^
%.o:%.c
	gcc -c $<

.PHONY:clean
clean:
	rm -rf libmymath.a *.o output

.PHONY:output
output:
	mkdir output
	cp libmymath.a output
	cp *.h output 