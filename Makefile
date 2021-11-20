IDIR =./include
CC=g++
CFLAGS=-I$(IDIR)

ODIR=./build
SDIR=./source
LDIR =./lib

LIBS=-lm

_DEPS = grammaAnalysis.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = grammaAnalysis.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

grammaAnalysis: $(OBJ)
	$(CC) -o $(ODIR)/$@ $^ $(CFLAGS) $(LIBS)

$(OBJ): $(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 