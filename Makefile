CC = g++
PROG= app.out
TEST_PROG = test.out

ODIR :=bin
SDIR :=src
LDIR :=lib
TDIR :=tests

SOURCES := $(wildcard $(SDIR)/*.cpp)
OBJ := $(patsubst $(SDIR)/%,%,$(SOURCES))
OBJ := $(patsubst %.cpp,%.o,$(OBJ))
OBJ := $(addprefix $(ODIR)/,$(OBJ))

TEST_SRC := $(wildcard $(TDIR)/*.cpp)
TEST_OBJ := $(patsubst %.cpp,%.o,$(TEST_SRC))

LIBS:=
CFLAGS:=-I$(LDIR)/
CFLAGS_TEST := $(CFLAGS) -I$(SDIR)/

# Link program
$(ODIR)/$(PROG): $(OBJ)
	$(CC) -o $@ $(CFLAGS) $^ 

# Build object files
$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c -o $@ $^ $(CFLAGS) $(LIBS)

# Build lib used for testing
$(TDIR)/catch_amalgamated.o: $(LDIR)/catch_amalgamated.cpp
	$(CC) -c -o $@ $(CFLAGS) $^ 

# Build object files for tests
$(TDIR)/%.o: $(TDIR)/%.cpp
	$(CC) -c -o $@ $(CFLAGS_TEST) $^ 

# Link test objects to make test program
$(TDIR)/$(TEST_PROG) : $(TEST_OBJ) $(TDIR)/catch_amalgamated.o $(patsubst $(ODIR)/main.o, ,$(OBJ)) 
	$(CC) -o $@ $^

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o $(ODIR)/*.out $(TDIR)/*.o $(TDIR)/*.out

.PHONY: run
run:
	./$(ODIR)/$(PROG)

.PHONY: test
test : $(TDIR)/$(TEST_PROG) 
	./$(TDIR)/$(TEST_PROG)


