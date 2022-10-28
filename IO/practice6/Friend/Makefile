Test:Test.c
    # 这里只是告知编译器头文件库路径在哪里,当程序编译好的时候,此时就已经和编译器无关了
	gcc -o $@ $^ -I ./lib -L ./lib -l mymath
.PHONY:clean
clean:
	rm -f Test