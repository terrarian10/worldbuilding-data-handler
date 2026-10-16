CXX = g++
CXXFLAGS = -std=c++20 -Iinclude

history-game: src/main.cpp
	$(CXX) $(CXXFLAGS) src/main.cpp -o history-game