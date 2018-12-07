#include "phonebook.h"
#include <math.h>

Phone_Book::Phone_Book(){
	p = 23; //initialize the size of hash table as 23;

	hash_table.resize(p);
	cout <<"initiated"<<endl;
}

Phone_Book::Phone_Book(string ifile){
	p = 23;
	hash_table.resize(p);
	add_file(ifile);
	cout <<"initiated"<<endl;
}


void Phone_Book::evaluate_p(int & size){
	double pi;
	pi = double(all_entries.size())/size;
	while (pi > 1.5){
		size= size*2;
		pi = double(all_entries.size())/size;
	}
	hash_table.resize(size);
	cout <<"now the prime number is "<<size<<endl;
	cout <<"the hash_table capacity index is "<<pi<<endl;
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
	entries = sort_byCity(entries);
	cout <<"sorted"<<all_entries.size()<< endl;

	for (int i=0; i <p; i++){
		hash_table[i].clear();
	}


	for (int i =0; i < entries.size(); i++){
		entries[i]->loc = i;
		Entry * entry = entries[i];
		entry->hash_value = entry->get_hash(entry->key, p);
		//cout <<"we get new hash value"<<endl;

		hash_table[entry->hash_value].push_back(entry) ;			
	}
	
	

	//for debug purpose
	// for (int i = 0; i < all_entries.size(); i++){
	// 	Entry::print_entry(all_entries[i]);
	// }
	std::cout <<"all entries added to the hash table" <<endl;

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
		evaluate_p(p);
		hash_and_sort(all_entries);		//to remake the hash table and the sort
		loaded_files.push_back(ifile);
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
		return merge_by_city(v1,v2);
	}


}

std::vector<Entry* > Phone_Book::merge_by_city(std::vector<Entry* > a, std::vector<Entry* > b){
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


//this is for debug 
void Phone_Book::print(){
	for (int i = 0; i < p; i++){
		cout << i <<" : ";
		for (int j = 0; j < hash_table[i].size(); j++){
			cout << hash_table[i][j]->first<<" ";
		}
		cout << endl;
	}
}

// void Phone_Book::add_line(Entry * entry){
// 	hash_table[entry->hash_value].push_back(entry);
// }
void Phone_Book::add_line(Entry * entry){
	all_entries.push_back(entry);
	hash_and_sort(all_entries);
}

// void Phone_Book::remove(string first, string second){
// 	vector <Entry*> results;
// 	results= find(first,second);
// 	if (results.size() ==0 ){
// 		cerr <<"this entry is not found"<<endl;
// 	}
// 	else{
// 		cout << "There are "<< results.size()<<" of them"<<endl;
// 		//first delete it from the sorted city list
// 		for (int i=0; i<results.size(); i++){
// 			all_entries.erase(all_entries.begin()+results[i]->loc); //delete it from the all_entries		
// 		}
// 		cout <<"deleted from all_entries"<<endl;


// 		int seq = results[0]->hash_value;//they all have the same key and thus hash_value
// 		for (int i = 0; i < hash_table[seq].size(); i++){
// 			if (hash_table[seq][i]->first == results[i]->first && hash_table[seq][i]->second == results[i]->second  ){
// 				hash_table[seq].erase(hash_table[seq].begin()+i);
// 				if (i != hash_table[seq].size()-1) i--;		
// 				cout <<"An entry is deleted"<<endl;
// 			}
// 		}
			
// 		cout <<"all relevant entries are deleted"<<endl;
// 	}

// }
void Phone_Book::remove(string first, string second){
	vector <Entry*> results;
	results= find(first,second);

	if (results.size() ==0 ){
		cerr <<"this entry is not found"<<endl;
	}

	else{
		int seq = results[0]->hash_value;//they all have the same key and thus hash_value
		for (int i = 0; i < hash_table[seq].size(); i++){
			if (hash_table[seq][i]->first == results[0]->first && hash_table[seq][i]->second == results[0]->second  ){
				hash_table[seq].erase(hash_table[seq].begin()+i);
				i--;		
				cout <<"An entry is deleted"<<endl;
			}
		}
		all_entries.clear();
		for (int i=0; i < p; i++){
			for (int j = 0; j < hash_table[i].size(); j++){
				all_entries.push_back(hash_table[i][j]);
			}
		}
		hash_and_sort(all_entries);

			
		cout <<"all relevant entries are deleted"<<endl;
	}

}


vector <Entry*> Phone_Book::find(string first, string second){
	string key;
	key = first + " "+ second;
	int hash;
	int count = 1;
	hash = Phone_Book::get_hash(key);
	vector <Entry*> results;
	for (int i = 0; i < hash_table[hash].size(); i++){
		count++;
		if(hash_table[hash][i]->first ==first && hash_table[hash][i]->second ==second){
			//cout <<"the number of comparison is "<<count<<endl;
			results.push_back(hash_table[hash][i]);
		}
	}
	cout <<"the number of comparison is "<<count<<endl;
	return results;

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

			
	}
	//cout <<"we are about to return"<<endl;
	return residents;
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
		else if (strcmp(the_city.c_str(),all_entries[middle]->city.c_str()) == 0){
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