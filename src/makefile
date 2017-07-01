NOME_SAIDA=hub

IDIR =../include
CC=g++
EXT = c
LFLAGS = `sdl-config --libs` -lSDL2 #-lSDL2_image -lSDL2_mixer -lSDL2_ttf
CFLAGS=-Wall -g -fprofile-arcs -ftest-coverage -I $(IDIR) $(LFLAGS)

GCOVDIR=gcov
ODIR=obj
LDIR =../lib

LIBS=-lm /usr/lib/libgtest.a -lgtest -lpthread 

_DEPS = screen_management.h pagina_inicial.h graphical_structures.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o screen_management.o pagina_inicial.o graphical_structures.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(NOME_SAIDA): $(OBJ)
	$(CC) -o $@ $^ $(LIBS) $(CFLAGS)

obj/main.o: main.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

obj/screen_management.o: graphic/screen_management.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

obj/graphical_structures.o: graphic/graphical_structures.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

obj/pagina_inicial.o: graphic/pagina_inicial.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: %.$(EXT) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: graphic/%.$(EXT) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(ODIR)/* *~ core $(INCDIR)/*~ 

.PHONY: reset
reset:
	make clean
	rm -f teste
	rm -f $(GCOVDIR)/*
	rm -f ../valores.txt

.PHONY: mv_gcov_files
mv_gcov_files:
	mv $(ODIR)/*.gcda $(GCOVDIR)
	mv $(ODIR)/*.gcno $(GCOVDIR)
	cp *.c $(GCOVDIR)