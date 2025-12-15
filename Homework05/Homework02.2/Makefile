CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = programm
TARGET_TEST = programm_test
SOURCE = main.cpp

GTEST_LIBS = -lgtest -lgtest_main
PTHREAD_LIB = -pthread

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

test-build: $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET_TEST) $(SOURCE) $(GTEST_LIBS) $(PTHREAD_LIB)

test: test-build
	./$(TARGET_TEST) --run-tests

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TARGET_TEST)

rebuild: clean all

.PHONY: all clean rebuild run test test-build