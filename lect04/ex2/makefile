all: run

run: dllist.o fields.o jrb.o jval.o ex2.o
	gcc dllist.o fields.o jrb.o jval.o ex2.o -o run

dllist.o: /Users/khacthangdev/Desktop/cAdvance/libfdr/dllist.c
	gcc -c /Users/khacthangdev/Desktop/cAdvance/libfdr/dllist.c

fields.o: /Users/khacthangdev/Desktop/cAdvance/libfdr/fields.c
	gcc -c /Users/khacthangdev/Desktop/cAdvance/libfdr/fields.c

jrb.o: /Users/khacthangdev/Desktop/cAdvance/libfdr/jrb.c
	gcc -c /Users/khacthangdev/Desktop/cAdvance/libfdr/jrb.c

jval.o: /Users/khacthangdev/Desktop/cAdvance/libfdr/jval.c
	gcc -c /Users/khacthangdev/Desktop/cAdvance/libfdr/jval.c

ex2.o: ex2.c
	gcc -c -I/Users/khacthangdev/Desktop/cAdvance/libfdr/ ex2.c

clean: 
	rm -f *.o *~ run


