CXX = g++
CXXFLAGS = -std=c++20 -Iinclude

history-game: src/game.cpp
	$(CXX) $(CXXFLAGS) src/game.cpp -o history-game