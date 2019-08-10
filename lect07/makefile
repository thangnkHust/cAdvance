all: run

run: dllist.o fields.o jrb.o jval.o graph.o dijkstra.o test.o
	gcc dllist.o fields.o jrb.o jval.o graph.o dijkstra.o test.o -o run

dllist.o: /Users/khacthangdev/Desktop/cAdvance/libfdr/dllist.c
	gcc -c /Users/khacthangdev/Desktop/cAdvance/libfdr/dllist.c

fields.o: /Users/khacthangdev/Desktop/cAdvance/libfdr/fields.c
	gcc -c /Users/khacthangdev/Desktop/cAdvance/libfdr/fields.c

jrb.o: /Users/khacthangdev/Desktop/cAdvance/libfdr/jrb.c
	gcc -c /Users/khacthangdev/Desktop/cAdvance/libfdr/jrb.c

jval.o: /Users/khacthangdev/Desktop/cAdvance/libfdr/jval.c
	gcc -c /Users/khacthangdev/Desktop/cAdvance/libfdr/jval.c

graph.o: /Users/khacthangdev/Desktop/cAdvance/Graph/graph.c
	gcc -c /Users/khacthangdev/Desktop/cAdvance/Graph/graph.c

dijkstra.o: /Users/khacthangdev/Desktop/cAdvance/Dijkstra/dijkstra.c
	gcc -c /Users/khacthangdev/Desktop/cAdvance/Dijkstra/dijkstra.c

test.o: test.c
	gcc -c test.c

clean: 
	rm -f *.o *~ run


