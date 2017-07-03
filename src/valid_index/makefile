IDIR = ../../include
CC = g++
CFLAGS = -Wall -ftest-coverage -fprofile-arcs -I $(IDIR)

ODIR = ../obj
GCOVDIR = ../gcov

LIBS = -lm -lgtest

_DEPS = valid_index.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

make:
	$(CC) -c valid_index.cpp $(CFLAGS) $(LIBS)
	mv valid_index.o $(ODIR)

.PHONY: my_gcov

mv_gcov:
	cp $(DEPS) $(GCOVDIR)
	cp *.cpp $(GCOVDIR)
	mv *.gcda $(GCOVDIR)
	mv *.gcno $(GCOVDIR)
	mv $(ODIR)/*.gcda $(GCOVDIR)
	mv $(ODIR)/*.gcno $(GCOVDIR)

.PHONY: clean

clean:
	rm $(ODIR)/valid_index.o *.gcno *.gcda
