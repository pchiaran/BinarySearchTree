EXE = bst

#LFLAGS = -lblass
CXX = c++
CXXFLAGS = -I include -g -std=c++14 -Wall -Wextra

SRC = main.cpp src/bst.cpp

OBJ = ${SRC:.cpp=.o}

LIB = include/bst.hpp include/node.hpp include/iterator.hpp
all: $(EXE)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(EXE): $(OBJ)
	$(CXX) $^ -o $(EXE) $(LFLAGS)

main.o: $(LIB) 

src/bst.o: $(LIB)

clean:
	rm -rf src/*.o main.o $(EXE)

.PHONY: clean all
