#Makefile for lab01, William Lu, CS32

CXX=clang++
# CXX=g++

helloworld: helloworld.o
	$(CXX) -o helloworld helloworld.o

helloworld.o: helloworld.cpp
	$(CXX) -c helloworld.cpp

lab01Test: lab01Test.o tddFuncs.o arrayFuncs.o
	$(CXX) -o lab01Test lab01Test.o tddFuncs.o arrayFuncs.o
clean:
	/bin/rm -f helloworld helloworld.o lab01Test lab01Test.o tddFuncs.o arrayFuncs.o
