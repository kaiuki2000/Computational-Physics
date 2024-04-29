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

lib: $(LIBDIR)/libFC.a

$(LIBDIR)/libFC.a: $(OBJ) 
	@echo make lib...
	ar ruv $@ $^
	ranlib $@

%.exe: $(BINDIR)/%.o $(LIBDIR)/libFC.a 
	@echo compiling and linking... 
	$(CC) -I src $< -o $(BINDIR)/$@ -L lib -l FC $(ROOTLIB)

$(BINDIR)/%.o: %.C | $(INC)
	@echo compiling... $<
	$(CC) -I src -I $(ROOTINC) -c $< -o $@

prob1a: $(BINDIR)/prob1a.o $(LIBDIR)/libFC.a
	@echo Creating prob1a.exe...
	$(CC) -I src $< -o $(BINDIR)/$@.exe -L lib -l FC $(ROOTLIB)

prob1b: $(BINDIR)/prob1b.o $(LIBDIR)/libFC.a
	@echo Creating prob1b.exe...
	$(CC) -I src $< -o $(BINDIR)/$@.exe -L lib -l FC $(ROOTLIB)

prob2: $(BINDIR)/prob2.o $(LIBDIR)/libFC.a
	@echo Creating prob2.exe...
	$(CC) -I src $< -o $(BINDIR)/$@.exe -L lib -l FC $(ROOTLIB)

# clean

tilde := $(wildcard */*~) $(wildcard *~)
exe := $(wildcard */*.exe) $(wildcard *.exe)
obj := $(wildcard */*.o) $(wildcard *.o) $(wildcard */*.so) $(wildcard */*.pcm) $(wildcard */*.d)
pdf := $(wildcard *.pdf)

clean:
	@echo cleaning dir...
	rm -f $(exe) $(obj) $(tilde) $(pdf) $(LIBDIR)/libFC.a