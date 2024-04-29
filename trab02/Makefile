ROOTLIB := $(shell root-config --libs)
ROOTINC := $(shell root-config --incdir)

BINDIR := bin
LIBDIR := lib

CCFLAGS := -pedantic

CC := g++ -std=c++11 

VPATH = main:src

ROOTLIB := $(shell root-config --libs)
ROOTINC := $(shell root-config --incdir)

SRC := $(wildcard src/*.C)
OBJ := $(patsubst %.C, $(BINDIR)/%.o, $(notdir $(SRC)))
INC := $(wildcard src/*.h)

# lib

lib: $(LIBDIR)/libFC.a

$(LIBDIR)/libFC.a: $(OBJ) 
	@echo Making lib... 
	ar ruv $@ $^
	ranlib $@
	@echo

# trab02

trab02: $(BINDIR)/main_trab02.o $(LIBDIR)/libFC.a 
	@echo Compiling and linking... 
	$(CC) -I src $< -o $(BINDIR)/main_$@.exe -L lib -l FC $(ROOTLIB)
	@echo

$(BINDIR)/%.o: %.C | $(INC)
	@echo Compiling... $<
	$(CC) -I src -I $(ROOTINC) -c $< -o $@
	@echo

# clean

tilde := $(wildcard */*~) $(wildcard *~)
exe := $(wildcard */*.exe) $(wildcard *.exe)
obj := $(wildcard */*.o) $(wildcard *.o) $(wildcard */*.so) $(wildcard */*.pcm) $(wildcard */*.d)

clean:
	@echo Cleaning directory...
	rm -f $(exe) $(obj) $(tilde) $(LIBDIR)/libFC.a
	@echo