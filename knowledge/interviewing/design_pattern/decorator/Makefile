objs=main.o
.cpp.o:
	g++ -g -c $?
main:$(objs)
	g++ $? -o $@ -lpthread
	rm -rf *.o core* tags 
clean:
	rm -rf main *.o core* tags 
