IDIR = ../../include
CC = g++
CFLAGS = -Wall -ftest-coverage -fprofile-arcs -I $(IDIR)

ODIR = ../obj
LDIR = ../../lib
TDIR = ../tests/product_search
GCOVDIR = ../gcov

LIBS = -lm -lgtest

_DEPS = error_level.h product_search.h product.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = product.o product_search.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_TEST = product_search_tests.o
TEST = $(patsubst %,$(TDIR)/%,$(_TEST))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

search_tests: $(OBJ) $(TEST)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

verify_tests:
	cppcheck ./product_search.c ./search_tests --enable=all
	valgrind --leak-check=full ./search_tests

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
