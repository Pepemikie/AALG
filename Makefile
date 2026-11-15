#-----------------------
# Makefile Práctica 2 - Ziqi Zhoulin y José Miguel Romero Oubiña
#-----------------------

CC = gcc -ansi -pedantic
CFLAGS = -Wall
EXE = exercise4 exercise5

all : $(EXE)

.PHONY : clean cleanpng cleanall
clean :
	rm -f *.o core *.log $(EXE)

cleanpng:
	rm -f *.png

cleanall: clean cleanpng
	rm -f *.dat

$(EXE) : % : %.o sorting.o times.o permutations.o
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -o $@ $@.o sorting.o times.o permutations.o

permutations.o : permutations.c permutations.h
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $<

sorting.o : sorting.c sorting.h
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $<

times.o : times.c times.h
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $<

exercise4_test:
	@echo Running exercise4
	@./exercise4 -size 8

exercise5_test:
	@echo Running exercise5
	@./exercise5 -num_min 100 -num_max 2000 -incr 100 -numP 100 -outputFile resultados.dat

valgrind_exercise4:
	@echo Running valgrind on exercise4
	@valgrind --leak-check=full -s ./exercise4 -size 5

valgrind_exercise5:
	@echo Running valgrind on exercise5
	@valgrind --leak-check=full -s ./exercise5 -num_min 10 -num_max 50 -incr 10 -numP 5 -outputFile resultados.dat
graficas: exercise5_test
	@gnuplot graficas.gp