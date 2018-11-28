#include "phonebook.h"

Entry::Entry(string first,string second,string room,string street,string city,string country,string number)
	:first(first), second(second),room(room),street(street),city(city),country(country),number(number){
		key = first + " "+ second;
		hash_value = get_hash(key);
		
	}

void Entry::print_entry(Entry* entry){
	cout <<entry->first <<" "<< entry->second <<" "<<entry->room <<" "<<entry->street<<" " <<entry->city<<" " <<entry->country <<" "<<entry->number <<endl;
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