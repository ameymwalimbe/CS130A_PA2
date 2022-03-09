CXX=clang++

PA2: main.o GraphGenerator.o GraphOperator.o Person.o
	${CXX} $^ -o $@

main.o: main.cpp
	g++ -c main.cpp

GraphGenerator.o: GraphGenerator.cpp GraphGenerator.hpp
	g++ -c GraphGenerator.cpp

GraphOperator.o: GraphOperator.cpp GraphOperator.hpp
	g++ -c GraphOperator.cpp

Person.o: Person.cpp Person.hpp
	g++ -c Person.cpp

clean:
	rm *.o PA2