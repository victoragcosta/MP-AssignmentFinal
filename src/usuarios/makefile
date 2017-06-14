IDIR = ../../include
CC = g++
CFLAGS = -ftest-coverage -fprofile-arcs -I $(IDIR) 
LIBS = -lm -pthread ~/Documentos/googletest/googletest/gtest-all.o

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
	$(CC) -c -o $@ $< $(CFLAGS)

$(TDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< 


testes_usuarios: $(OBJ) $(TEST) $(ODIR)/grafo.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: gcov

gcov:
	cp *.c $(GCOVDIR)
	mv -f $(ODIR)/*.gcda $(ODIR)/*.gcno -t $(GCOVDIR)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.gcda $(ODIR)/*.gcno $(GCOVDIR)/* $(TDIR)/*.gcda $(TDIR)/*.gcno $(TDIR)/*.o $(ODIR)/*.o *.o testes_usuarios core $(INCDIR)/*~
