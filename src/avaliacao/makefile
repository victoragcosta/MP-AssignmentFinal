IDIR = ../../include
CC = g++
CFLAGS = -ftest-coverage -fprofile-arcs -I $(IDIR) 
LIBS = -lm -lgtest

ODIR = ../obj
TDIR = ../tests/avaliacao
GCOVDIR = ../gcov
GRAFOSDIR = ../grafo

_DEPS = usuarios.h avaliacao.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = usuarios.o avaliacao.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_TEST = teste_avaliacao.o
TEST = $(patsubst %,$(TDIR)/%,$(_TEST))

$(ODIR)/grafo.o: $(GRAFOSDIR)/grafo.c $(DEPS)
	cppcheck --enable=warning $<
	$(CC) -c -o $@ $< $(CFLAGS)
	
$(ODIR)/usuarios.o: ../usuarios/usuarios.c $(DEPS)
	cppcheck --enable=warning $<
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: %.c $(DEPS)
	cppcheck --enable=warning $<
	$(CC) -c -o $@ $< $(CFLAGS)

$(TDIR)/%.o: %.c $(DEPS)
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
