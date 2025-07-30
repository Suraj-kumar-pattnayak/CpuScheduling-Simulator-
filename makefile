CXX = g++
TARGET = main.exe
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)