CC = g++
PROG= app.out

ODIR :=bin
SDIR :=src
LDIR :=lib

SOURCES := $(wildcard $(SDIR)/*.cpp)
OBJ := $(patsubst $(SDIR)/%,%,$(SOURCES))
OBJ := $(patsubst %.cpp,%.o,$(OBJ))
OBJ := $(addprefix $(ODIR)/,$(OBJ))

LIBS:=
CFLAGS:=-I $(LDIR)/ 

$(ODIR)/$(PROG): $(OBJ)
	$(CC) -o $@ $(CFLAGS) $^ 


$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c -o $@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean
clean:
	rm bin/*.o

.PHONY: run
run:
	./$(ODIR)/$(PROG)
