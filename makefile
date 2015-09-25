#**************************************
# makefile for decision_tree program
PROG = Decision_Tree
CC = g++-4.9
CPPFLAGS = -g -Wall -std=c++11
OBJS = main.o Decision_Tree.o

#**************************************
# targets
$(PROG) : $(OBJS)
	$(CC) $(CPPFLAGS) -o $(PROG) $(OBJS)

main.o :
	$(CC) $(CPPFLAGS) -c main.cpp

# xml_parser.o : xml_parser.h xml_parser.cpp
# 	$(CC) -c xml_parser.cpp

Decision_Tree.o : Decision_Tree.h Decision_Tree.cpp
	$(CC) $(CPPFLAGS) -c Decision_Tree.cpp

clean:
	rm -f core $(PROG) $(OBJS)

run: 
	./$(PROG)