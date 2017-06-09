IDIR = ../../include
CC = g++
CFLAGS = -Wall -ftest-coverage -fprofile-arcs -I $(IDIR)

ODIR = ../obj
LDIR = ../../lib
TDIR = ../tests/product_search
GCOVDIR = ../gcov

LIBS = -lm -lgtest

_DEPS = product_search.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = product_search.o
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
	cppcheck product_search.c --enable=all
	valgrind --leak-check=full ./search_tests

.PHONY: my_gcov

mv_gcov:
	mv $(ODIR)/*.gcda $(GCOVDIR)
	mv $(ODIR)/*.gcno $(GCOVDIR)
	cp $(IDIR)/$(_DEPS) $(GCOVDIR)
	cp *.c $(GCOVDIR)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
