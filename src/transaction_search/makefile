IDIR = ../../include
CC = g++
CFLAGS = -Wall -g -ftest-coverage -fprofile-arcs -I $(IDIR)

ODIR = ../obj
LDIR = ../../lib
TDIR = ../tests/transaction_search
GCOVDIR = ../gcov

LIBS = -lm -lgtest

_DEPS = error_level.h product.h transaction.h transaction_search.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = product.o transaction.o transaction_search.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_TEST = transaction_search_tests.o
TEST = $(patsubst %,$(TDIR)/%,$(_TEST))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

transaction_search_tests: $(OBJ) $(TEST)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

verify_tests:
	cppcheck ./transaction_search.c ./transaction_search_tests --enable=all
	valgrind --leak-check=full ./transaction_search_tests

.PHONY: my_gcov

mv_gcov:
	cp $(DEPS) $(GCOVDIR)
	cp *.c $(GCOVDIR)
	mv $(TDIR)/*.gcda $(GCOVDIR)
	mv $(TDIR)/*.gcno $(GCOVDIR)
	mv $(ODIR)/*.gcda $(GCOVDIR)
	mv $(ODIR)/*.gcno $(GCOVDIR)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
