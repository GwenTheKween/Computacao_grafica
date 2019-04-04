COMP = g++
COMPFLAG = -O3 -std=c++17 -c -g
LINKFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
NOME = PoliFill
CFILES = dm.cpp main.cpp botoes.cpp
OFILES = $(CFILES:.cpp=.o) glad.o

all: $(NOME)

$(NOME): $(OFILES)
	$(COMP) $(OFILES) $(LINKFLAGS) -o $(NOME)

%.o:%.cpp %.h
	$(COMP) $(COMPFLAG) $(FOLDER)$< -o $@

%.o:%.cpp
	$(COMP) $(COMPFLAG) $(FOLDER)$< -o $@

%.o:%.c
	gcc -O3 -c -g $(FOLDER)$< -o $@

run: $(NOME)
	./$(NOME)

clean:
	rm $(OFILES) $(NOME)
