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

Point: $(BINDIR)/rPoint.o $(LIBDIR)/libFC.a
	@echo Creating rPoint.exe...
	$(CC) -I src $< -o $(BINDIR)/r$@.exe -L lib -l FC $(ROOTLIB)

Vector: $(BINDIR)/rVector.o $(LIBDIR)/libFC.a
	@echo Creating rVector.exe...
	$(CC) -I src $< -o $(BINDIR)/r$@.exe -L lib -l FC $(ROOTLIB)

IntegralMC: $(BINDIR)/rIntegralMC.o $(LIBDIR)/libFC.a
	@echo Creating rIntegralMC.exe...
	$(CC) -I src $< -o $(BINDIR)/r$@.exe -L lib -l FC $(ROOTLIB)

Canhao: $(BINDIR)/rCanhao.o $(LIBDIR)/libFC.a
	@echo Creating rCanhao.exe...
	$(CC) -I src $< -o $(BINDIR)/r$@.exe -L lib -l FC $(ROOTLIB)

######### clean

tilde := $(wildcard */*~) $(wildcard *~)
exe := $(wildcard */*.exe) $(wildcard *.exe)
obj := $(wildcard */*.o) $(wildcard *.o) $(wildcard */*.so) $(wildcard */*.pcm) $(wildcard */*.d)

clean:
	@echo cleaning dir...
	rm -f $(exe) $(obj) $(tilde) $(LIBDIR)/libFC.a