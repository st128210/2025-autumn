CXX = g++
TARGET = text_editor

CXXFLAGS ?= -std=c++17 -Wall -Wextra
LDFLAGS ?= 

ifeq ($(origin CXXFLAGS), environment)
    ACTUAL_CXXFLAGS = $(CXXFLAGS)
else
    ACTUAL_CXXFLAGS = -std=c++17 -Wall -Wextra
endif

ifeq ($(origin LDFLAGS), environment)
    ACTUAL_LDFLAGS = $(LDFLAGS)
else
    ACTUAL_LDFLAGS = 
endif

SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(ACTUAL_CXXFLAGS) -o $@ $^ $(ACTUAL_LDFLAGS)

%.o: %.cpp
	$(CXX) $(ACTUAL_CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS)

rebuild: clean all

debug:
	@echo "CXX: $(CXX)"
	@echo "CXXFLAGS from env: $(CXXFLAGS)"
	@echo "Actual CXXFLAGS: $(ACTUAL_CXXFLAGS)"
	@echo "LDFLAGS from env: $(LDFLAGS)"
	@echo "Actual LDFLAGS: $(ACTUAL_LDFLAGS)"
	@echo "Sources: $(SOURCES)"

.PHONY: all clean rebuild run debug