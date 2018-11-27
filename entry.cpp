#include "phonebook.h"

Entry::Entry(string first,string second,string room,string street,string city,string country,string number)
	:first(first), second(second),room(room),street(street),city(city),country(country),number(number){
		key = first + " "+ second;
		hash_value = get_hash(key);
		
	}