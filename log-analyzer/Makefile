CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = log_analyzer

SRCS = main.cpp LogAnalyzer.cpp
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
