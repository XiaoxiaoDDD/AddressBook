#include "phonebook.h"
#include <math.h>

Phone_Book::Phone_Book(){

	hash_table.resize(p);
}

Phone_Book::Phone_Book(string ifile){

	hash_table.resize(p);
	add_file(ifile);
}


int Phone_Book::append_file(string file){
	for (int i=0; i < loaded_files.size(); i++){
		if (file == loaded_files[i]){
			cout << "this file is already loaded"<<endl;
			return 1;
		}
	}
	add_file(file);
	return 0;
}

void Phone_Book::hash_and_sort(std::vector<Entry*> & entries){
	count = entries.size();
	for (int i =0; i < entries.size(); i++){

		Entry * entry = entries[i];
		hash_table[entry->hash_value].push_back(entry) ;			


	}
	std::cout <<"all entries added to the hash table" <<endl;
	entries = sort_byCity(entries);
	cout <<"sorted"<<all_entries.size()<< endl;

	//for debug purpose
	for (int i = 0; i < all_entries.size(); i++){
		Entry::print_entry(all_entries[i]);
	}

}


void Phone_Book::add_file(string ifile){
	string line;
	ifstream data(ifile);
	if (data.is_open()){
		while (getline(data,line)){
			Entry * entry;
			entry = entry_getter(line);		
			all_entries.push_back(entry);
		}
		hash_and_sort(all_entries);		//to remake the hash table and the sort
	}
	else{
		cout <<"the file cannot be opened" <<endl;
	}
}

std::vector<Entry *> Phone_Book::sort_byCity(vector<Entry*>& all){
	int n = all.size();
	if ( n ==1){
		return all;
	}
	else{
		int half = floor(n/2);
		vector<Entry*> v1;
		vector<Entry*> v2;
		for (int i = 0; i < all.size(); i++){
			if (i < half){
				v1.push_back(all[i]);
			}
			else{
				v2.push_back(all[i]);
			}
		}
		v1 = sort_byCity(v1);
		v2 = sort_byCity(v2);
		return merge(v1,v2);
	}

}

std::vector<Entry* > Phone_Book::merge(std::vector<Entry* > a, std::vector<Entry* > b){
	int aa;
	int bb;
	aa = 0;
	bb = 0;//a and b are the indexes
	std::vector<Entry *> new_vec;
	while (aa < a.size() && bb < b.size() ){
		if (strcmp(a[aa]->city.c_str(), b[bb]->city.c_str()) <0){
			new_vec.push_back(a[aa++]);
		}
		else{
			new_vec.push_back(b[bb++]);
		}
	}
	while (aa < a.size()){
		new_vec.push_back(a[aa++]);
	}
	while (bb < b.size()){
		new_vec.push_back(b[bb++]);
	}

	return new_vec;

}



//this is for debug i guess, can't remember
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

void Phone_Book::remove(string first, string second){
	Entry* e;
	e= find(first,second);
	if (e == NULL){
		cerr <<"this entry is not found"<<endl;
	}
	else{	


	}

}


Entry * Phone_Book::find(string first, string second){
	string key;
	key = first + " "+ second;
	int hash;
	hash = Phone_Book::get_hash(key);
	for (int i = 0; i < hash_table[hash].size(); i++){
		if(hash_table[hash][i]->first ==first && hash_table[hash][i]->second ==second){
			cout << "found: ";
			return hash_table[hash][i];
		}
	}
	return NULL;

}

std::vector<Entry*> Phone_Book::find_city(string target_city){
	std::vector<Entry*> residents;
	int e;
	e = binary_search(target_city);
	//cout <<"one occurence is at the position"<<e<<endl;
	if (e != -1){

		residents.push_back(all_entries[e]);
		//cout <<"yes "<<endl;
		int pre = e - 1;
		int post = e + 1;
		while (pre >=0 && all_entries[pre]->city == target_city ){
			residents.push_back(all_entries[pre]);
			pre--;
		}
		//cout <<"yes" <<endl;
		while (post < all_entries.size() && all_entries[post]->city == target_city ){
			residents.push_back(all_entries[post]);
			post++;
		}
		//cout <<"yes" <<endl;

		return residents;
	
	}
}


//find the first occurance of the city
int Phone_Book::binary_search(string the_city){
	int left = 0;
	int right = all_entries.size() - 1;
	int middle;

	while (left <= right) {
		middle = (left + right)/ 2;

		if (strcmp(the_city.c_str(),all_entries[middle]->city.c_str())>0) {
			left = middle + 1;
		}
		else if (strcmp(the_city.c_str(),all_entries[middle]->city.c_str()) < 0) {
			right = middle;
		}
		if (strcmp(the_city.c_str(),all_entries[middle]->city.c_str()) == 0){
			return middle;
		}
	}
	return -1;

}




int Phone_Book::get_hash(string key){
	int sum = 0;
	for (int i = 0; i < key.length(); i++){
		sum += key[i];
	}
	return sum% p;
}

Entry * Phone_Book::entry_getter(string line){
	line = line +" "; //to ensure that number got read
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