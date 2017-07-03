IDIR = ../../include
CC = g++
CFLAGS = -Wall -ftest-coverage -fprofile-arcs -I $(IDIR)

ODIR = ../obj
LDIR = ../../lib
TDIR = ../tests/product_search
GCOVDIR = ../gcov

LIBS = -lm -lgtest

_DEPS = error_level.h product.h product_search.h valid_index.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = product.o  valid_index.o product_search.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_TEST = product_search_tests.o
TEST = $(patsubst %,$(TDIR)/%,$(_TEST))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TDIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

search_tests: $(OBJ) $(TEST)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

verify_tests:
	cppcheck ./product_search.cpp ./search_tests --enable=all
	valgrind --leak-check=full ./search_tests

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
	rm search_tests
