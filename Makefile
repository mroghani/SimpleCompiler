compiler: parser.cc scanner.cc driver.o  helpers.o compiler.cpp
	g++ compiler.cpp driver.o helpers.o parser.cc scanner.cc -o compiler

compiler.o: compiler.cpp
	g++ -c compiler.cpp

scanner.cc: parser.cc scanner.l
	flex -o scanner.cc scanner.l

parser.cc: parser.yy types.hh types/*.hh
	bison parser.yy -o parser.cc

driver.o: driver.cc driver.hh
	g++ -c driver.cc

helpers.o: helpers/helpers.hh helpers/helpers.cc
	g++ -c helpers/helpers.cc

clean:
	rm *.o compiler parser.cc parser.hh location.hh scanner.cc