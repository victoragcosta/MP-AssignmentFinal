IDIR = ../../include
CC = g++
CFLAGS = -Wall -ftest-coverage -fprofile-arcs -I $(IDIR)

ODIR = ../obj
LDIR = ../../lib
TDIR = ../tests/product
GCOVDIR = ../gcov

LIBS = -lm -lgtest

_DEPS = error_level.h product.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = product.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_TEST = product_tests.o
TEST = $(patsubst %,$(TDIR)/%,$(_TEST))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

product_tests: $(OBJ) $(TEST)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

verify_tests:
	cppcheck product.c --enable=all
	valgrind --leak-check=full ./product_tests

.PHONY: my_gcov

mv_gcov:
	mv $(ODIR)/*.gcda $(GCOVDIR)
	mv $(ODIR)/*.gcno $(GCOVDIR)
	cp $(IDIR)/$(_DEPS) $(GCOVDIR)
	cp *.c $(GCOVDIR)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
