
phonebook: phonebook.o functions.o entry.o
	g++ phonebook.o functions.o entry.o -o phonebook


phonebook.o: phonebook.cpp
	g++ -std=c++11 -c phonebook.cpp

	
functions.o: functions.cpp
	g++ -std=c++11 -c functions.cpp

entry.o: entry.cpp
	g++ -std=c++11 -c entry.cpp

clean:
	rm *.o phonebook *.txt