CC = g++
CC_C = gcc

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

LIB_SOURCES := $(wildcard $(LDIR)/*.c*)
LIB_OBJ := $(patsubst $(LDIR)/%,%,$(LIB_SOURCES))
LIB_OBJ := $(patsubst %.c,%.o,$(LIB_OBJ))
LIB_OBJ := $(patsubst %.cpp,%.o,$(LIB_OBJ))
LIB_OBJ := $(addprefix $(ODIR)/,$(LIB_OBJ))


TEST_SRC := $(wildcard $(TDIR)/*.cpp)
TEST_OBJ := $(patsubst %.cpp,%.o,$(TEST_SRC))

LIBS := -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl


CFLAGS := -I$(LDIR)/ $(LIBS)
CFLAGS_TEST := $(CFLAGS) -I$(SDIR)/

$(ODIR)/$(PROG) : $(OBJ) $(LIB_OBJ)
	$(CC) -o $@ $^ $(CFLAGS) 

# Build object files from sources
$(ODIR)/%.o : $(SDIR)/%.cpp
	$(CC) -c -o $@ $^ $(CFLAGS) 

# Build libs
# c and cpp files
$(ODIR)/%.o : $(LDIR)/%.cpp
	$(CC) -c -o $@ $^ $(CFLAGS) 

$(ODIR)/%.o : $(LDIR)/%.c
	$(CC_C) -c -o $@ $^ $(CFLAGS)

# Build lib used for testing
$(TDIR)/catch_amalgamated.o : $(TDIR)/catch_amalgamated.cpp
	$(CC) -c -o $@ $^ $(CFLAGS) 

# Build object files for tests
$(TDIR)/%.o : $(TDIR)/%.cpp
	$(CC) -c -o $@ $(CFLAGS_TEST) $^ $(CFLAGS_TEST) 

# Link test objects to make test program
$(TDIR)/$(TEST_PROG) : $(TEST_OBJ) $(TDIR)/catch_amalgamated.o $(patsubst $(ODIR)/main.o, ,$(OBJ)) 
	$(CC) -o $@ $^ $(CFLAGS_TEST) 

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o $(ODIR)/*.out $(TDIR)/*.o $(TDIR)/*.out

.PHONY: run
run:
	./$(ODIR)/$(PROG)

.PHONY: test
test : $(TDIR)/$(TEST_PROG) 
	./$(TDIR)/$(TEST_PROG)


