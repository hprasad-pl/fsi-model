
CXX = g++
CXXFLAGS = `root-config --cflags` -Wall -O2
LDFLAGS = `root-config --libs`

SRC_DIR = $(PWD)
LIB_DIR = $(PWD)/lib
OBJ_DIR = $(PWD)/obj


SRC = $(SRC_DIR)/simulate_events.cpp $(SRC_DIR)/event.cpp
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
HEADERS = $(LIB_DIR)/event.h
DICT_CPP = $(OBJ_DIR)/eventDict.cpp
DICT_OBJ = $(OBJ_DIR)/eventDict.o

TARGET = simulate_events

all: $(TARGET)

$(TARGET): $(OBJ) $(DICT_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(DICT_OBJ) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DICT_OBJ): $(LIB_DIR)/event.h $(LIB_DIR)/LinkDef.h
	mkdir -p $(OBJ_DIR)
	rootcling -f $(DICT_CPP) -c $(LIB_DIR)/event.h $(LIB_DIR)/LinkDef.h
	$(CXX) $(CXXFLAGS) -c $(DICT_CPP) -o $(DICT_OBJ)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
