IDIR = ../../include
CC = g++
CFLAGS = -ftest-coverage -fprofile-arcs -I $(IDIR)
LIBS = -lm -lgtest

ODIR = ../obj
TDIR = ../tests/avaliacao
GCOVDIR = ../gcov
GRAFOSDIR = ../grafo

_DEPS = usuarios.h avaliacao.h aleatorio.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = usuarios.o avaliacao.o aleatorio.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_TEST = teste_avaliacao.o
TEST = $(patsubst %,$(TDIR)/%,$(_TEST))

$(ODIR)/%.o: %.cpp $(DEPS)
	cppcheck --enable=warning $<
	$(CC) -c -o $@ $< $(CFLAGS)

$(TDIR)/%.o: %.cpp $(DEPS)
	cppcheck --enable=warning $<
	$(CC) -c -o $@ $<

testes_avaliacao: $(OBJ) $(TEST) $(ODIR)/grafo.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: gcov


gcov:
	cp *.c $(GCOVDIR)
	mv -f $(ODIR)/*.gcda $(ODIR)/*.gcno -t $(GCOVDIR)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.gcda $(ODIR)/*.gcno $(GCOVDIR)/* $(TDIR)/*.gcda $(TDIR)/*.gcno $(TDIR)/*.o $(ODIR)/*.o *.o testes_usuarios core $(INCDIR)/*~
	rm testes_avaliacao
