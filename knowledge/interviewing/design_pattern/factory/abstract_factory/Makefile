objs=main.o
.c.o:
	g++ -g -c $<
main:$(objs)
	g++ $? -o $@ -lpthread
	rm -rf *.o 
clean:
	rm -rf *.o  main tags
