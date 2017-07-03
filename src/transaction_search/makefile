IDIR = ../../include
CC = g++
CFLAGS = -Wall -g -ftest-coverage -fprofile-arcs -I $(IDIR)

ODIR = ../obj
LDIR = ../../lib
TDIR = ../tests/transaction_search
GCOVDIR = ../gcov

LIBS = -lm -lgtest

_DEPS = avaliacao.h error_level.h grafo.h product.h transaction.h transaction_search.h usuarios.h valid_index.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = avaliacao.o grafo.o product.o transaction.o transaction_search.o usuarios.o valid_index.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_TEST = transaction_search_tests.o
TEST = $(patsubst %,$(TDIR)/%,$(_TEST))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TDIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

transaction_search_tests: $(OBJ) $(TEST)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

verify_tests:
	cppcheck ./transaction_search.cpp ./transaction_search_tests --enable=all
	valgrind --leak-check=full ./transaction_search_tests

.PHONY: my_gcov

mv_gcov:
	cp $(DEPS) $(GCOVDIR)
	cp *.cpp $(GCOVDIR)
	mv $(TDIR)/*.gcda $(GCOVDIR)
	mv $(TDIR)/*.gcno $(GCOVDIR)
	mv $(ODIR)/*.gcda $(GCOVDIR)
	mv $(ODIR)/*.gcno $(GCOVDIR)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ $(TDIR)/*.gcda $(TDIR)/*.gcno $(TDIR)/*.o $(ODIR)/*.o
	rm transaction_search_tests
