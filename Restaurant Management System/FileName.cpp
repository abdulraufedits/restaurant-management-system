#include <iostream>
#include <string>
#include <fstream>
using namespace std;
ofstream fileo;
ifstream filei;
string username;
int i = 0;
void onboarding();
void staffMenu();
void adminMenu();
void showMenu();
void valid(string str);
void storeOrder(int dish[], int orderNo, int k);

void userLogin(string password, string faculty, string fname) {
	string user, pswrd;
	cout << "Who are you? (Staff/Customr): ";
	cin >> faculty;
	cout << "Enter your username:";
	cin >> username;
	cout << "\nEnter your password:";
	cin >> password;
	fname = faculty + ".txt";
	filei.open(fname.c_str());
	bool passed = false;
	while (getline(filei, user)) {
		if (user == username) {
			getline(filei, pswrd);
			if (pswrd == password) {
				passed = true;
				break;
			}
		}
	}
	if (passed == true) {
		cout << "Welcome back " << user << "!\n";
		filei.close();
		if (faculty == "staff" || faculty == "Staff") {
			staffMenu();
		}
		else if (username == "admin" && password == "admin") {
			adminMenu();
		}
		else {
			onboarding();
		}
	}
	if (passed == false)
	{
		cout << "\nYou are not registered, please register before logging in.\n";
		filei.close();
		return;
	}
	
	cout << endl;
}

void userRegister(string password, string faculty, string fname) {
	cout << "Who are you? (Staff/Customr): ";
	cin >> faculty;
	cout << "Create a username:";
	cin >> username;
	i = 0;
	valid(faculty);
	if (i >= 3)
	{
		userRegister(password, faculty, fname);
	}
	cout << "Create a password:";
	cin >> password;
	fname =faculty + ".txt";
	//cout<<fname;
	fileo.open(fname, ios::app);
	fileo << username << endl << password << endl;
	cout << "\nYou are successfully registered. Please login to continue.\n";
	fileo.close();
}
void adminMenu() {

}
void onboarding() {
	int orderNo = 1;
	string action;
	bool loop = true;
	do {
		cout << "Press 'menu' to see the menu\n";;
		cout << "Press 'logout to logout\n";
		cin >> action;
		if (action == "menu") {
			bool closeOrder = false;
			int k = 0;
			int dish[1] = { NULL };
			char opt;
			showMenu();
			do {
				cout << "Enter the serial number of the dish you want: ";
				cin >> dish[k];
				cout << "Add another dish? (Y/N) ";
				cin >> opt;
				if (opt == 'Y') {
					k++;
				}
				else if (opt == 'N') {
					closeOrder = true;
				}
			} while (closeOrder == false);
			storeOrder(dish, orderNo, k);
			orderNo++;
		}
		else if (action == "logout") {
			loop = false;
		}
	} while (loop == true);
}
void showMenu() {

	string menuData = "menuData.txt";
	filei.open(menuData.c_str());
	string menuTxt;
	while (getline(filei, menuTxt)){
		cout << menuTxt << endl;
	}
	
}
void storeOrder(int dish[], int orderNo,int k) {
	fileo.open("menuList.txt", ios::app);
	for (int x = 0; x < k+1; x++) {
		fileo << "\nOrder #" << orderNo << endl;
		fileo << dish[x] << " ";
	}
}
void showOrder() {
	string menuList = "menuList.txt";
	filei.open(menuList.c_str());
	string menuTxt;
	while (getline(filei, menuTxt)) {
		cout << menuTxt << endl;
	}
}
void staffMenu(){
	int action;
	bool loop = true;
	do {
		cout << "\nPress 1 to check the pending orders\n";
		cout << "Press 2 to edit menu\n";
		cout << "Press 3 to check the customer feedbacks\n";
		cout << "Press 4 to logout";
		cin >> action;
		switch (action) {
		case 1:
			showOrder();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			loop = false;
			break;
		}
	} while (loop == true);
}
void valid(string faculty)
{
	string dir, user;
	bool passed = false;
	ifstream file;
	dir = faculty + ".txt";
	file.open(dir.c_str());
	do {
		getline(file, user);
		if (user != username) {
			passed = true;
			break;
		}
	} while (getline(file, user));
	if (passed == true) {
		return;
	}
	else if(passed == false)
	{
		i++;
		if (i == 3)
		{
			cout << "\nThis username already exists\nPlease try Again.\n";
			//file.close();
			return;
		}
		cout << "\nThis username already exists!\nCreate a username:";
		cin >> username;
		//file.close();
		valid(faculty);
	}
}

int main() {
	string password, faculty, fname;
	bool loop = true;
	string action;
	do {
		cout << "--Restaurant Management System--\n";
		cout << "Type 'login' to login" << endl;
		cout << "Type 'register' to register"<<endl;
		cin >> action;
		if (action == "login") {
			userLogin(password, faculty,fname);
		}
		else if (action == "register") {
			userRegister(password, faculty, fname);
		}
		else {
			cout << "\nInvalid input.\n";
		}

	} while (loop == true);
	system("pause");
	return 0;
}