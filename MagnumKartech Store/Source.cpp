#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <Windows.h>


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


std::string currentUserName, currentUserPassword, current_user_cart_directory;
int currentUserAdmission, cartContainmentAmount = 0;
bool logged = false;
float total_cart_cost = 0;

std::vector<std::string> usernames_list, passwords_list;
std::vector<int> admissions_list;

std::vector<AmmoType>Ammunition_Static{}, Ammunition{}, CartContainment{};



void write_static_storage() {
	std::ifstream file;
	file.open("AmmoProductsStatic.txt");
	bool ammoCaliberEntered = false; //explains when the ammo caliber is entered and where is the end of the line;
	int heading = 0; //from 0 to 2, explains where information to store, like 0 for ammo type, 1 for amount and 2 for cost per round
	std::string line, word;

	std::string overall_name;
	std::vector<std::string> ammo_types;
	std::vector<int> ammo_amount;
	std::vector<float> ammo_cost;
	if (file.is_open()) {
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
	if (file.is_open()) {
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
}


void read_storage(std::vector<AmmoType> storage) {
	for (int i = 0; i < storage.size(); i++) {

		std::cout << "\n+---------->\n| Ammo Caliber: " << storage[i].Ammo_name << "\n+---------->";
		std::cout << "\n| Ammo types:";
		for (int k = 0; k < storage[i].AmmoTypesIncluded.size(); k++) {
			std::cout << "\t|" << storage[i].AmmoTypesIncluded[k];
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

void createLists() {
	std::string line, word;
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

void delete_caliber_from_cart_(std::string caliber) {
	std::vector<AmmoType>Cart_Redo{};
	for (int i = 0; i < CartContainment.size(); i++) {
		if (CartContainment[i].Ammo_name != caliber) {
			Cart_Redo.push_back(CartContainment[i]);
		}
	}
	CartContainment.swap(Cart_Redo);
}
void delete_type_from_cart_(std::string caliber, std::string type) {
	std::vector < std::string > Names_redo{};
	std::vector <int> amount_redo{};
	int a;


	for (int i = 0; i < CartContainment.size(); i++) {
		for (int k = 0; k < CartContainment[i].AmmoTypesIncluded.size(); k++) {
			if (CartContainment[i].Ammo_name == caliber) {
				if (CartContainment[i].AmmoTypesIncluded[k] != type) {
					Names_redo.push_back(CartContainment[i].AmmoTypesIncluded[k]);
					amount_redo.push_back(CartContainment[i].AmmoTypesAmount[k]);
				}
				CartContainment[i].AmmoTypesAmount.swap(amount_redo);
				CartContainment[i].AmmoTypesIncluded.swap(Names_redo);
			}
		}
	}
	

}


void write_carts() {
	std::ifstream file;
	file.open(current_user_cart_directory);
	bool ammoCaliberEntered = false; //explains when the ammo caliber is entered and where is the end of the line;
	int heading = 0; //from 0 to 2, explains where information to store, like 0 for ammo type, 1 for amount and 2 for cost per round
	std::string line, word;

	std::string overall_name;
	std::vector<std::string> ammo_types;
	std::vector<int> ammo_amount;
	std::vector<float> ammo_cost;
	if (file.is_open()) {
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
					CartContainment.push_back(AmmoType(overall_name, ammo_types, ammo_amount, ammo_cost));
					ammo_types.clear();
					ammo_amount.clear();
					ammo_cost.clear();
				}
			}
		}
	}
}
void cart_in_file_rewrite() {
	std::ofstream file_write, file(current_user_cart_directory);
	file_write.open(current_user_cart_directory);
	if (CartContainment.size() != 0) {
		for (int i = 0; i < CartContainment.size(); i++) {
			file_write << CartContainment[i].Ammo_name << "|";

			if (CartContainment[i].AmmoTypesIncluded.size() != 0) {
				for (int k = 0; k < CartContainment[i].AmmoTypesIncluded.size(); k++) {
					file_write << CartContainment[i].AmmoTypesIncluded[k] << "_" << CartContainment[i].AmmoTypesAmount[k] << "_" << CartContainment[i].AmmoTypesCost[k] << "_";
				}
			}
			file_write << "$" << std::endl;
		}
	}
}
void cart_proportions_renew() {
	int index = 0;
	bool caliber_match1 = false;
	cartContainmentAmount = 0;
	total_cart_cost = 0.0;
	std::vector<AmmoType>Cart_Redo{};

	if (CartContainment.size() != 0) {
		for (int i = 0; i < CartContainment.size(); i++) {
			if (cartContainmentAmount + CartContainment[i].AmmoTypesIncluded.size() != 0) {
				Cart_Redo.push_back(CartContainment[i]);
			}
			else {
				std::cout << "Caliber " << CartContainment[i].Ammo_name << " was removed because of emptiness\n";
			}
			cartContainmentAmount += CartContainment[i].AmmoTypesIncluded.size();
		}

		for (int i = 0; i < CartContainment.size(); i++) {
			caliber_match1 = false;
			for (int k = 0; k < Ammunition.size(); k++) {
				if (CartContainment[i].Ammo_name == Ammunition[k].Ammo_name) {
					caliber_match1 = true;
				}
			}
			if (caliber_match1 == false) {
				delete_caliber_from_cart_(CartContainment[i].Ammo_name);
			}
		}
		CartContainment.swap(Cart_Redo);
		Cart_Redo.clear();

		for (int i = 0; i < CartContainment.size(); i++) {
			for (int k = 0; k < CartContainment[i].AmmoTypesIncluded.size(); k++) {
				if (CartContainment[i].AmmoTypesAmount[k] < 0) { CartContainment[i].AmmoTypesAmount[k] = 0; }
				
				for (int l = 0; l < Ammunition.size(); l++) {
					for (int b = 0; b < Ammunition[l].AmmoTypesIncluded.size(); b++) {
						if (Ammunition[l].Ammo_name == CartContainment[i].Ammo_name && Ammunition[l].AmmoTypesIncluded[b] == CartContainment[i].AmmoTypesIncluded[k]) {
							if (CartContainment[i].AmmoTypesAmount[k] > Ammunition[l].AmmoTypesAmount[b]) {
								CartContainment[i].AmmoTypesAmount[k] = Ammunition[l].AmmoTypesAmount[b];

							}
							CartContainment[i].AmmoTypesCost[k] = Ammunition[l].AmmoTypesCost[b];
						}

					}
				}
			}
		}

		
		

		for (int i = 0; i < CartContainment.size(); i++) {
			for (int k = 0; k < CartContainment[i].AmmoTypesIncluded.size(); k++) {
				total_cart_cost += CartContainment[i].AmmoTypesCost[k] * CartContainment[i].AmmoTypesAmount[k];
			}
		}

		


	}
		cart_in_file_rewrite();





};



void logUserIn(std::string UserName, std::string Password) {
	for (int i = 0; i < usernames_list.size(); i++) {
		if (UserName == usernames_list[i]) {
			if (Password == passwords_list[i]) {
				logged = true;
				system("cls");
				std::cout << "\nYou've been logged in succesfully as " << UserName << "\n";
				currentUserName = UserName;
				currentUserPassword = Password;
				currentUserAdmission = admissions_list[i];
				current_user_cart_directory = "CartsSaves/" + currentUserName + ".txt";
				std::ifstream file;
				std::ofstream file_write;
				file.open(current_user_cart_directory);
				if (!file.is_open()) {
					std::ofstream file_create(current_user_cart_directory);
					std::cout << "Looks like you're new here! We have created your cart folder!\n";
				}
				file.close();
				std::cout << "\n";
				write_carts();
				
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

		if (Ammunition[i].AmmoTypesIncluded.size() != 0) {
			for (int k = 0; k < Ammunition[i].AmmoTypesIncluded.size(); k++) {
				file_write << Ammunition[i].AmmoTypesIncluded[k] << "_" << Ammunition[i].AmmoTypesAmount[k] << "_" << Ammunition[i].AmmoTypesCost[k] << "_";
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

					else if (choice == 2) {
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
			} while (choice < 1 || choice > 2);
			Ammunition.swap(Ammunition_Static);
			Ammunition_Static.clear();
			write_static_storage();
			rewrite_active_storage();
			system("cls");
			task_is_done = true;
			std::cout << "Storage refilled succesfully!\n";
		}

		else if (choice == 4) { task_is_done = true; system("cls"); }
	}
}
void view_static_storage_func_() {
	read_storage(Ammunition_Static);
}
void renew_current_storage_func_() {
	std::cout << "blank storage you see, there's current things you can change\n";
}



void store_UI_out() {
	std::cout << std::left <<
		"+-------------------\n" <<
		"|   Store page\n" <<
		"+-------------------\n" << std::setw(16) << "| Calibers" << std::setw(32) << "Types" << std::setw(16) << "(Amount)" << std::setw(16) << "(cost per round)\n";
	for (int i = 0; i < Ammunition.size(); i++) {
		std::cout << std::left << "| " << i + 1 << "] " << Ammunition[i].Ammo_name << std::endl;
		for (int k = 0; k < Ammunition[i].AmmoTypesIncluded.size(); k++) {
			std::cout << std::left << std::setw(13) << "|    :-" << k + 1 << ") " << std::setw(32) << Ammunition[i].AmmoTypesIncluded[k] << std::setw(16)
				<< Ammunition[i].AmmoTypesAmount[k] << std::setw(32)
				<< Ammunition[i].AmmoTypesCost[k] << std::endl;
		}
	}
}

void view_store_func_() {
	bool task1_isEnded = false;
	int choice = 0, caliber, type, amount = 0, CaliberMatch = -1, TypeMatch = -1;
	while (task1_isEnded == false) {
		do {
			store_UI_out();
			std::cout << "\nChoose an action\n1 - Make a purchase\n2 - Back\n\n>>> ";
			std::cin >> choice;
			system("cls");
		} while (choice < 1 || choice > 2);
		if (choice == 1) {
			do {
				store_UI_out();
				std::cout << "Choose a caliber\n>>> ";
				std::cin >> caliber;
				system("cls");
			} while (caliber < 1 || caliber > Ammunition.size());
			
			do {
				std::cout << "\nCaliber choosen: (" << Ammunition[caliber - 1].Ammo_name <<")\nChoose a type:\n";
				for (int i = 0; i < Ammunition[caliber - 1].AmmoTypesIncluded.size(); i++) {
					std::cout << i + 1 << ") - " << Ammunition[caliber - 1].AmmoTypesIncluded[i]<< std::endl;
				}
				std::cout << "\n>>> ";
				std::cin >> type;
				system("cls");
			} while (type < 1 || type > Ammunition[caliber-1].AmmoTypesIncluded.size());


			do {
				std::cout << "Amount: ";
				std::cin >> amount;
				system("cls");
			} while (amount < 0);
			if (amount > Ammunition[caliber - 1].AmmoTypesAmount[type - 1]) {
				amount = Ammunition[caliber - 1].AmmoTypesAmount[type - 1];
			}
			
			

			for (int i = 0; i < Ammunition.size(); i++) {


				for (int b = 0; b < Ammunition[i].AmmoTypesIncluded.size(); b++) {
					for (int k = 0; k < CartContainment.size(); k++) {
						if (Ammunition[caliber - 1].Ammo_name == CartContainment[k].Ammo_name) {
							CaliberMatch = k;
							std::cout << "Calibers match fnd: " << Ammunition[i].Ammo_name << " - " 
								<< CartContainment[k].Ammo_name << std::endl;
							Sleep(40);
						}
						for (int n = 0; n < CartContainment[k].AmmoTypesIncluded.size(); n++) {
							if (Ammunition[caliber - 1].AmmoTypesIncluded[type - 1] == CartContainment[k].AmmoTypesIncluded[n]) {
								TypeMatch = n;
								std::cout << "Ammunition: " << Ammunition[i].Ammo_name << " - " << CartContainment[k].Ammo_name << std::endl;
								std::cout << "Match fnd: " << Ammunition[i].AmmoTypesIncluded[b]<<" - "<< CartContainment[k].AmmoTypesIncluded[n] << std::endl;
							}
						}
					}
				}
			}
			Sleep(200);
			if (CaliberMatch == -1) {
				CartContainment.push_back(AmmoType(Ammunition[caliber - 1].Ammo_name, 
					{ Ammunition[caliber - 1].AmmoTypesIncluded[type - 1]},
					{ amount },
					{ Ammunition[caliber - 1].AmmoTypesCost[type - 1] }));
				std::cout << "Caliber not found\n";
				Sleep(25);
			}

			else if (CaliberMatch != -1 && TypeMatch == -1) {
				CartContainment[CaliberMatch].AmmoTypesIncluded.push_back(Ammunition[caliber - 1].AmmoTypesIncluded[type - 1]);
				CartContainment[CaliberMatch].AmmoTypesAmount.push_back(amount);
				CartContainment[CaliberMatch].AmmoTypesCost.push_back(Ammunition[caliber - 1].AmmoTypesCost[type - 1]);
				std::cout << "Caliber found, no type";
				Sleep(25);
			}
			else if (CaliberMatch != -1 && TypeMatch != -1) {
				CartContainment[CaliberMatch].AmmoTypesAmount[TypeMatch] += amount;
				std::cout << "Caliber found, type found";
				Sleep(25);
			}
			cart_proportions_renew();
		
		
			system("cls");
		
		
		}
		if (choice == 2) { task1_isEnded = true; }

	}
}

void view_cart_func_() {
	std::string word;
	bool task1_isEnded = false, task2_isEnded = false, task3_isEnded = false;
	int choice1 = 0, ammo_caliber, ammo_type;
	while (task1_isEnded == false) {
		cart_proportions_renew();

		if (cartContainmentAmount != 0 && CartContainment.size()!= 0) {
			do {
				std::cout << std::left <<
					"+-------------------\n" <<
					"| Your cart contains " << cartContainmentAmount << " positions in total!\n" <<
					"+-------------------\n" << std::setw(16)<< "| Calibers" << std::setw(32) <<"Types" << std::setw(16) << "(Amount)" << std::setw(24) << "(cost per round)"
					<< std::setw(8) << "(Total cost)\n";
				for (int i = 0; i < CartContainment.size(); i++) {
					std::cout << std::left << "| " << i + 1 << "] " << CartContainment[i].Ammo_name << std::endl;
					for (int k = 0; k < CartContainment[i].AmmoTypesIncluded.size(); k++) {
						std::cout << std::left << std::setw(13) << "|    :-" << k + 1 << ") " << std::setw(32) << CartContainment[i].AmmoTypesIncluded[k] << std::setw(16) 
							<< CartContainment[i].AmmoTypesAmount[k] << std::setw(24)
							<< CartContainment[i].AmmoTypesCost[k] << std::setw(16) << CartContainment[i].AmmoTypesCost[k] * CartContainment[i].AmmoTypesAmount[k] << std::endl;
					}
				}
				std::cout << std::left << "\\_________________\n" <<
					"\n\nTotal cost of your cart is " << total_cart_cost << "!\n\nWould you like to:\n1 - Buy all of these (" << total_cart_cost << ")\n" <<
					"2 - Change containings of your cart\n3 - Back\n\n>>> ";
				std::cin >> choice1;
				system("cls");
			} while (choice1 < 1 || choice1 > 3);
			if (choice1 == 1) {

				for (int i = 0; i < Ammunition.size(); i++) {
					for (int b = 0; b < Ammunition[i].AmmoTypesIncluded.size(); b++) {
						for (int k = 0; k < CartContainment.size(); k++) {
							for (int n = 0; n < CartContainment[k].AmmoTypesIncluded.size(); n++) {
								if (Ammunition[i].AmmoTypesIncluded[b] == CartContainment[k].AmmoTypesIncluded[n]) {
									Ammunition[i].AmmoTypesAmount[b] -= CartContainment[k].AmmoTypesAmount[n];
								}




							}
						}
					}
				}


				do {
					cart_proportions_renew();
					rewrite_active_storage();
					std::cout << "Purchase were made succesfully!\n\nWould you like to save your current cart,\nor we better clean it?\n\n1 - Save current\n2 - Make it clean\n\n>>> ";
					std::cin >> choice1;
					system("cls");
				} while (choice1 < 1 || choice1 > 2);
				if (choice1 == 1) {}
				else if (choice1 == 2) {
					CartContainment.clear();
					
					std::cout << "Your cart was cleared succesfully!\n\n";
				}
			}
			else if (choice1 == 2) { 
				
					
					do {
						std::cout << "+-------------------\n" << "| Choose a caliber first (left column)\n" << "+-------------------\n";
						std::cout <<std::left<< std::setw(16) << "| Calibers" << std::setw(32) << "Types" << std::setw(16) << "(Amount)" << std::setw(24) << "(cost per round)"
							<< std::setw(8) << "(Total cost)\n";
						for (int i = 0; i < CartContainment.size(); i++) {
							std::cout << std::left << "| " << i + 1 << "] " << CartContainment[i].Ammo_name << std::endl;
							for (int k = 0; k < CartContainment[i].AmmoTypesIncluded.size(); k++) {
								std::cout << std::left << std::setw(13) << "|    :-" << k + 1 << ") " << std::setw(32) << CartContainment[i].AmmoTypesIncluded[k] << std::setw(16)
									<< CartContainment[i].AmmoTypesAmount[k] << std::setw(24)
									<< CartContainment[i].AmmoTypesCost[k] << std::setw(16) << CartContainment[i].AmmoTypesCost[k] * CartContainment[i].AmmoTypesAmount[k] << std::endl;
							}
						}
						std::cout << ">>> ";
						std::cin >> ammo_caliber;
						system("cls");
					} while (ammo_caliber < 1 || ammo_caliber > CartContainment.size());
					do {
						std::cout << "Caliber choosen: " << CartContainment[ammo_caliber - 1].Ammo_name <<"\n";
						for (int i = 0; i < CartContainment[ammo_caliber - 1].AmmoTypesIncluded.size(); i++) {
							std::cout << "| " << i + 1 << ") " << CartContainment[ammo_caliber - 1].AmmoTypesIncluded[i] << std::endl;
						}
						std::cout << ">>> ";
						std::cin >> ammo_type;
						system("cls");
					} while(ammo_type < 1 || ammo_type > CartContainment[ammo_caliber - 1].AmmoTypesIncluded.size());
					do {
						std::cout << "Choosen type \"" << CartContainment[ammo_caliber - 1].AmmoTypesIncluded[ammo_type - 1] << "\" of a " << CartContainment[ammo_caliber - 1].Ammo_name <<
							" caliber\n\n" << "What do you want to do?\n1 - Change amount (current:"<< 
							CartContainment[ammo_caliber - 1].AmmoTypesAmount[ammo_type - 1] <<")\n2 - Delete\n3 - Back\n>>> ";
						std::cin >> choice1;
					}while (choice1 < 1 || choice1 > 3);
					if (choice1 == 1) {
						std::cout << "Enter a new value(current:" << CartContainment[ammo_caliber - 1].AmmoTypesAmount[ammo_type - 1] << "): ";
						std::cin >> CartContainment[ammo_caliber - 1].AmmoTypesAmount[ammo_type - 1];
						task2_isEnded == true;
						cart_proportions_renew();
					}
					else if (choice1 == 2) {
						delete_type_from_cart_(CartContainment[ammo_caliber - 1].Ammo_name, CartContainment[ammo_caliber - 1].AmmoTypesIncluded[ammo_type - 1]);
						
					}
					else if(choice1 == 3){
						task2_isEnded == true;
					}
					
				
				
			}
			else if (choice1 == 3) { task1_isEnded = true; }
		}
		else {
			std::cout << "Your cart is currently empty\n";
			task1_isEnded = true;
		}
	}
}

void manage_your_account_func_() {
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
			logged = false; operation_complete = true;
		}
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
		} while (user_select < 1 || user_select >usernames_list.size());
		do {
			std::cout << "Account selected: (" << usernames_list[user_select - 1] << ")\nAction?\n1 - Change properties\n2 - delete\n3 - nothing\n>>> ";
			std::cin >> choice;
			system("cls");
		} while (choice < 1 || choice > 3);

		if (choice == 1) {

			if (admissions_list[user_select - 1] != 1) {
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
						<< passwords_list[user_select - 1] << ")\n>>> ";
					std::cin.ignore(1000, '\n');
					std::getline(std::cin, passwords_list[user_select - 1]);
				}
				else if (choice == 3) {
					std::cout << "Enter the new name for account (" << usernames_list[user_select - 1] << ")\n(Current is "
						<< admissions_list[user_select - 1] << ")\n>>> ";;
					std::cin >> admissions_list[user_select - 1];
				}
			}
			else { std::cout << "Unable to change properties of admin account"; }
		}


		else if (choice == 2) { delete_user(usernames_list[user_select - 1]); }
		else if (choice == 3) { task_is_complete = true; }

	}
}

void first_start() {
	std::ifstream file;
	std::ofstream file_write;
	file.open("AmmoProductsStatic.txt");
	if (!file.is_open()) {
		std::ofstream file_read1("AmmoProductsStatic.txt");
		file_write.open("AmmoProductsStatic.txt");
		file_write << "7.62x39|HP_100_90_SP_100_90_AP_100_90_Tracer_100_90_$\n";
		file_write << "12g|Slug_140_90_Shrap_200_90_Kartech_200_90_Tracer Slug_100_90_Dragon Breath_200_150_$\n";
		file_write << "45.ACP|HP_100_40_SP_100_50_Tracer_100_90_$\n";
		file_write << "50.|HE_140_1100_AP_50_900_Tracer_200_700_APHE_100_1600_$\n";
		file_write.close();
		std::cout << "File \"Static\" was created via \"blank slate\" scenario\n";
	}
	file.close();
	file.open("AmmoProducts.txt");
	if (!file.is_open()) {
		std::ofstream file_read2("AmmoProducts.txt");
		std::cout << "File \"Mobile\" was created via \"blank slate\" scenario\n";
	}
	file.close();
	file.open("OtherUsers.txt");
	if (!file.is_open()) {
		std::ofstream file_read3("OtherUsers.txt");
		file_write.open("OtherUsers.txt");
		file_write << ("Admin|Admin|1|");
		file_write.close();
		std::cout << "File \"Users\" was created via \"blank slate\" scenario\n";
		std::cout << "Default admin account name is \"Admin\" and password is equal\n\n";
	}
	file.close();
	file.open("AllCarts.txt");
	if (!file.is_open()) {
		std::ofstream file_read4("AllCarts.txt");
		std::cout << "File \"Carts\" was created via \"blank slate\" scenario\n";
	}
	file.close();

	file.open("CartsSaves/BlankConfirmation.txt");
	if (!file.is_open()) {
		system("mkdir CartsSaves");
		std::ofstream file_read5("CartsSaves/BlankConfirmation.txt");
		file_write.open("CartsSaves/BlankConfirmation.txt");
		file_write << ("DO NOT DELETE THIS FILE! OR ALL CARTS WILL BE DELETED AS WELL!!");
		file_write.close();
		std::cout << "Folder \"Carts\" was created via \"blank slate\" scenario\n";
	}
	file.close();

}

void credits_() {
	std::cout <<
		"Greetings, Dear user! :D\nThis programm were created\ndue to need of making some kind of shop\nvia C++ programming language!"<<
		"\n\nThere's still some work to do\nand i would be really happy if\nyou'll send me some feedback in comments to repository!\n\nLink: "
		<<"https://github.com/RiftSquadronMember/MagnumKartech-Store.git\n\n"<<
		"Also! This code is sharing via \"Apache 2.0\" License!\n\n" <<
		"Glory to corporation!\nEcho 1-1 out!\n\n";
	std::cout <<
		"       _______\n" <<
		"     _/   |   \\_\n" <<
		"    /    / \\    \\\n" <<
		"   /____/   \\____\\\n" <<
		"  | \\__       __/ |\n" <<
		"  |    \\     /    |\n" <<
		"   \\   /     \\   /\n" <<
		"    \\ /  ___  \\ /\n" <<
		"     \\__/   \\__/\n" <<
		"      \\       /\n" <<
		"       \\     /\n" <<
		"        \\   /\n" <<
		"         \\_/\n";
	system("pause");
	system("cls");
}

int main() {
	const int amount_of_actions = 7;
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
		actions[action_number].action_acces = 2;

		action_number = 2;

		actions[action_number].action_name = "view store";
		actions[action_number].action = view_store_func_;
		actions[action_number].action_acces = 3;

		action_number = 3;

		actions[action_number].action_name = "view your cart";
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

		action_number = 6;

		actions[action_number].action_name = "Credits";
		actions[action_number].action = credits_;
		actions[action_number].action_acces = 3;

	}
	first_start();
	write_static_storage();
	write_active_storage();
	rewrite_active_storage();



	createLists();

	do {
		while (logged == false) {
			EnterMenuOut();
		}
		UI_out(amount_of_actions, actions);
	} while (task_ended == false);
	return 0;
}
