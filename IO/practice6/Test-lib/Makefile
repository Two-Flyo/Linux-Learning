# 形成一个动态链接的共享库
libmymath.so:add.o sub.o
	gcc -shared -o $@ $^


# 产生.o目标文件,程序内部的地址方案是:与位置无关,库文件可以在内存的任何
# 位置加载,而且不影响和其他程序的关联性
%.o:%.c
	gcc -fPIC -c $<

.PHONY:clean
clean:
	rm -f libmymath.so

.PHONY:lib
lib:
	mkdir lib
	cp *h lib
	cp libmymath.so lib