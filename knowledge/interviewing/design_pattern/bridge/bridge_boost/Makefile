objs=main.o
.cpp.o:
	g++ -c $?
main:$(objs)
	g++ -g $? -o $@
	rm -rf *.o tags core* 
clean:
	rm -rf *.o tags core* main
