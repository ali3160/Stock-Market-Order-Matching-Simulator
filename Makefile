
CXX = g++

CXXFLAGS = -O0 -g3 -std=c++17

main: main.cpp Order.o Market.o
	$(CXX) $(CXXFLAGS) main.cpp Order.o Market.o -o main

Order.o: Order.cpp Order.h
	$(CXX) $(CXXFLAGS) -c Order.cpp -o Order.o

Market.o: Market.cpp Market.h
	$(CXX) $(CXXFLAGS) -c Market.cpp -o Market.o

deepclean:
	rm -f *~ *.o main main.exe *.stackdump