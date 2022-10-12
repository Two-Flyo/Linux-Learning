.PHONY:all
all:exe exec

exec:exec.c
	gcc -o $@ $^
exe:exe.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -f exec exe
