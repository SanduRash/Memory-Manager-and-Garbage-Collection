# This is (at least the start of) a makefile for CSC45500, 
#   project#1
## NOTE: any LINE starting with a '#' in a Makefile is a comment

#OPTIM=-O
DBG=-g
OPTS=$(DBG) $(OPTIM) -Wall -ansi -pedantic -std=c++20

CC=g++ $(OPTS)  -c
LNK=g++

OBJS=Grammar.o Token.o TokenStream.o main.o Variable.o MemoryList.o
GLBL=Makefile Grammar.hpp Token.hpp TokenStream.hpp Variable.hpp MemoryList.hpp

beautifier: $(OBJS)
	$(LNK) -o beautifier $(OBJS)

main.o: main.cpp Token.hpp $(GLBL)
	$(CC) main.cpp

Grammar.o: Grammar.cpp Grammar.hpp $(GLBL)
	$(CC) Grammar.cpp

Token.o: Token.cpp Token.hpp $(GLBL)
	$(CC) Token.cpp

TokenStream.o: TokenStream.cpp TokenStream.hpp $(GLBL)
	$(CC) TokenStream.cpp

Variable.o: Variable.cpp Variable.hpp $(GLBL)
	$(CC) Variable.cpp

MemoryList.o: MemoryList.cpp MemoryList.hpp $(GLBL)
	$(CC) MemoryList.cpp

clean:
	/bin/rm -f *.o beautifier *~

