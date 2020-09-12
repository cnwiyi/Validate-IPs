validateIP: main.cpp
	g++ main.cpp -o validateIP -g -std=c++17 -Wall -lpthread

clean:
	rm -rf validateIP*
