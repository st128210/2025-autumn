CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./vcpkg/installed/x64-windows/include
TARGET = programm
TARGET_TEST = programm_test
SOURCE = main.cpp

VCPKG_INCLUDE = ./vcpkg/installed/x64-windows/include
VCPKG_LIB = ./vcpkg/installed/x64-windows/lib

LINK_FLAGS = -L$(VCPKG_LIB) -lgtest -lgtest_main -lpthread

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

test-build: $(SOURCE)
	$(CXX) $(CXXFLAGS) -I$(VCPKG_INCLUDE) -o $(TARGET_TEST) $(SOURCE) $(LINK_FLAGS)

test: test-build
	./$(TARGET_TEST)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TARGET_TEST)

rebuild: clean all

.PHONY: all clean rebuild run test test-build