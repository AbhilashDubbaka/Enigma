OBJ = main.o enigma.o plugboard.o reflector.o rotor.o helper.o
CXX = g++
CXXFLAGS = -Wall -g -MMD
EXE = enigma

$(EXE):$(OBJ)
	$(CXX) $^ -o $@

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $<

-include $(OBJ:.o=.d)

.PHONY: clean

clean:
	rm -f $(OBJ) $(EXE) $(OBJ:.o=.d)
