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
	static void print_entry(Entry* );
	
};

class Phone_Book
{
public:
	Phone_Book();
	Phone_Book(string);
	int append_file(string);

	void add_file(string ifile);
	void add_line(Entry *);
	int find(string,string);
	int get_hash(string);
	void remove(string);
	void dump(string);
	void find_city(string);
	Entry * entry_getter(string);
	void print();
	vector<Entry *> sort_byCity(vector<Entry*> );
	std::vector<Entry* > merge(std::vector<Entry* > , std::vector<Entry* > );
	
	~Phone_Book();
	std::vector<std::vector<Entry*> > hash_table;
	vector <Entry *> all_entries;
	int count;
	int size;
	vector<string> loaded_files;

	
};
#endif

//problem now: multiple entries