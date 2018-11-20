# All Targets
all: rest

# Tool invocations
# Executable "rest" depends on the files rest.o and Main.o.
rest: bin/Dish.o bin/Table.o bin/Customer.o bin/Restaurant.o bin/Action.o bin/Main.o
	@echo 'Building target: rest'
	@echo 'Invoking: C++ Linker'
	g++ -o bin/rest bin/Dish.o bin/Restaurant.o bin/Table.o bin/Customer.o bin/Action.o bin/Main.o
	@echo 'Finished building target: rest'
	@echo ' '

# Depends on the source and header files
bin/Restaurant.o: src/Restaurant.cpp
	g++ -g -Wall -std=c++11 -c -Iinclude -o bin/Restaurant.o src/Restaurant.cpp
bin/Dish.o: src/Dish.cpp
	g++ -g -Wall -std=c++11 -c -Iinclude -o bin/Dish.o src/Dish.cpp
bin/Action.o: src/Action.cpp
	g++ -g -Wall -std=c++11 -c -Iinclude -o bin/Action.o src/Action.cpp

bin/Table.o: src/Table.cpp
	g++ -g -Wall -std=c++11 -c -Iinclude -o bin/Table.o src/Table.cpp

bin/Customer.o: src/Customer.cpp
	g++ -g -Wall -std=c++11 -c -Iinclude -o bin/Customer.o src/Customer.cpp

# Depends on the source and header files 
bin/Main.o: src/Main.cpp
	g++ -g -Wall -std=c++11 -c -Iinclude -o bin/Main.o src/Main.cpp

#Clean the build directory
clean: 
	rm -f bin/*
