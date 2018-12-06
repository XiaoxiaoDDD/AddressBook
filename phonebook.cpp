#include "phonebook.h"


int main(int argc, char* argv[]){

	string ifile_name = "default";
	bool initialized;
	initialized = 0;

	if (argc ==1){  //if the file is not given
		;
	}
	else if (argc ==3 && strcmp(argv[1],"-f")==0){  //if the file is already given
		ifile_name = argv[2];

	}
	else{  //if the promp is mistaken
		cerr <<"mymachine-prompt >> ./phonebook -f <filename>"<<endl;
		return 1;
	}


	string user_input;

	while (true){
		cin >> user_input;
		Phone_Book * pbook;
		if (initialized ==0){ //if not initialized yet
			if (user_input =="init"){
				if (ifile_name =="default"){
					pbook = new Phone_Book();
					initialized = 1;
				}
				else{
					pbook = new Phone_Book(ifile_name);
					pbook->loaded_files.push_back(ifile_name);
					initialized = 1;
				}

			}
			else{
				cout <<"please initialize first"<<endl;
			}
		}
		else{

			if (user_input =="init"){
				cout <<"already initialized"<<endl;
			}

			else if (user_input =="load"){
				string file_name;
				cin >>file_name;
				pbook->append_file(file_name);
				initialized = 1;
			}

			//version A--not working
			// else if (user_input.substr(0,3) =="add"){
			// 	Entry * entry;
			// 	entry = pbook->entry_getter(user_input);
			// 	pbook->add_line(entry);
			// 	cout <<"added~"<<endl;
			// }

			//version B--it works

			else if (user_input =="add"){
				string first,second, room, street, city, country, number;
				cin >> first >>second >>room >>street >>city >>country >>number;
				Entry * entry = new Entry(first, second ,room, street, city, country, number);
				pbook->add_line(entry);
				pbook->print();
			}

			else if (user_input =="find"){
				string first, second;
				cin >>first >>second;
				Entry * e;
				e =pbook->find(first,second);
				if (e ==NULL){
					cout <<"not found"<<endl;
				}
				else{
					cout <<"found:"<<endl;
					Entry::print_entry(e);
				}
			
			}
			else if (user_input =="delete"){
				string first, second;
				cin >>first>> second;
				pbook->remove(first, second);
			
			}
			else if (user_input =="dump"){
				string ofile;
				cin >>ofile;
				pbook->dump(ofile);
			
			}
			else if (user_input =="allinCity"){
				string city;
				cin >>city;
				vector <Entry *>residents;
				residents=pbook->find_city(city);
				pbook->save_to_file(residents, city);
				if (residents.size()==0){
					cout <<"the city is not found in the phonebook"<<endl;
				}
				else{
					cout <<"There are "<<residents.size()<<" residents in this city"<<endl;
					for (int i = 0; i < residents.size(); i++){
						Entry::print_entry(residents[i]);
					}
				}
			}
			else if (user_input =="quit"){
				return 0;
			}
			else{
				cout <<"illegitimate command" <<endl;
			}
		}
	}

	return 0;

}