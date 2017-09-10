objs=main.o
.c.o:
	g++ -g -c $<
main:$(objs)
	g++ $? -o $@ 
	rm -rf *.o 
clean:
	rm -rf *.o  main tags
