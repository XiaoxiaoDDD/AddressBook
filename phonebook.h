#ifndef PHONEBOOK_H
#define  PHONEBOOK_H


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


//const int p = 10007; //this is the prime number chosen

const int p = 23; //this is the prime number chosen



class Entry
{
public:
	Entry(string,string,string,string,string,string,string);
	~Entry();
	int get_hash(string);
	string first, second, room, street, city, country, number;
	string key;
	int hash_value;
	
};

class Phone_Book
{
public:
	Phone_Book();
	Phone_Book(string);
	void append_file(string);

	void add_file(string ifile);
	void add_line(Entry *);
	void find(string);
	void remove(string);
	void dump(string);
	void find_city(string);
	Entry * entry_getter(string);
	void print();
	
	~Phone_Book();
	std::vector<std::vector<Entry*> > hash_table;
	int count;

	
};
#endif

//problem now: multiple entries