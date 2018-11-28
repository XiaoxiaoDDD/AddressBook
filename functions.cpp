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

}

void Phone_Book::print(){
	for (int i = 0; i < p; i++){
		cout << i <<" : ";
		for (int j = 0; j < hash_table[i].size(); j++){
			cout << hash_table[i][j]->first<<" ";
		}
		cout << endl;
	}
}

void Phone_Book::add_line(Entry * entry){
	hash_table[entry->hash_value].push_back(entry);
}


int Phone_Book::find(string first, string second){
	string key;
	key = first + " "+ second;
	int hash;
	hash = Phone_Book::get_hash(key);
	for (int i = 0; i < hash_table[hash].size(); i++){
		if(hash_table[hash][i]->first ==first && hash_table[hash][i]->second ==second){
			cout << "found: ";
			Entry::print_entry(hash_table[hash][i]);
			return 0;
		}
	}
	cout <<"not found"<<endl;
	return 1;


}



int Phone_Book::get_hash(string key){
	int sum = 0;
	for (int i = 0; i < key.length(); i++){
		sum += key[i];
	}
	return sum% p;
}

Entry * Phone_Book::entry_getter(string line){
	string lis[8];

	int index = 0;
	string tmp;
	tmp = "";
	for (int i = 0; i < line.length(); i++){
		if (line[i] != ' '){
			tmp += line[i];
		}
		else{
			lis[index] = tmp;
			//cout <<"-"<<tmp;
			tmp = "";
			index++;
		}
	}
	Entry * ent;
	ent = new Entry(lis[0],lis[1], lis[2],lis[3],lis[4],lis[5],lis[6]);
	return ent;
}