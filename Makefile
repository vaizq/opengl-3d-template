CC = g++
PROG= app.out

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

$(ODIR)/$(PROG): $(OBJ)
	$(CC) -o $@ $(CFLAGS) $^ 


$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c -o $@ $^ $(CFLAGS) $(LIBS)


$(TDIR)/catch_amalgamated.o: $(LDIR)/catch_amalgamated.cpp
	$(CC) -c -o $@ $(CFLAGS) $^ 

$(TDIR)/%.o: $(TDIR)/%.cpp
	$(CC) -c -o $@ $(CFLAGS_TEST) $^ 

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o $(ODIR)/*.out $(TDIR)/*.o $(TDIR)/*.out

.PHONY: run
run:
	./$(ODIR)/$(PROG)

.PHONY: test
test: $(TEST_OBJ) $(TDIR)/catch_amalgamated.o $(patsubst $(ODIR)/main.o, ,$(OBJ)) 
	$(CC) -o $(TDIR)/test.out $^
	./$(TDIR)/test.out


