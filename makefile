OBJS = scanner.o bst.o node.o trees.o avl.o queue.o
OPTS = -Wall -g -std=c99

trees : $(OBJS)
	gcc $(OPTS) $(OBJS) -o trees -lm

trees.o : trees.c bst.h node.h scanner.h avl.h
	gcc $(OPTS) -c trees.c

scanner.o : scanner.c scanner.h
	gcc $(OPTS) -c scanner.c

node.o : node.c node.h
	gcc $(OPTS) -c node.c

bst.o : bst.c node.h queue.h
	gcc $(OPTS) -c bst.c

avl.o : avl.c node.h bst.h
	gcc $(OPTS) -c avl.c

queue.o : queue.c queue.h
	gcc $(OPTS) -c queue.c

test :
	trees -b corpus instr
clean :
	rm -f $(OBJS) trees
