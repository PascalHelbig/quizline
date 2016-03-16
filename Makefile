compile-and-run: compile run
compile:
	ecpg main.cpp question.cpp category.cpp sqlhelper.cpp
	g++ -I/usr/include/postgresql -c main.c question.c category.c sqlhelper.c
	g++ -o main main.o question.o category.o sqlhelper.o -L/usr/lib/psql -lecpg
run:
	./main
