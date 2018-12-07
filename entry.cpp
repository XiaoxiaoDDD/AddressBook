#include "phonebook.h"
#include <math.h>

Entry::Entry(string first,string second,string room,string street,string city,string country,string number)
	:first(first), second(second),room(room),street(street),city(city),country(country),number(number){
		key = first + " "+ second;
		
		loc = -1;
		
	}

void Entry::print_entry(Entry* entry){
	cout <<entry->first <<" "<< entry->second <<" "<<entry->room <<" "<<entry->street<<" " <<entry->city<<" " <<entry->country;
	cout<<" "<<entry->number <<endl;
}

int Entry::get_hash(string key, int prime){
	int sum;
	sum = 0;
	key = this->first+" "+ this->second;
	for (int i = 0; i < key.length(); i++){
		sum += key[i];
	}
	return sum% prime;
}

void Phone_Book::save_to_file(vector<Entry*> residents,string city){
	ofstream outfile;
	outfile.open(city);
	for (int i = 0; i < residents.size(); i++){
		outfile <<residents[i]->first <<" "<< residents[i]->second <<" "<<residents[i]->room <<" "<<residents[i]->street<<" " <<residents[i]->city<<" " <<residents[i]->country<<" "<<residents[i]->number <<endl;	
	}
	cout <<"all the entries are saved in the file called "<<city<<endl;
	outfile.close();

	
}

//the following parts are phonebook functions
void Phone_Book::dump(string ofile){
	ofstream outfile;
	outfile.open(ofile);

	vector<Entry *> key_sorted;
	for (int i=0; i < all_entries.size(); i++){
		key_sorted.push_back(all_entries[i]);
	}
	key_sorted = sort_by_key(key_sorted);

	for (int i = 0; i < key_sorted.size(); i++){
		outfile <<key_sorted[i]->first <<" "<< key_sorted[i]->second <<" "<<key_sorted[i]->room <<" "<<key_sorted[i]->street<<" " <<key_sorted[i]->city<<" " <<key_sorted[i]->country<<" "<<key_sorted[i]->number <<endl;	
	}
	outfile.close();
	cout <<"All entries are dumpt in the designated file"<<endl;

}

vector<Entry*> Phone_Book::sort_by_key(vector<Entry*>& all){

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
		v1 = sort_by_key(v1);
		v2 = sort_by_key(v2);
		return merge_by_key(v1,v2);
	}

}

std::vector<Entry* > Phone_Book::merge_by_key(std::vector<Entry* > a, std::vector<Entry* > b){
	int aa;
	int bb;
	aa = 0;
	bb = 0;//a and b are the indexes
	std::vector<Entry *> new_vec;
	while (aa < a.size() && bb < b.size() ){
		if (strcmp(a[aa]->second.c_str(), b[bb]->second.c_str()) <0){
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




	