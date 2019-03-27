COMP = g++
COMPFLAG = -O3 -std=c++17 -c -g
LINKFLAGS = -lglfw -lvulkan -o
NOME = PoliFill
CFILES = dm.cpp main.cpp
OFILES = $(CFILES:.cpp=.o)

all: $(NOME)

$(NOME): $(OFILES)
	$(COMP) $(OFILES) $(LINKFLAGS) $(NOME)

%.o:%.cpp
	$(COMP) $(COMPFLAG) $(FOLDER)$< -o $@

run: $(NOME)
	./$(NOME)

clean:
	rm $(OFILES) $(NOME)
