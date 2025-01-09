#include <iostream>
#include <fstream>
#include <string>
#include <vector>


struct userAction {
	void (*action)();
	int action_acces;
	std::string action_name;
};

struct AmmoType {
	std::string Ammo_name;
	std::vector<std::string>AmmoTypesIncluded{};
	std::vector<int> AmmoTypesAmount{};
	std::vector<float> AmmoTypesCost{};
	AmmoType(const std::string& name,
		const std::vector<std::string>& included,
		const std::vector<int>& amount,
		const std::vector<float>& cost)
		: Ammo_name(name), AmmoTypesIncluded(included), AmmoTypesAmount(amount), AmmoTypesCost(cost) {}
};


std::string currentUserName, currentUserPassword;
int currentUserAdmission;
bool logged = false;

std::vector<std::string> usernames_list, passwords_list;
std::vector<int> admissions_list;

std::vector<AmmoType>Ammunition_Static{}, Ammunition{};




void write_static_storage(){
	std::ifstream file;
	file.open("AmmoProductsStatic.txt");
	bool ammoCaliberEntered = false; //explains when the ammo caliber is entered and where is the end of the line;
	int heading = 0; //from 0 to 2, explains where information to store, like 0 for ammo type, 1 for amount and 2 for cost per round
	std::string line, word;

	std::string overall_name;
	std::vector<std::string> ammo_types;
	std::vector<int> ammo_amount;
	std::vector<float> ammo_cost;

	while (std::getline(file, line)) {
		
		for (int i = 0; i < line.length(); i++) {
			if (line[i] != '|' && line[i] != '_' && line[i] != '$') {
				word = word + line[i];
			}
			if (line[i] == '|' && ammoCaliberEntered == false) {
				overall_name = word;
				ammoCaliberEntered = true;
				//std::cout << "Ammo name: (" <<word<< ")   ";
				word = "";
				
			}
			if (line[i] == '_') {
				//std::cout << "   " <<word <<" " << heading << "   ";
				if (heading == 0) { ammo_types.push_back(word); }
				if (heading == 1) { ammo_amount.push_back(stoi(word)); }
				if (heading == 2) { ammo_cost.push_back(stof(word)); heading = -1; }
				word = "";
				heading++;
			}
			if (line[i] == '$') {
				//std::cout << "  Endline \n";
				ammoCaliberEntered = false;
				word = "";
				heading = 0;
				Ammunition_Static.push_back(AmmoType(overall_name, ammo_types, ammo_amount, ammo_cost));
				ammo_types.clear();
				ammo_amount.clear();
				ammo_cost.clear();
			}
		}
	}
}

void write_active_storage() {
	std::ifstream file;
	file.open("AmmoProducts.txt");
	bool ammoCaliberEntered = false; //explains when the ammo caliber is entered and where is the end of the line;
	int heading = 0; //from 0 to 2, explains where information to store, like 0 for ammo type, 1 for amount and 2 for cost per round
	std::string line, word;

	std::string overall_name;
	std::vector<std::string> ammo_types;
	std::vector<int> ammo_amount;
	std::vector<float> ammo_cost;

	while (std::getline(file, line)) {

		for (int i = 0; i < line.length(); i++) {
			if (line[i] != '|' && line[i] != '_' && line[i] != '$') {
				word = word + line[i];
			}
			if (line[i] == '|' && ammoCaliberEntered == false) {
				overall_name = word;
				ammoCaliberEntered = true;
				//std::cout << "Ammo name: (" <<word<< ")   ";
				word = "";

			}
			if (line[i] == '_') {
				//std::cout << "   " <<word <<" " << heading << "   ";
				if (heading == 0) { ammo_types.push_back(word); }
				if (heading == 1) { ammo_amount.push_back(stoi(word)); }
				if (heading == 2) { ammo_cost.push_back(stof(word)); heading = -1; }
				word = "";
				heading++;
			}
			if (line[i] == '$') {
				//std::cout << "  Endline \n";
				ammoCaliberEntered = false;
				word = "";
				heading = 0;
				Ammunition.push_back(AmmoType(overall_name, ammo_types, ammo_amount, ammo_cost));
				ammo_types.clear();
				ammo_amount.clear();
				ammo_cost.clear();
			}
		}
	}
}


void read_storage(std::vector<AmmoType> storage){
	for (int i = 0; i < storage.size(); i++) {
		 
		std::cout << "\n+---------->\n| Ammo Caliber: " << storage[i].Ammo_name << "\n+---------->";
		std::cout << "\n| Ammo types:";
		for (int k = 0; k < storage[i].AmmoTypesIncluded.size(); k++) {
			std::cout << "\t|"<< storage[i].AmmoTypesIncluded[k];
		}
		std::cout << "\n| Ammo amount:";
		for (int k = 0; k < storage[i].AmmoTypesAmount.size(); k++) {
			std::cout << "\t|" << storage[i].AmmoTypesAmount[k];
		}
		std::cout << "\n| Ammo cost:";
		for (int k = 0; k < storage[i].AmmoTypesCost.size(); k++) {
			std::cout << "\t|" << storage[i].AmmoTypesCost[k];
		}
		std::cout << "\n\\__________/\n";
	}
	std::cout << std::endl;
}

///  ---debug---
/*void lists_out() {
	for (int i = 0; i < usernames_list.size(); i++) {
		std::cout << usernames_list[i] <<", ";
	}
	for (int i = 0; i < passwords_list.size(); i++) {
		std::cout << passwords_list[i] << ", ";
	}
}
*/
///  - --end-- -

void createLists(){
	std::string line,word;
	std::ifstream file;
	int counter = 0;
	file.open("OtherUsers.txt");
	while (std::getline(file, line)) { 
		for (int i = 0; i < line.length(); i++) {
			if (line[i] != '|') {
				word = word + line[i];
			}
			else {

				counter++;
				if (counter == 1) {
					usernames_list.push_back(word);
				}
				else if (counter == 2) {
					passwords_list.push_back(word);
				}
				else if (counter == 3) {
					admissions_list.push_back(stoi(word));

				}
				word = "";
			}
			
		}
		counter = 0;
	}
}

void logUserIn(std::string UserName, std::string Password) {
	for (int i = 0; i < usernames_list.size(); i++) {
		if (UserName == usernames_list[i]) {
			if (Password == passwords_list[i]) {
				logged = true;
				system("cls");
				std::cout << "\nYou've been logged in succesfully as " << UserName << "\n\n";
				currentUserName = UserName;
				currentUserPassword = Password;
				currentUserAdmission = admissions_list[i];
				
			};
		}
	}
}

void UI_out(int amount_of_actions, userAction actions[]) {
	int action = 0;
	for (int i = 0; i < amount_of_actions; i++) {
		if (actions[i].action_acces == currentUserAdmission || actions[i].action_acces > currentUserAdmission) {
			std::cout << i + 1 << " - " << actions[i].action_name << "\n";
		}
	}
	
	std::cout << "Choose an action >>> ";
	std::cin >> action;
	system("cls");
	if (actions[action - 1].action_acces >= currentUserAdmission) {
		actions[action - 1].action();
	}
	
	



}

void EnterMenuOut() {
	int enter_code;
	std::ofstream file;
	std::string password, username;
	bool all_good = false, invalidSlash = false, used_name = false;
	

	
	do {
		do {
			std::cout << "Hello, user!\nWould you like to\n\n1 - sign in\n2 - sign up\n>>> ";
			std::cin >> enter_code;
		} while (enter_code < 1 || enter_code > 2);


		std::cin.ignore(1000, '\n');


		if (enter_code == 1) {
			std::cout << "Enter your username\t>> ";
			
			std::getline(std::cin, username);
			std::cout << "\nEnter your password\t>> ";
			
			std::getline(std::cin, password);
		}
		else if (enter_code == 2) {
			file.open("OtherUsers.txt", std::ofstream::app);
			system("cls");
			std::cout << "Glad to see a new face around here!\nLet's begin\n";
			do {
				if (invalidSlash) {
					std::cout << "uh-oh, something went wrong\nlooks like you had forbidden symbol\ntry not to use \"|\" next time\n\n";
				}
				if (used_name) {
					std::cout << "hmmm, your nickname seem to match an existing one... try other one!\n\n";
				}
				std::cout << "Enter your username\t<< ";
				
				std::getline(std::cin, username);

				for (int i = 0; i < usernames_list.size(); i++) {
					if (username == usernames_list[i]) { used_name = true; }
				}
				for (int i = 0; i < username.length(); i++) {
					if (username[i] == '|') { invalidSlash = true; }
				}
				std::cout << "\nEnter your password\t<< ";
				std::getline(std::cin, password);
				for (int i = 0; i < password.length(); i++) {
					if (password[i] == '|') { invalidSlash = true; }
				}
				system("cls");
				if (invalidSlash == false && used_name == false) {
					all_good = true;
					
				}
			} while (all_good == false);

			file << username + "|" + password + "|" + "3" + "|" << std::endl;
			file.close();

			usernames_list.push_back(username);
			passwords_list.push_back(password);
			admissions_list.push_back(3);


			std::cout << "Welcome, " << username << "!\nYour account were created succesfully!";
		}
		logUserIn(username, password);
	} while (logged == false);
}

void createAdmin(){
	std::ofstream filework, file1("AdminList.txt"), file2("OtherUsers.txt");
	filework.open("AdminList.txt");
	if (filework.is_open() == true) {
		std::cout << "Admins list created succesfully";
	}
	else{ std::cout << "Admins list failure"; }
	filework << "Admin|Admin|1" << std::endl;
	filework.close();
	std::ofstream ;
	filework.open("OtherUsers.txt");
	if (filework.is_open() == true) {
		std::cout << "User list created succesfully";
	}
	else { std::cout << "User list failure"; }
	filework.close();


	


}
void rewrite_saves() {
	std::remove("OtherUsers.txt");
	std::ofstream file_write, file("OtherUsers.txt");
	file_write.open("OtherUsers.txt");
	for (int i = 0; i < usernames_list.size(); i++) {
		file_write << usernames_list[i] << "|" << passwords_list[i] << "|" << admissions_list[i] << "|" << std::endl;
	}
}
void delete_user(std::string username) {
	int user_index = 0, confirmation = 0;
	for (int i = 0; i < usernames_list.size(); i++) {
		if (username == usernames_list[i]) { user_index = i; }
	}
	do {
		std::cout << "Are you sure you want to delete account named \"" << username << "\"?\n1 - Yes\n2 - No, backup\n>>> ";
		std::cin >> confirmation;
		system("cls");
	} while (confirmation < 1 || confirmation > 2);
	if (admissions_list[user_index] != 1 && confirmation == 1) {
		std::vector<std::string> names_redo{}, passwords_redo{};
		std::vector<int> adm_redo{};

		for (int i = 0; i < usernames_list.size(); i++) {
			if (username != usernames_list[i]) {
				names_redo.push_back(usernames_list[i]);
				passwords_redo.push_back(passwords_list[i]);
				adm_redo.push_back(admissions_list[i]);
			}
		}
		usernames_list.swap(names_redo);
		passwords_list.swap(passwords_redo);
		admissions_list.swap(adm_redo);
		
		rewrite_saves();
		std::cout << "Account were deleted succesfully!\n";
	}
	else { std::cout << "Unable to delete user\n"; }
}



void rewrite_active_storage() {
	std::remove("AmmoProducts.txt");
	std::ofstream file_write, file("AmmoProducts.txt");
	file_write.open("AmmoProducts.txt");
	for (int i = 0; i < Ammunition.size(); i++) {
		file_write << Ammunition[i].Ammo_name << "|";
		
		if (Ammunition[i].AmmoTypesIncluded.size() != 0){
		for (int k = 0; k < Ammunition[i].AmmoTypesIncluded.size(); k++) {
		file_write << Ammunition[i].AmmoTypesIncluded[k] << "_" << Ammunition[i].AmmoTypesAmount[k] <<"_" << Ammunition[i].AmmoTypesCost[k]<< "_";
		}
		}
		file_write << "$" << std::endl;
	}
}



void moderate_store_func_() {
	int choice = 0, caliber_choice = 0, type_choice = 0;
	bool task_is_done = false, task_is_done2 = false, task_is_done3 = false, possibility = true;
	while (task_is_done == false) {
		
		do {
			std::cout << "What do you want to do?\n1 - Add a new type\n2 - Change already added one\n3 - Refill with the static storage\n4 - Go back\n>>> ";
			std::cin >> choice;
			system("cls");
		} while (choice < 1 || choice > 4);


		if (choice == 1) {
			std::string name;
			bool match = false;
			std::cout << "Enter the new caliber\n>>> ";
			std::cin.ignore(1000, '\n');
			std::getline(std::cin, name);
			for (int i = 0; i < Ammunition.size(); i++) {
				if (name == Ammunition[i].Ammo_name) {
					match = true;
				}
			}
			if (match == false) {
				AmmoType NewType{ name,{},{},{} };
				Ammunition.push_back(NewType);
				rewrite_active_storage();
			}
			else if (match == true) {
				std::cout << "This caliber is already exist";
			}

			
		}

		else if (choice == 2) {
			if (Ammunition.size() > 0) {
				do {
					system("cls");
					std::cout << "+----------\n| Choose a caliber\n+----------";
					for (int i = 0; i < Ammunition.size(); i++) {
						std::cout << "\n| " << i + 1 << " -\t" << Ammunition[i].Ammo_name;
					}
					std::cout << "\n+----------\n\n>>> ";
					std::cin >> caliber_choice;
				} while (caliber_choice < 1 || caliber_choice > Ammunition.size());
				do {
					task_is_done2 = false;
					do {
						
						std::cout << "Ammo caliber choosen: (" << Ammunition[caliber_choice - 1].Ammo_name <<
							")\n\nChoose an action:\n1 - ReName\n2 - Add a new type\n3 - Choose exact type\n4 - Delete this caliber\n5 - Go back\n>>> ";
						std::cin >> choice;
						system("cls");
					} while (choice < 1 || choice > 5);
					if (choice == 1) {
						std::cout << "\nChange (" << Ammunition[caliber_choice - 1].Ammo_name << ") to > ";
						std::cin.ignore(1000, '\n');
						std::getline(std::cin, Ammunition[caliber_choice - 1].Ammo_name);
						system("cls");
						task_is_done2 = true;
						rewrite_active_storage();
					}

					else if (choice == 2){
						system("cls");
						std::string name;
						int amount;
						float cost;
						do {
							std::cout << "/````````````````\n| -> Adding a new type:\n\\__________________\n";
							std::cout << "| Enter the name of type   : ";
							std::cin.ignore(1000, '\n');
							std::getline(std::cin, name);
							std::cout << "| Enter the amount of type : ";
							std::cin >> amount;
							std::cout << "| Enter the cost of type   : ";
							std::cin >> cost;
							std::cout << "\\__________________";
							system("cls");
							if (amount < 0 || cost < 0) {
								std::cout << "The amount of cost MUST be above zero!\n";
							}
						} while (amount < 0 || cost < 0);
						Ammunition[caliber_choice - 1].AmmoTypesAmount.push_back(amount);
						Ammunition[caliber_choice - 1].AmmoTypesCost.push_back(cost);
						Ammunition[caliber_choice - 1].AmmoTypesIncluded.push_back(name);
						rewrite_active_storage();
						




					}

					else if (choice == 3) {
						if (Ammunition[caliber_choice - 1].AmmoTypesAmount.size() == 0) {
							std::cout << "There's no types for this ammunition, add a new one!\n";
						}
						else {
							do {
								std::cout << "Caliber: " << Ammunition[caliber_choice - 1].Ammo_name;
								system("cls");
								std::cout << "+----------\n| Choose a type\n+----------";
								for (int i = 0; i < Ammunition[caliber_choice - 1].AmmoTypesIncluded.size(); i++) {
									std::cout << "\n| " << i + 1 << " -\t" << Ammunition[caliber_choice - 1].AmmoTypesIncluded[i];
								}
								std::cout << "\n+----------\n\n>>> ";
								std::cin >> type_choice;
							} while (type_choice < 1 || type_choice > Ammunition[caliber_choice - 1].AmmoTypesIncluded.size());
							do {
								task_is_done3 = false;
								do {
									system("cls");
									std::cout << "Ammo choosen: (" << Ammunition[caliber_choice - 1].AmmoTypesIncluded[type_choice - 1]
										<< ") in a (" << Ammunition[caliber_choice - 1].Ammo_name <<
										") caliber\n\nActions:\n1 - ReName\n2 - Change amount (" <<
										Ammunition[caliber_choice - 1].AmmoTypesAmount[type_choice - 1]
										<< ")\n3 - Change cost (" <<
										Ammunition[caliber_choice - 1].AmmoTypesCost[type_choice - 1]
										<< ")\n4 - Delete\n5 - Go back\n\n>>> ";
									std::cin >> choice;
								} while (choice < 1 || choice > 5);
								system("cls");
								if (choice == 1) {
									std::cout << "Change name from (" << Ammunition[caliber_choice - 1].AmmoTypesIncluded[type_choice - 1]
										<< ") to > ";
									std::cin.ignore(1000, '\n');
									std::getline(std::cin, Ammunition[caliber_choice - 1].AmmoTypesIncluded[type_choice - 1]);
									rewrite_active_storage();
								}
								else if (choice == 2) {
									std::cout << "Change amount from (" << Ammunition[caliber_choice - 1].AmmoTypesAmount[type_choice - 1]
										<< ") to > ";
									std::cin >> Ammunition[caliber_choice - 1].AmmoTypesAmount[type_choice - 1];
									rewrite_active_storage();
								}
								else if (choice == 3) {
									std::cout << "Change cost from (" << Ammunition[caliber_choice - 1].AmmoTypesCost[type_choice - 1]
										<< ") to > ";
									std::cin >> Ammunition[caliber_choice - 1].AmmoTypesCost[type_choice - 1];
									rewrite_active_storage();
								}
								else if (choice == 4) {
									int type_index = 0;
									std::vector<std::string>types_redo{};
									std::vector<int>amounts_redo{};
									std::vector<float>costs_redo{};
									for (int i = 0; i < Ammunition[caliber_choice - 1].AmmoTypesIncluded.size(); i++) {
										if (Ammunition[caliber_choice - 1].AmmoTypesIncluded[i] != Ammunition[caliber_choice - 1].AmmoTypesIncluded[type_choice - 1]) {
											types_redo.push_back(Ammunition[caliber_choice - 1].AmmoTypesIncluded[i]);
											amounts_redo.push_back(Ammunition[caliber_choice - 1].AmmoTypesAmount[i]);
											costs_redo.push_back(Ammunition[caliber_choice - 1].AmmoTypesCost[i]);

											

										}
									}
									Ammunition[caliber_choice - 1].AmmoTypesIncluded.swap(types_redo);
									Ammunition[caliber_choice - 1].AmmoTypesAmount.swap(amounts_redo);
									Ammunition[caliber_choice - 1].AmmoTypesCost.swap(costs_redo);
									task_is_done3 = true;
									rewrite_active_storage();



								}
								else if (choice == 5) { task_is_done3 = true; }


							} while (task_is_done3 == false);
						}
					}







					else if (choice == 4) {
						std::vector<AmmoType> AmmoRedo{};
						for (int i = 0; i < Ammunition.size(); i++) {
							if (i != caliber_choice - 1) { AmmoRedo.push_back(Ammunition[i]); }
						}
						system("cls");
						Ammunition.swap(AmmoRedo);
						rewrite_active_storage();
						std::cout << "Ammo caliber was deleted succesfully\n";
						task_is_done2 = true;

					}
					else if (choice == 5) { task_is_done2 = true; system("cls"); }

				} while (task_is_done2 == false);
			}
			else { std::cout << "NO AMMUNITION ADDED! Restore your active storage, or add a new ammo type by yourself!\n"; }
		}

		else if (choice == 3) {  
			do {
				std::cout << "Are you sure you DO want to refill?\nAny custom calibers will be vanished\n\n1 - Yes, refill\n2 - No, go back\n>>>";
				std::cin >> choice;
			} while(choice < 1 || choice > 2);
			Ammunition.swap(Ammunition_Static);
			Ammunition_Static.clear();
			write_static_storage();
			rewrite_active_storage();
			system("cls"); 
			task_is_done = true;
			std::cout << "Storage refilled succesfully!\n";
}

		else if (choice == 4) { task_is_done = true; system("cls"); }}
}
void view_static_storage_func_() {
	read_storage(Ammunition_Static);
}
void renew_current_storage_func_() {
	std::cout << "blank storage you see, there's current things you can change\n";
}
void view_store_func_() {
	std::cout << "blank store, wow wow, so many types of ammunition here, look, ooo\n";
}
void view_cart_func_() {
	std::cout << "there's your cart, so many shit buyed, you did\n";
}
void manage_your_account_func_(){
	bool operation_complete = false;
	int choice = 0;
	while (operation_complete == false) {
		system("cls");
		do {
			std::cout << "Your account, " << currentUserName << " user\n\n1 - Change your username(soon)\n2 - change your password(soon)\n3 - log out\n4 - delete account\n5 - back\n>>> ";
			std::cin >> choice;
		} while (choice < 1 || choice > 5);
		if (choice == 3) {
			system("cls");
			std::cout << "You've logged out!\n\n";
			logged = false;
			operation_complete = true;
		}
		else if (choice == 4) { 
			do {
				system("cls");
				std::cout << "Are you sure you want to delete your account?\n1 - Yes :(\n2 - No! :D\n>>> ";
				std::cin >> choice;
			} while (choice < 1 || choice > 2);
			if (choice == 1) {
				delete_user(currentUserName);
				std::cout << "User account was deleted succesfully\n";
			}
			else { system("cls"); }
		logged = false; operation_complete = true; }
		else if (choice == 5) { operation_complete = true; }
		
	}

	
}

void adm_manage_user_acc_func_() {
	int choice = 0, user_select = 0;
	bool task_is_complete = false;
	while (task_is_complete == false) {
		
		do {
			std::cout << "Users:\n\tNames\t\tPasswords\tAdmission\n";
			for (int i = 0; i < usernames_list.size(); i++) {
				std::cout << "(" << i + 1 << ") - " << "\t" << usernames_list[i] << "\t\t" << passwords_list[i] << "\t\t" << admissions_list[i] << "\n";
			}
			std::cout << "\n\nChoose an account : ";
			std::cin >> user_select;
			system("cls");
		} while (user_select < 1 || user_select >usernames_list.size() );
		do {
			std::cout << "Account selected: ("<<usernames_list[user_select -1]<<")\nAction?\n1 - Change properties\n2 - delete\n3 - nothing\n>>> ";
			std::cin >> choice;
			system("cls");
		} while (choice < 1 || choice > 3);

		if (choice == 1) {
			do {
				std::cout << "Account selected: (" << usernames_list[user_select - 1] << ")\n\nProperties:\n1 - Change name\n2 - Change password\n3 - Change admission\n>>> ";
				std::cin >> choice;
				system("cls");
			} while (choice < 1 || choice > 3);
			if (choice == 1) {
				std::cout << "Enter the new name for account (" << usernames_list[user_select - 1] << ")\n>>> ";
				std::cin.ignore(1000, '\n');
				std::getline(std::cin, usernames_list[user_select - 1]);
			}
			else if (choice == 2) {
				std::cout << "Enter the new password for account (" << usernames_list[user_select - 1] << ")\n(Current is " 
					<< passwords_list[user_select - 1] <<")\n>>> ";
				std::cin.ignore(1000, '\n');
				std::getline(std::cin, passwords_list[user_select - 1]);
			}
			else if (choice == 3) {
				std::cout << "Enter the new name for account (" << usernames_list[user_select - 1] << ")\n(Current is " 
					<< admissions_list[user_select - 1] << ")\n>>> ";;
				std::cin >> admissions_list[user_select - 1];
			}
		}


		else if (choice == 2) { delete_user(usernames_list[user_select - 1]); }
		else if (choice == 3) { task_is_complete = true; }
		
	}
}


int main() {
	const int amount_of_actions = 6;
	int action_number = 0;
	bool task_ended = false;
	///createAdmin();
	
	userAction actions[amount_of_actions]{};

	if (true) {
		actions[action_number].action_name = "moderate current storage";
		actions[action_number].action = moderate_store_func_;
		actions[action_number].action_acces = 1;

		action_number = 1;

		actions[action_number].action_name = "view static storage";
		actions[action_number].action = view_static_storage_func_;
		actions[action_number].action_acces = 1;

		action_number = 2;

		actions[action_number].action_name = "view store(planned)";
		actions[action_number].action = view_store_func_;
		actions[action_number].action_acces = 3;

		action_number = 3;

		actions[action_number].action_name = "view your cart(planned)";
		actions[action_number].action = view_cart_func_;
		actions[action_number].action_acces = 3;

		action_number = 4;

		actions[action_number].action_name = "moderate users";
		actions[action_number].action = adm_manage_user_acc_func_;
		actions[action_number].action_acces = 1;

		action_number = 5;

		actions[action_number].action_name = "your account";
		actions[action_number].action = manage_your_account_func_;
		actions[action_number].action_acces = 3;

	}

	write_static_storage();
	write_active_storage();
	rewrite_active_storage();
	
	
	

	createLists();

	do {
		while (logged == false){
			EnterMenuOut();
		} 
		UI_out(amount_of_actions, actions);
	} while (task_ended == false);
	return 0;
}