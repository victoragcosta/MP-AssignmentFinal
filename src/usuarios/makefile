IDIR = ../../include
CC = g++
CFLAGS = -ftest-coverage -fprofile-arcs -I $(IDIR)
LIBS = -lm -lgtest

ODIR = ../obj
TDIR = ../tests/usuarios
GCOVDIR = ../gcov
GRAFOSDIR = ../grafo

_DEPS = usuarios.h aleatorio.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = usuarios.o aleatorio.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_TEST = teste_usuarios.o
TEST = $(patsubst %,$(TDIR)/%,$(_TEST))

$(ODIR)/grafo.o: $(GRAFOSDIR)/grafo.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: %.c $(DEPS)
	cppcheck --enable=warning $<
	$(CC) -c -o $@ $< $(CFLAGS)

$(TDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

testes_usuarios: $(OBJ) $(TEST) $(ODIR)/grafo.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: gcov

gcov:
	mv $(ODIR)/*.gcda $(GCOVDIR)
	mv $(ODIR)/*.gcno $(GCOVDIR)
	cp $(IDIR)/$(_DEPS) $(GCOVDIR)
	cp *.c $(GCOVDIR)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
