#include "phonebook.h"

Phone_Book::Phone_Book(){

	hash_table.resize(p);
}

Phone_Book::Phone_Book(string ifile){

	hash_table.resize(p);
	add_file(ifile);
}


void Phone_Book::append_file(string file){
	add_file(file);
}


void Phone_Book::add_file(string ifile){
	string line;
	ifstream data(ifile);
	if (data.is_open()){
		while (getline(data,line)){
			Entry * entry;
			entry = entry_getter(line);
			hash_table[entry->hash_value].push_back(entry) ;
			count++;
		}
	}
	else{
		cout <<"the file cannot be opened" <<endl;
	}
	std::cout <<"all entries added to the hash table" <<endl;
	for (int i = 0; i < p; i++){
		cout << i <<" : ";
		for (int j = 0; j < hash_table[i].size(); j++){
			cout << hash_table[i][j]->first<<" ";
		}
		cout << endl;
	}
}

int Entry::get_hash(string key){
	int sum;
	sum = 0;
	key = this->first+" "+ this->second;
	for (int i = 0; i < key.length(); i++){
		sum += key[i];
	}
	return sum% p;
}

Entry * Phone_Book::entry_getter(string line){
	string lis[7];

	int index = 0;
	string tmp;
	for (int i = 0; i < line.length(); i++){
		if (line[i] != ' '){
			tmp += line[i];
		}
		else{
			lis[index] = tmp;
			tmp = "";
			index++;
		}
	}
	Entry * ent;
	ent = new Entry(lis[0],lis[1], lis[2],lis[3],lis[4],lis[5],lis[6]);
	return ent;
}