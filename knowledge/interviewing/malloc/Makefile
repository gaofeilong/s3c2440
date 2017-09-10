objs=main.o
.c.o:
	cc -g -c $<
main:$(objs)
	cc $? -o $@
	rm -rf *.o 
clean:
	rm -rf *.o  main tags
