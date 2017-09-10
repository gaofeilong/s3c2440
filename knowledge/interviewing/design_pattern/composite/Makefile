objs=main.o
.cpp.o:
	g++ -g -c $?
main:$(objs)
	g++ $? -o $@
	rm -rf *.o tags core* 
clean:
	rm -rf *.o tags core* main
