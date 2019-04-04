#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

struct Address
{
	int street_number;
	string street_name;
	string city;
	string province;
	string postal_code;
	string country;
};
struct PhoneNumber
{
	int country_code;
	int city_code;
	int cell_code;
};
struct Dates
{
	int day;
	int month;
	int year;
};
struct Contact
{
	int contact_id;
	string fname;
	string lname;
	string company_name;
	PhoneNumber phone_number;
	PhoneNumber fax_number;
	Dates meeting_date;
	Address address;
};

//operator overloading cout Contact
ostream & operator << (ostream& out_stream, Contact c);
//operator overloading cout PhoneNumber
ostream & operator << (ostream& out_stream, PhoneNumber phn);
//operator overloading cout Dates
ostream & operator << (ostream& out_stream, Dates da);
//operator overloading cout Address
ostream & operator << (ostream& out_stream, Address ad);
//operator overloading cin PhoneNumber
istream & operator >> (istream& in_stream, PhoneNumber &phn);
//operator overloading cin Dates
istream & operator >> (istream& in_stream, Dates &dates);
//operator overloading cin Address
istream & operator >> (istream& in_stream, Address &ad);
//operator overloading cin Contact
istream & operator >> (istream& in_stream, Contact &c);

// void pre_made_contact_list(); // this is for making pre-made record
void main_display(); // displaying the main menu options
void main_input_validation(int*); // validating the menu choice integers
void switch_for_main_choice(int*); // calling each functions according to the main choice
void create_contacts(); // switch option 1 : create contacts
void display_Contacts(); // switch option 2 : display all contacts (using delegate function)
void display_elements_of_contacts(Contact contact); // delegate function to be called inside display contacts function
void search_Contacts_by_name(vector<Contact>); // switch option 4: find a contact by full name
void search_Contacts_by_id(vector<Contact>); // switch option 3: find a contact by ID
bool sort_id(Contact compare_a, Contact compare_b);
bool sort_name(Contact compare_a, Contact compare_b);
void sort_by_id();
void sort_by_name();


vector<Contact> contact_list; // global struct to contain the list

int main()
{
	int main_choice;
	int *p_choice = &main_choice;
	vector<Contact> *p_contact_list = &contact_list;
	do
	{
		main_display(); // display options for menu 
		//pre_made_contact_list(); //for data in ready

		main_input_validation(p_choice); // validation of menu choice
		switch_for_main_choice(p_choice); // functions according to the choice

	} while (main_choice != 8);
	system("pause");

	return 0;
}

void pre_made_contact_list()
{
	Contact contact;

	for (int i = 0; i < 10; i++)
	{
 		if (i % 2 == 1)
		{
			contact.contact_id = 100 + i;
			contact.fname = "Judy" + to_string(contact.contact_id);
		}
		else
		{
			contact.contact_id = 200 + i;
			contact.fname = "Kong" + to_string(contact.contact_id);
		}
		contact.lname = "Mok";
		contact.company_name = "LaSalle";
		contact.phone_number.country_code = 10;
		contact.phone_number.city_code = 100;
		contact.phone_number.cell_code = 1000000 + i;
		contact.fax_number.country_code = 10;
		contact.fax_number.city_code = 100;
		contact.fax_number.cell_code = 2000000 + i;
		contact.meeting_date.day = 1 + i;
		contact.meeting_date.month = 3;
		contact.meeting_date.year = 2018;
		contact.address.street_number = 1050 + i;
		contact.address.street_name = "Ste. Catherine";
		contact.address.city = "Montreal";
		contact.address.province = "Quebec";
		contact.address.country = "Canada";
		contact.address.postal_code = "H4B 1M1";
		contact_list.push_back(contact);
	}
}
void main_display()
{
	system("cls");

	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
	cout << "-                  Contact Management Application                 -" << endl;
	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
	cout << "-                                                                 -" << endl;
	cout << "-                      Please choose a menu                       -" << endl;
	cout << "-                                                                 -" << endl;
	cout << "-                To CREATE a contact information : 1              -" << endl;
	cout << "-                    To DISPLAY ALL the contacts : 2              -" << endl;
	cout << "-                 To SEARCH for a contacts by ID : 3              -" << endl;
	cout << "-To SEARCH for a contacts by FIRST and LAST NAME : 4              -" << endl;
	cout << "-                     To SORT the contacts by ID : 5              -" << endl;
	cout << "-           To SORT the contacts by company NAME : 6              -" << endl;
	cout << "-                                                                 -" << endl;
	cout << "-                        To Exit the application : 8              -" << endl;
	cout << "-                                                                 -" << endl;
	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
	cout << "Please enter the option : ";

}
void main_input_validation(int* main_choice)
{
	cin >> *main_choice;
	while (!cin || (*main_choice > 8) || (*main_choice < 1))
	{
		cout << "Please enter the correct menu number from above." << endl;
		cin.clear();
		cin.ignore();
		system("pause");
		system("cls");
		main_display();
		cin >> *main_choice;
	}
}
void switch_for_main_choice(int* main_choice)
{
	switch (*main_choice)
	{
	case 1: //create
		create_contacts();
		system("pause");
		break;
	case 2: // display all
		system("cls");
		display_Contacts();
		system("pause");
		break;
	case 3: // search by id
		search_Contacts_by_id(contact_list);
		system("pause");
		break;
	case 4: // search by fname and lname
		search_Contacts_by_name(contact_list);
		system("pause");
		break;
	case 5:
		sort_by_id();
		display_Contacts();
		system("pause");
		break;
	case 6:
		sort_by_name();
		display_Contacts();
		system("pause");
		break;
	case 8:
		break;
	}

	cout << "\n\n\n\n\nEnd Of Testing!" << endl;
}





void create_contacts()
{
	Contact toadd;
	char quit;
	do
	{
		cin >> toadd;
		contact_list.push_back(toadd);
		cout << "To save current list, enter 'q' or 'Q'. To go back to the main menu, enter any other letter." << endl;
		cin >> quit;
	} while (!(quit == 'q') || (quit == 'Q'));
}
void display_Contacts()
{
	for_each(contact_list.begin(), contact_list.end(), display_elements_of_contacts);
}
void display_elements_of_contacts(Contact contact)
{
	cout << contact;
}
void search_Contacts_by_name(vector<Contact> contact_list)
{
	bool found = false;
	string target;
	cout << "Please enter the full name to search : ";
	cin.ignore();
	getline(cin, target);

	for (int i = 0; i < contact_list.size(); i++)
	{
		string full_name = contact_list.at(i).fname + " " + contact_list.at(i).lname;
		if (full_name == target)
		{
			cout << endl << "-     Result     -" << endl;
			cout << contact_list.at(i);
			found = true;
		}
	}
	if (!found)
	{
		cout << "The list does not have the name : " << target << endl;
	}
}
void search_Contacts_by_id(vector<Contact> contact_list)
{
	bool found = false;
	int target;
	cout << "Please enter the ID to search : ";
	cin >> target;

	for (int i = 0; i < contact_list.size(); i++)
	{
		if (contact_list.at(i).contact_id == target)
		{
			cout << endl << "-     Result     -" << endl;
			cout << contact_list.at(i);
			found = true;
		}
	}
	if (!found)
	{
		cout << "The list does not contain the ID : " << target << endl;
	}
}
void sort_by_id()
{
	sort(contact_list.begin(), contact_list.end(), sort_id);
}
void sort_by_name()
{
	sort(contact_list.begin(), contact_list.end(), sort_name);
}
bool sort_id(Contact compare_a, Contact compare_b)
{
	return compare_a.contact_id < compare_b.contact_id;
}
bool sort_name(Contact compare_a, Contact compare_b)
{
	return compare_a.fname.substr(0, 1) < compare_b.fname.substr(0, 1);
}


//operator overloading cout Contact
ostream & operator << (ostream& out_stream, Contact c)
{
	cout << "\n\n-----------------------------------------" << endl;
	cout << "Contact ID                       : " << c.contact_id << endl;
	cout << "Name                             : " << c.fname + " " + c.lname << endl;
	cout << "Company Name                     : " << c.company_name << endl;
	cout << "Phone Number                     : ";
	cout << c.phone_number;
	cout << "Fax Number                       : ";
	cout << c.fax_number;
	cout << "Meeting Date                     : ";
	cout << c.meeting_date;
	cout << "Address                          : ";
	cout << c.address;
	return out_stream;
}
//operator overloading cout PhoneNumber
ostream & operator << (ostream& out_stream, PhoneNumber phn)
{
	cout << "+" << phn.country_code << " - " << phn.city_code << ")" << phn.cell_code << endl;
	return out_stream;
}
//operator overloading cout Dates
ostream & operator << (ostream& out_stream, Dates da)
{
	cout << da.day << "/" << da.month << "/" << da.year << endl;
	return out_stream;
}
//operator overloading cout Address
ostream & operator << (ostream& out_stream, Address ad)
{
	cout << ad.street_number << " " << ad.street_name << " " << ad.city << " " << ad.province << " " << ad.postal_code << " " << ad.country << endl;
	return out_stream;
}
//operator overloading cin PhoneNumber
istream & operator >> (istream& in_stream, PhoneNumber &phn)
{
	cout << "Country Code (2 digits)    : ";
	cin >> phn.country_code;
	while ((phn.country_code < 10) || (phn.country_code > 99))
	{
		cout << "Country Code is not correct. (Contry code is made with 2 numbers - please enter a number betweeb 10 - 99)" << endl;
		cout << "Country Code (2 digits)    : ";
		cin >> phn.country_code;
	}
	cout << "City Code    (3 digits)    : ";
	cin >> phn.city_code;
	while ((phn.city_code < 100) || (phn.city_code > 999))
	{
		cout << "City Code is not correct. (City Code is made with 3 numbers - please enter a number betweeb 100 - 999)" << endl;
		cout << "City Code (3 digits)    : ";
		cin >> phn.city_code;
	}
	cout << "Cell Code    (7 digits)    : ";
	cin >> phn.cell_code;
	while ((phn.cell_code < 1000000) || (phn.cell_code > 9999999))
	{
		cout << "Cell Code is not correct. (Cell code is made with 7 numbers - please enter a number betweeb 1000000 - 9999999)" << endl;
		cout << "Cell Code (7 digits)    : ";
		cin >> phn.city_code;
	}

	return in_stream;
}
//operator overloading cin Dates
istream & operator >> (istream& in_stream, Dates &dates)
{
	cout << "Month (1 - 12)             : ";
	cin >> dates.month;
	while ((dates.month < 1) || (dates.month > 12))
	{
		cout << "Entered number is not suitable for months" << endl;
		cout << "Month (1 - 12)             : ";
		cin >> dates.month;
	}
	cout << "Date (1 - 31)              : ";
	cin >> dates.day;
	while 
		(!((((dates.month == 1) || (dates.month == 3) || (dates.month == 5) ||
		(dates.month == 7) || (dates.month == 8) || (dates.month == 10) || (dates.month == 12)) && 
			(dates.day > 0) && (dates.day < 32)) || (((dates.month == 4) || (dates.month == 6) || 
			(dates.month == 9) || (dates.month == 11)) && (dates.day > 0) &&(dates.day < 31)) || 
			((dates.month == 2) && (dates.day > 0) && (dates.day < 30))))
	{
		cout << "Please enter the day correctly (hint - February does not have 30th day)" << endl;
		cout << "Date (1 - 31)              : ";
		cin >> dates.day;
	}
	cout << "Year (2017 - 2020)         : ";
	cin >> dates.year;
	while ((dates.year < 2017) || (dates.year > 2020))
	{
		cout << "Please enter the year between 2017 and 2020" << endl;
		cout << "Year (2017 - 2020)         : ";
		cin >> dates.year;
	}

	return in_stream;
}
//operator overloading cin Address
istream & operator >> (istream& in_stream, Address &ad)
{
	cout << "Street Number              : ";
	cin >> ad.street_number;
	cout << "Street Name                : ";
	cin.ignore();
	getline(cin, ad.street_name);
	cout << "City                       : ";
	getline(cin, ad.city);
	cout << "Province                   : ";
	getline(cin, ad.province);
	cout << "Postal Code                : ";
	getline(cin, ad.postal_code);
	cout << "Country                    : ";
	getline(cin, ad.country);

	return in_stream;
}
//operator overloading cin Contact
istream & operator >> (istream& in_stream, Contact &c)
{
	cout << "Contact ID                       : ";
	cin >> c.contact_id;
	cout << "First Name                       : ";
	cin.ignore();
	getline(cin, c.fname);
	cout << "Last Name                        : ";
	getline(cin, c.lname);
	cout << "Company Name                     : ";
	getline(cin, c.company_name);
	cout << "Phone number                     : " << endl;
	cin >> c.phone_number;
	cout << "Fax number                       : " << endl;
	cin >> c.fax_number;
	cout << "Meeting Date                     : " << endl;
	cin >> c.meeting_date;
	cout << "Address                          : " << endl;
	cin >> c.address;

	return in_stream;
}


/*
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
-                  Contact Management Application                 -
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
-                                                                 -
-                      Please choose a menu                       -
-                                                                 -
-                To CREATE a contact information : 1              -
-                    To DISPLAY ALL the contacts : 2              -
-                 To SEARCH for a contacts by ID : 3              -
-To SEARCH for a contacts by FIRST and LAST NAME : 4              -
-                     To SORT the contacts by ID : 5              -
-           To SORT the contacts by company NAME : 6              -
-                                                                 -
-                        To Exit the application : 8              -
-                                                                 -
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Please enter the option : 1
Contact ID                       : 1985
First Name                       : Judy Jooyeon
Last Name                        : Mok
Company Name                     : LaSalle
Phone number                     :
Country Code (2 digits)    : 13
City Code    (3 digits)    : 123
Cell Code    (7 digits)    : 1234567
Fax number                       :
Country Code (2 digits)    : 13
City Code    (3 digits)    : 123
Cell Code    (7 digits)    : 1234566
Meeting Date                     :
Month (1 - 12)             : 2
Date (1 - 31)              : 13
Year (2017 - 2020)         : 2019
Address                          :
Street Number              : 1613
Street Name                : Great Taninia
City                       : Somewhere
Province                   : Quebec
Postal Code                : H2G1L7
Country                    : Canada
To save current list, enter 'q' or 'Q'. To go back to the main menu, enter any other letter.
f
Contact ID                       : 21
First Name                       : Jennifer
Last Name                        : Baycroft
Company Name                     : Telus
Phone number                     :
Country Code (2 digits)    : 22
City Code    (3 digits)    : 123
Cell Code    (7 digits)    : 4567897
Fax number                       :
Country Code (2 digits)    : 22
City Code    (3 digits)    : 123
Cell Code    (7 digits)    : 4561231
Meeting Date                     :
Month (1 - 12)             : 8
Date (1 - 31)              : 11
Year (2017 - 2020)         : 2017
Address                          :
Street Number              : 4561
Street Name                : Great Kong
City                       : KongCity
Province                   : Quebec
Postal Code                : H2G1L7
Country                    : Canada
To save current list, enter 'q' or 'Q'. To go back to the main menu, enter any other letter.
d
Contact ID                       : 263
First Name                       : Natalie Kat
Last Name                        : Howe
Company Name                     : TreePlanting
Phone number                     :
Country Code (2 digits)    : 11
City Code    (3 digits)    : 579
Cell Code    (7 digits)    : 1235896
Fax number                       :
Country Code (2 digits)    : 11
City Code    (3 digits)    : 579
Cell Code    (7 digits)    : 2356897
Meeting Date                     :
Month (1 - 12)             : 1
Date (1 - 31)              : 15
Year (2017 - 2020)         : 2020
Address                          :
Street Number              : 7777
Street Name                : Dictorent Dr
City                       : Vancouver
Province                   : British Columbia
Postal Code                : H2G1L7
Country                    : Canada
To save current list, enter 'q' or 'Q'. To go back to the main menu, enter any other letter.
q








-----------------------------------------
Contact ID                       : 200
Name                             : Kong200 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000000
Fax Number                       : +10 - 100)2000000
Meeting Date                     : 1/3/2018
Address                          : 1050 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 101
Name                             : Judy101 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000001
Fax Number                       : +10 - 100)2000001
Meeting Date                     : 2/3/2018
Address                          : 1051 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 202
Name                             : Kong202 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000002
Fax Number                       : +10 - 100)2000002
Meeting Date                     : 3/3/2018
Address                          : 1052 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 103
Name                             : Judy103 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000003
Fax Number                       : +10 - 100)2000003
Meeting Date                     : 4/3/2018
Address                          : 1053 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 204
Name                             : Kong204 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000004
Fax Number                       : +10 - 100)2000004
Meeting Date                     : 5/3/2018
Address                          : 1054 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 105
Name                             : Judy105 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000005
Fax Number                       : +10 - 100)2000005
Meeting Date                     : 6/3/2018
Address                          : 1055 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 206
Name                             : Kong206 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000006
Fax Number                       : +10 - 100)2000006
Meeting Date                     : 7/3/2018
Address                          : 1056 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 107
Name                             : Judy107 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000007
Fax Number                       : +10 - 100)2000007
Meeting Date                     : 8/3/2018
Address                          : 1057 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 208
Name                             : Kong208 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000008
Fax Number                       : +10 - 100)2000008
Meeting Date                     : 9/3/2018
Address                          : 1058 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 109
Name                             : Judy109 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000009
Fax Number                       : +10 - 100)2000009
Meeting Date                     : 10/3/2018
Address                          : 1059 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 1985
Name                             : Judy Jooyeon Mok
Company Name                     : LaSalle
Phone Number                     : +13 - 123)1234567
Fax Number                       : +13 - 123)1234566
Meeting Date                     : 13/2/2019
Address                          : 1613 Great Taninia Somewhere Quebec H2G1L7 Canada


-----------------------------------------
Contact ID                       : 21
Name                             : Jennifer Baycroft
Company Name                     : Telus
Phone Number                     : +22 - 123)4567897
Fax Number                       : +22 - 123)4561231
Meeting Date                     : 11/8/2017
Address                          : 4561 Great Kong KongCity Quebec H2G1L7 Canada


-----------------------------------------
Contact ID                       : 263
Name                             : Natalie Kat Howe
Company Name                     : TreePlanting
Phone Number                     : +11 - 579)1235896
Fax Number                       : +11 - 579)2356897
Meeting Date                     : 15/1/2020
Address                          : 7777 Dictorent Dr Vancouver British Columbia H2G1L7 Canada


-----------------------------------------
Contact ID                       : 200
Name                             : Kong200 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000000
Fax Number                       : +10 - 100)2000000
Meeting Date                     : 1/3/2018
Address                          : 1050 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 101
Name                             : Judy101 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000001
Fax Number                       : +10 - 100)2000001
Meeting Date                     : 2/3/2018
Address                          : 1051 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 202
Name                             : Kong202 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000002
Fax Number                       : +10 - 100)2000002
Meeting Date                     : 3/3/2018
Address                          : 1052 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 103
Name                             : Judy103 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000003
Fax Number                       : +10 - 100)2000003
Meeting Date                     : 4/3/2018
Address                          : 1053 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 204
Name                             : Kong204 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000004
Fax Number                       : +10 - 100)2000004
Meeting Date                     : 5/3/2018
Address                          : 1054 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 105
Name                             : Judy105 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000005
Fax Number                       : +10 - 100)2000005
Meeting Date                     : 6/3/2018
Address                          : 1055 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 206
Name                             : Kong206 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000006
Fax Number                       : +10 - 100)2000006
Meeting Date                     : 7/3/2018
Address                          : 1056 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 107
Name                             : Judy107 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000007
Fax Number                       : +10 - 100)2000007
Meeting Date                     : 8/3/2018
Address                          : 1057 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 208
Name                             : Kong208 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000008
Fax Number                       : +10 - 100)2000008
Meeting Date                     : 9/3/2018
Address                          : 1058 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 109
Name                             : Judy109 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000009
Fax Number                       : +10 - 100)2000009
Meeting Date                     : 10/3/2018
Address                          : 1059 Ste. Catherine Montreal Quebec H4B 1M1 Canada
Press any key to continue . . .






-                  Contact Management Application                 -
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
-                                                                 -
-                      Please choose a menu                       -
-                                                                 -
-                To CREATE a contact information : 1              -
-                    To DISPLAY ALL the contacts : 2              -
-                 To SEARCH for a contacts by ID : 3              -
-To SEARCH for a contacts by FIRST and LAST NAME : 4              -
-                     To SORT the contacts by ID : 5              -
-           To SORT the contacts by company NAME : 6              -
-                                                                 -
-                        To Exit the application : 8              -
-                                                                 -
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Please enter the option : 3
Please enter the ID to search : 263

-     Result     -


-----------------------------------------
Contact ID                       : 263
Name                             : Natalie Kat Howe
Company Name                     : TreePlanting
Phone Number                     : +11 - 579)1235896
Fax Number                       : +11 - 579)2356897
Meeting Date                     : 15/1/2020
Address                          : 7777 Dictorent Dr Vancouver British Columbia H2G1L7 Canada







- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
-                  Contact Management Application                 -
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
-                                                                 -
-                      Please choose a menu                       -
-                                                                 -
-                To CREATE a contact information : 1              -
-                    To DISPLAY ALL the contacts : 2              -
-                 To SEARCH for a contacts by ID : 3              -
-To SEARCH for a contacts by FIRST and LAST NAME : 4              -
-                     To SORT the contacts by ID : 5              -
-           To SORT the contacts by company NAME : 6              -
-                                                                 -
-                        To Exit the application : 8              -
-                                                                 -
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Please enter the option : 4
Please enter the full name to search : Jennifer Baycroft

-     Result     -


-----------------------------------------
Contact ID                       : 21
Name                             : Jennifer Baycroft
Company Name                     : Telus
Phone Number                     : +22 - 123)4567897
Fax Number                       : +22 - 123)4561231
Meeting Date                     : 11/8/2017
Address                          : 4561 Great Kong KongCity Quebec H2G1L7 Canada
Press any key to continue . . .






- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
-                  Contact Management Application                 -
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
-                                                                 -
-                      Please choose a menu                       -
-                                                                 -
-                To CREATE a contact information : 1              -
-                    To DISPLAY ALL the contacts : 2              -
-                 To SEARCH for a contacts by ID : 3              -
-To SEARCH for a contacts by FIRST and LAST NAME : 4              -
-                     To SORT the contacts by ID : 5              -
-           To SORT the contacts by company NAME : 6              -
-                                                                 -
-                        To Exit the application : 8              -
-                                                                 -
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Please enter the option : 5


-----------------------------------------
Contact ID                       : 21
Name                             : Jennifer Baycroft
Company Name                     : Telus
Phone Number                     : +22 - 123)4567897
Fax Number                       : +22 - 123)4561231
Meeting Date                     : 11/8/2017
Address                          : 4561 Great Kong KongCity Quebec H2G1L7 Canada


-----------------------------------------
Contact ID                       : 101
Name                             : Judy101 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000001
Fax Number                       : +10 - 100)2000001
Meeting Date                     : 2/3/2018
Address                          : 1051 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 101
Name                             : Judy101 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000001
Fax Number                       : +10 - 100)2000001
Meeting Date                     : 2/3/2018
Address                          : 1051 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 101
Name                             : Judy101 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000001
Fax Number                       : +10 - 100)2000001
Meeting Date                     : 2/3/2018
Address                          : 1051 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 101
Name                             : Judy101 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000001
Fax Number                       : +10 - 100)2000001
Meeting Date                     : 2/3/2018
Address                          : 1051 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 101
Name                             : Judy101 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000001
Fax Number                       : +10 - 100)2000001
Meeting Date                     : 2/3/2018
Address                          : 1051 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 101
Name                             : Judy101 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000001
Fax Number                       : +10 - 100)2000001
Meeting Date                     : 2/3/2018
Address                          : 1051 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 101
Name                             : Judy101 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000001
Fax Number                       : +10 - 100)2000001
Meeting Date                     : 2/3/2018
Address                          : 1051 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 103
Name                             : Judy103 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000003
Fax Number                       : +10 - 100)2000003
Meeting Date                     : 4/3/2018
Address                          : 1053 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 103
Name                             : Judy103 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000003
Fax Number                       : +10 - 100)2000003
Meeting Date                     : 4/3/2018
Address                          : 1053 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 103
Name                             : Judy103 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000003
Fax Number                       : +10 - 100)2000003
Meeting Date                     : 4/3/2018
Address                          : 1053 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 103
Name                             : Judy103 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000003
Fax Number                       : +10 - 100)2000003
Meeting Date                     : 4/3/2018
Address                          : 1053 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 103
Name                             : Judy103 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000003
Fax Number                       : +10 - 100)2000003
Meeting Date                     : 4/3/2018
Address                          : 1053 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 103
Name                             : Judy103 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000003
Fax Number                       : +10 - 100)2000003
Meeting Date                     : 4/3/2018
Address                          : 1053 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 103
Name                             : Judy103 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000003
Fax Number                       : +10 - 100)2000003
Meeting Date                     : 4/3/2018
Address                          : 1053 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 105
Name                             : Judy105 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000005
Fax Number                       : +10 - 100)2000005
Meeting Date                     : 6/3/2018
Address                          : 1055 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 105
Name                             : Judy105 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000005
Fax Number                       : +10 - 100)2000005
Meeting Date                     : 6/3/2018
Address                          : 1055 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 105
Name                             : Judy105 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000005
Fax Number                       : +10 - 100)2000005
Meeting Date                     : 6/3/2018
Address                          : 1055 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 105
Name                             : Judy105 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000005
Fax Number                       : +10 - 100)2000005
Meeting Date                     : 6/3/2018
Address                          : 1055 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 105
Name                             : Judy105 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000005
Fax Number                       : +10 - 100)2000005
Meeting Date                     : 6/3/2018
Address                          : 1055 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 105
Name                             : Judy105 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000005
Fax Number                       : +10 - 100)2000005
Meeting Date                     : 6/3/2018
Address                          : 1055 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 105
Name                             : Judy105 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000005
Fax Number                       : +10 - 100)2000005
Meeting Date                     : 6/3/2018
Address                          : 1055 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 107
Name                             : Judy107 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000007
Fax Number                       : +10 - 100)2000007
Meeting Date                     : 8/3/2018
Address                          : 1057 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 107
Name                             : Judy107 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000007
Fax Number                       : +10 - 100)2000007
Meeting Date                     : 8/3/2018
Address                          : 1057 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 107
Name                             : Judy107 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000007
Fax Number                       : +10 - 100)2000007
Meeting Date                     : 8/3/2018
Address                          : 1057 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 107
Name                             : Judy107 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000007
Fax Number                       : +10 - 100)2000007
Meeting Date                     : 8/3/2018
Address                          : 1057 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 107
Name                             : Judy107 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000007
Fax Number                       : +10 - 100)2000007
Meeting Date                     : 8/3/2018
Address                          : 1057 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 107
Name                             : Judy107 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000007
Fax Number                       : +10 - 100)2000007
Meeting Date                     : 8/3/2018
Address                          : 1057 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 107
Name                             : Judy107 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000007
Fax Number                       : +10 - 100)2000007
Meeting Date                     : 8/3/2018
Address                          : 1057 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 109
Name                             : Judy109 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000009
Fax Number                       : +10 - 100)2000009
Meeting Date                     : 10/3/2018
Address                          : 1059 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 109
Name                             : Judy109 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000009
Fax Number                       : +10 - 100)2000009
Meeting Date                     : 10/3/2018
Address                          : 1059 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 109
Name                             : Judy109 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000009
Fax Number                       : +10 - 100)2000009
Meeting Date                     : 10/3/2018
Address                          : 1059 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 109
Name                             : Judy109 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000009
Fax Number                       : +10 - 100)2000009
Meeting Date                     : 10/3/2018
Address                          : 1059 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 109
Name                             : Judy109 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000009
Fax Number                       : +10 - 100)2000009
Meeting Date                     : 10/3/2018
Address                          : 1059 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 109
Name                             : Judy109 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000009
Fax Number                       : +10 - 100)2000009
Meeting Date                     : 10/3/2018
Address                          : 1059 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 109
Name                             : Judy109 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000009
Fax Number                       : +10 - 100)2000009
Meeting Date                     : 10/3/2018
Address                          : 1059 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 200
Name                             : Kong200 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000000
Fax Number                       : +10 - 100)2000000
Meeting Date                     : 1/3/2018
Address                          : 1050 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 200
Name                             : Kong200 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000000
Fax Number                       : +10 - 100)2000000
Meeting Date                     : 1/3/2018
Address                          : 1050 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 200
Name                             : Kong200 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000000
Fax Number                       : +10 - 100)2000000
Meeting Date                     : 1/3/2018
Address                          : 1050 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 200
Name                             : Kong200 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000000
Fax Number                       : +10 - 100)2000000
Meeting Date                     : 1/3/2018
Address                          : 1050 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 200
Name                             : Kong200 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000000
Fax Number                       : +10 - 100)2000000
Meeting Date                     : 1/3/2018
Address                          : 1050 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 200
Name                             : Kong200 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000000
Fax Number                       : +10 - 100)2000000
Meeting Date                     : 1/3/2018
Address                          : 1050 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 200
Name                             : Kong200 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000000
Fax Number                       : +10 - 100)2000000
Meeting Date                     : 1/3/2018
Address                          : 1050 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 202
Name                             : Kong202 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000002
Fax Number                       : +10 - 100)2000002
Meeting Date                     : 3/3/2018
Address                          : 1052 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 202
Name                             : Kong202 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000002
Fax Number                       : +10 - 100)2000002
Meeting Date                     : 3/3/2018
Address                          : 1052 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 202
Name                             : Kong202 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000002
Fax Number                       : +10 - 100)2000002
Meeting Date                     : 3/3/2018
Address                          : 1052 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 202
Name                             : Kong202 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000002
Fax Number                       : +10 - 100)2000002
Meeting Date                     : 3/3/2018
Address                          : 1052 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 202
Name                             : Kong202 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000002
Fax Number                       : +10 - 100)2000002
Meeting Date                     : 3/3/2018
Address                          : 1052 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 202
Name                             : Kong202 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000002
Fax Number                       : +10 - 100)2000002
Meeting Date                     : 3/3/2018
Address                          : 1052 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 202
Name                             : Kong202 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000002
Fax Number                       : +10 - 100)2000002
Meeting Date                     : 3/3/2018
Address                          : 1052 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 204
Name                             : Kong204 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000004
Fax Number                       : +10 - 100)2000004
Meeting Date                     : 5/3/2018
Address                          : 1054 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 204
Name                             : Kong204 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000004
Fax Number                       : +10 - 100)2000004
Meeting Date                     : 5/3/2018
Address                          : 1054 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 204
Name                             : Kong204 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000004
Fax Number                       : +10 - 100)2000004
Meeting Date                     : 5/3/2018
Address                          : 1054 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 204
Name                             : Kong204 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000004
Fax Number                       : +10 - 100)2000004
Meeting Date                     : 5/3/2018
Address                          : 1054 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 204
Name                             : Kong204 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000004
Fax Number                       : +10 - 100)2000004
Meeting Date                     : 5/3/2018
Address                          : 1054 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 204
Name                             : Kong204 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000004
Fax Number                       : +10 - 100)2000004
Meeting Date                     : 5/3/2018
Address                          : 1054 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 204
Name                             : Kong204 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000004
Fax Number                       : +10 - 100)2000004
Meeting Date                     : 5/3/2018
Address                          : 1054 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 206
Name                             : Kong206 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000006
Fax Number                       : +10 - 100)2000006
Meeting Date                     : 7/3/2018
Address                          : 1056 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 206
Name                             : Kong206 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000006
Fax Number                       : +10 - 100)2000006
Meeting Date                     : 7/3/2018
Address                          : 1056 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 206
Name                             : Kong206 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000006
Fax Number                       : +10 - 100)2000006
Meeting Date                     : 7/3/2018
Address                          : 1056 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 206
Name                             : Kong206 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000006
Fax Number                       : +10 - 100)2000006
Meeting Date                     : 7/3/2018
Address                          : 1056 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 206
Name                             : Kong206 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000006
Fax Number                       : +10 - 100)2000006
Meeting Date                     : 7/3/2018
Address                          : 1056 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 206
Name                             : Kong206 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000006
Fax Number                       : +10 - 100)2000006
Meeting Date                     : 7/3/2018
Address                          : 1056 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 206
Name                             : Kong206 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000006
Fax Number                       : +10 - 100)2000006
Meeting Date                     : 7/3/2018
Address                          : 1056 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 208
Name                             : Kong208 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000008
Fax Number                       : +10 - 100)2000008
Meeting Date                     : 9/3/2018
Address                          : 1058 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 208
Name                             : Kong208 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000008
Fax Number                       : +10 - 100)2000008
Meeting Date                     : 9/3/2018
Address                          : 1058 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 208
Name                             : Kong208 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000008
Fax Number                       : +10 - 100)2000008
Meeting Date                     : 9/3/2018
Address                          : 1058 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 208
Name                             : Kong208 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000008
Fax Number                       : +10 - 100)2000008
Meeting Date                     : 9/3/2018
Address                          : 1058 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 208
Name                             : Kong208 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000008
Fax Number                       : +10 - 100)2000008
Meeting Date                     : 9/3/2018
Address                          : 1058 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 208
Name                             : Kong208 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000008
Fax Number                       : +10 - 100)2000008
Meeting Date                     : 9/3/2018
Address                          : 1058 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 208
Name                             : Kong208 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000008
Fax Number                       : +10 - 100)2000008
Meeting Date                     : 9/3/2018
Address                          : 1058 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 263
Name                             : Natalie Kat Howe
Company Name                     : TreePlanting
Phone Number                     : +11 - 579)1235896
Fax Number                       : +11 - 579)2356897
Meeting Date                     : 15/1/2020
Address                          : 7777 Dictorent Dr Vancouver British Columbia H2G1L7 Canada


-----------------------------------------
Contact ID                       : 1985
Name                             : Judy Jooyeon Mok
Company Name                     : LaSalle
Phone Number                     : +13 - 123)1234567
Fax Number                       : +13 - 123)1234566
Meeting Date                     : 13/2/2019
Address                          : 1613 Great Taninia Somewhere Quebec H2G1L7 Canada
Press any key to continue . . .




- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
-                  Contact Management Application                 -
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
-                                                                 -
-                      Please choose a menu                       -
-                                                                 -
-                To CREATE a contact information : 1              -
-                    To DISPLAY ALL the contacts : 2              -
-                 To SEARCH for a contacts by ID : 3              -
-To SEARCH for a contacts by FIRST and LAST NAME : 4              -
-                     To SORT the contacts by ID : 5              -
-           To SORT the contacts by company NAME : 6              -
-                                                                 -
-                        To Exit the application : 8              -
-                                                                 -
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Please enter the option : 6


-----------------------------------------
Contact ID                       : 21
Name                             : Jennifer Baycroft
Company Name                     : Telus
Phone Number                     : +22 - 123)4567897
Fax Number                       : +22 - 123)4561231
Meeting Date                     : 11/8/2017
Address                          : 4561 Great Kong KongCity Quebec H2G1L7 Canada


-----------------------------------------
Contact ID                       : 101
Name                             : Judy101 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000001
Fax Number                       : +10 - 100)2000001
Meeting Date                     : 2/3/2018
Address                          : 1051 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 101
Name                             : Judy101 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000001
Fax Number                       : +10 - 100)2000001
Meeting Date                     : 2/3/2018
Address                          : 1051 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 101
Name                             : Judy101 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000001
Fax Number                       : +10 - 100)2000001
Meeting Date                     : 2/3/2018
Address                          : 1051 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 101
Name                             : Judy101 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000001
Fax Number                       : +10 - 100)2000001
Meeting Date                     : 2/3/2018
Address                          : 1051 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 101
Name                             : Judy101 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000001
Fax Number                       : +10 - 100)2000001
Meeting Date                     : 2/3/2018
Address                          : 1051 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 101
Name                             : Judy101 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000001
Fax Number                       : +10 - 100)2000001
Meeting Date                     : 2/3/2018
Address                          : 1051 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 101
Name                             : Judy101 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000001
Fax Number                       : +10 - 100)2000001
Meeting Date                     : 2/3/2018
Address                          : 1051 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 103
Name                             : Judy103 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000003
Fax Number                       : +10 - 100)2000003
Meeting Date                     : 4/3/2018
Address                          : 1053 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 103
Name                             : Judy103 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000003
Fax Number                       : +10 - 100)2000003
Meeting Date                     : 4/3/2018
Address                          : 1053 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 103
Name                             : Judy103 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000003
Fax Number                       : +10 - 100)2000003
Meeting Date                     : 4/3/2018
Address                          : 1053 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 103
Name                             : Judy103 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000003
Fax Number                       : +10 - 100)2000003
Meeting Date                     : 4/3/2018
Address                          : 1053 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 103
Name                             : Judy103 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000003
Fax Number                       : +10 - 100)2000003
Meeting Date                     : 4/3/2018
Address                          : 1053 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 103
Name                             : Judy103 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000003
Fax Number                       : +10 - 100)2000003
Meeting Date                     : 4/3/2018
Address                          : 1053 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 103
Name                             : Judy103 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000003
Fax Number                       : +10 - 100)2000003
Meeting Date                     : 4/3/2018
Address                          : 1053 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 105
Name                             : Judy105 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000005
Fax Number                       : +10 - 100)2000005
Meeting Date                     : 6/3/2018
Address                          : 1055 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 105
Name                             : Judy105 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000005
Fax Number                       : +10 - 100)2000005
Meeting Date                     : 6/3/2018
Address                          : 1055 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 105
Name                             : Judy105 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000005
Fax Number                       : +10 - 100)2000005
Meeting Date                     : 6/3/2018
Address                          : 1055 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 105
Name                             : Judy105 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000005
Fax Number                       : +10 - 100)2000005
Meeting Date                     : 6/3/2018
Address                          : 1055 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 105
Name                             : Judy105 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000005
Fax Number                       : +10 - 100)2000005
Meeting Date                     : 6/3/2018
Address                          : 1055 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 105
Name                             : Judy105 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000005
Fax Number                       : +10 - 100)2000005
Meeting Date                     : 6/3/2018
Address                          : 1055 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 105
Name                             : Judy105 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000005
Fax Number                       : +10 - 100)2000005
Meeting Date                     : 6/3/2018
Address                          : 1055 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 107
Name                             : Judy107 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000007
Fax Number                       : +10 - 100)2000007
Meeting Date                     : 8/3/2018
Address                          : 1057 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 107
Name                             : Judy107 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000007
Fax Number                       : +10 - 100)2000007
Meeting Date                     : 8/3/2018
Address                          : 1057 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 107
Name                             : Judy107 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000007
Fax Number                       : +10 - 100)2000007
Meeting Date                     : 8/3/2018
Address                          : 1057 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 107
Name                             : Judy107 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000007
Fax Number                       : +10 - 100)2000007
Meeting Date                     : 8/3/2018
Address                          : 1057 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 107
Name                             : Judy107 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000007
Fax Number                       : +10 - 100)2000007
Meeting Date                     : 8/3/2018
Address                          : 1057 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 107
Name                             : Judy107 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000007
Fax Number                       : +10 - 100)2000007
Meeting Date                     : 8/3/2018
Address                          : 1057 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 107
Name                             : Judy107 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000007
Fax Number                       : +10 - 100)2000007
Meeting Date                     : 8/3/2018
Address                          : 1057 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 109
Name                             : Judy109 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000009
Fax Number                       : +10 - 100)2000009
Meeting Date                     : 10/3/2018
Address                          : 1059 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 109
Name                             : Judy109 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000009
Fax Number                       : +10 - 100)2000009
Meeting Date                     : 10/3/2018
Address                          : 1059 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 109
Name                             : Judy109 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000009
Fax Number                       : +10 - 100)2000009
Meeting Date                     : 10/3/2018
Address                          : 1059 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 109
Name                             : Judy109 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000009
Fax Number                       : +10 - 100)2000009
Meeting Date                     : 10/3/2018
Address                          : 1059 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 109
Name                             : Judy109 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000009
Fax Number                       : +10 - 100)2000009
Meeting Date                     : 10/3/2018
Address                          : 1059 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 109
Name                             : Judy109 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000009
Fax Number                       : +10 - 100)2000009
Meeting Date                     : 10/3/2018
Address                          : 1059 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 109
Name                             : Judy109 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000009
Fax Number                       : +10 - 100)2000009
Meeting Date                     : 10/3/2018
Address                          : 1059 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 1985
Name                             : Judy Jooyeon Mok
Company Name                     : LaSalle
Phone Number                     : +13 - 123)1234567
Fax Number                       : +13 - 123)1234566
Meeting Date                     : 13/2/2019
Address                          : 1613 Great Taninia Somewhere Quebec H2G1L7 Canada


-----------------------------------------
Contact ID                       : 101
Name                             : Judy101 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000001
Fax Number                       : +10 - 100)2000001
Meeting Date                     : 2/3/2018
Address                          : 1051 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 103
Name                             : Judy103 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000003
Fax Number                       : +10 - 100)2000003
Meeting Date                     : 4/3/2018
Address                          : 1053 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 105
Name                             : Judy105 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000005
Fax Number                       : +10 - 100)2000005
Meeting Date                     : 6/3/2018
Address                          : 1055 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 107
Name                             : Judy107 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000007
Fax Number                       : +10 - 100)2000007
Meeting Date                     : 8/3/2018
Address                          : 1057 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 109
Name                             : Judy109 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000009
Fax Number                       : +10 - 100)2000009
Meeting Date                     : 10/3/2018
Address                          : 1059 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 200
Name                             : Kong200 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000000
Fax Number                       : +10 - 100)2000000
Meeting Date                     : 1/3/2018
Address                          : 1050 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 200
Name                             : Kong200 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000000
Fax Number                       : +10 - 100)2000000
Meeting Date                     : 1/3/2018
Address                          : 1050 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 200
Name                             : Kong200 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000000
Fax Number                       : +10 - 100)2000000
Meeting Date                     : 1/3/2018
Address                          : 1050 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 200
Name                             : Kong200 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000000
Fax Number                       : +10 - 100)2000000
Meeting Date                     : 1/3/2018
Address                          : 1050 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 200
Name                             : Kong200 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000000
Fax Number                       : +10 - 100)2000000
Meeting Date                     : 1/3/2018
Address                          : 1050 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 202
Name                             : Kong202 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000002
Fax Number                       : +10 - 100)2000002
Meeting Date                     : 3/3/2018
Address                          : 1052 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 202
Name                             : Kong202 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000002
Fax Number                       : +10 - 100)2000002
Meeting Date                     : 3/3/2018
Address                          : 1052 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 202
Name                             : Kong202 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000002
Fax Number                       : +10 - 100)2000002
Meeting Date                     : 3/3/2018
Address                          : 1052 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 204
Name                             : Kong204 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000004
Fax Number                       : +10 - 100)2000004
Meeting Date                     : 5/3/2018
Address                          : 1054 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 204
Name                             : Kong204 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000004
Fax Number                       : +10 - 100)2000004
Meeting Date                     : 5/3/2018
Address                          : 1054 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 204
Name                             : Kong204 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000004
Fax Number                       : +10 - 100)2000004
Meeting Date                     : 5/3/2018
Address                          : 1054 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 204
Name                             : Kong204 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000004
Fax Number                       : +10 - 100)2000004
Meeting Date                     : 5/3/2018
Address                          : 1054 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 204
Name                             : Kong204 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000004
Fax Number                       : +10 - 100)2000004
Meeting Date                     : 5/3/2018
Address                          : 1054 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 204
Name                             : Kong204 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000004
Fax Number                       : +10 - 100)2000004
Meeting Date                     : 5/3/2018
Address                          : 1054 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 204
Name                             : Kong204 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000004
Fax Number                       : +10 - 100)2000004
Meeting Date                     : 5/3/2018
Address                          : 1054 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 206
Name                             : Kong206 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000006
Fax Number                       : +10 - 100)2000006
Meeting Date                     : 7/3/2018
Address                          : 1056 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 206
Name                             : Kong206 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000006
Fax Number                       : +10 - 100)2000006
Meeting Date                     : 7/3/2018
Address                          : 1056 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 206
Name                             : Kong206 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000006
Fax Number                       : +10 - 100)2000006
Meeting Date                     : 7/3/2018
Address                          : 1056 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 206
Name                             : Kong206 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000006
Fax Number                       : +10 - 100)2000006
Meeting Date                     : 7/3/2018
Address                          : 1056 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 206
Name                             : Kong206 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000006
Fax Number                       : +10 - 100)2000006
Meeting Date                     : 7/3/2018
Address                          : 1056 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 200
Name                             : Kong200 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000000
Fax Number                       : +10 - 100)2000000
Meeting Date                     : 1/3/2018
Address                          : 1050 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 206
Name                             : Kong206 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000006
Fax Number                       : +10 - 100)2000006
Meeting Date                     : 7/3/2018
Address                          : 1056 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 208
Name                             : Kong208 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000008
Fax Number                       : +10 - 100)2000008
Meeting Date                     : 9/3/2018
Address                          : 1058 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 208
Name                             : Kong208 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000008
Fax Number                       : +10 - 100)2000008
Meeting Date                     : 9/3/2018
Address                          : 1058 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 208
Name                             : Kong208 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000008
Fax Number                       : +10 - 100)2000008
Meeting Date                     : 9/3/2018
Address                          : 1058 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 208
Name                             : Kong208 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000008
Fax Number                       : +10 - 100)2000008
Meeting Date                     : 9/3/2018
Address                          : 1058 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 208
Name                             : Kong208 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000008
Fax Number                       : +10 - 100)2000008
Meeting Date                     : 9/3/2018
Address                          : 1058 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 208
Name                             : Kong208 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000008
Fax Number                       : +10 - 100)2000008
Meeting Date                     : 9/3/2018
Address                          : 1058 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 208
Name                             : Kong208 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000008
Fax Number                       : +10 - 100)2000008
Meeting Date                     : 9/3/2018
Address                          : 1058 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 200
Name                             : Kong200 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000000
Fax Number                       : +10 - 100)2000000
Meeting Date                     : 1/3/2018
Address                          : 1050 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 200
Name                             : Kong200 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000000
Fax Number                       : +10 - 100)2000000
Meeting Date                     : 1/3/2018
Address                          : 1050 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 202
Name                             : Kong202 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000002
Fax Number                       : +10 - 100)2000002
Meeting Date                     : 3/3/2018
Address                          : 1052 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 202
Name                             : Kong202 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000002
Fax Number                       : +10 - 100)2000002
Meeting Date                     : 3/3/2018
Address                          : 1052 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 202
Name                             : Kong202 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000002
Fax Number                       : +10 - 100)2000002
Meeting Date                     : 3/3/2018
Address                          : 1052 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 204
Name                             : Kong204 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000004
Fax Number                       : +10 - 100)2000004
Meeting Date                     : 5/3/2018
Address                          : 1054 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 202
Name                             : Kong202 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000002
Fax Number                       : +10 - 100)2000002
Meeting Date                     : 3/3/2018
Address                          : 1052 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 206
Name                             : Kong206 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000006
Fax Number                       : +10 - 100)2000006
Meeting Date                     : 7/3/2018
Address                          : 1056 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 202
Name                             : Kong202 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000002
Fax Number                       : +10 - 100)2000002
Meeting Date                     : 3/3/2018
Address                          : 1052 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 208
Name                             : Kong208 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000008
Fax Number                       : +10 - 100)2000008
Meeting Date                     : 9/3/2018
Address                          : 1058 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 206
Name                             : Kong206 Mok
Company Name                     : LaSalle
Phone Number                     : +10 - 100)1000006
Fax Number                       : +10 - 100)2000006
Meeting Date                     : 7/3/2018
Address                          : 1056 Ste. Catherine Montreal Quebec H4B 1M1 Canada


-----------------------------------------
Contact ID                       : 263
Name                             : Natalie Kat Howe
Company Name                     : TreePlanting
Phone Number                     : +11 - 579)1235896
Fax Number                       : +11 - 579)2356897
Meeting Date                     : 15/1/2020
Address                          : 7777 Dictorent Dr Vancouver British Columbia H2G1L7 Canada
Press any key to continue . . .


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
-                  Contact Management Application                 -
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
-                                                                 -
-                      Please choose a menu                       -
-                                                                 -
-                To CREATE a contact information : 1              -
-                    To DISPLAY ALL the contacts : 2              -
-                 To SEARCH for a contacts by ID : 3              -
-To SEARCH for a contacts by FIRST and LAST NAME : 4              -
-                     To SORT the contacts by ID : 5              -
-           To SORT the contacts by company NAME : 6              -
-                                                                 -
-                        To Exit the application : 8              -
-                                                                 -
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Please enter the option : 8





End Of Testing!
Press any key to continue . . .

*/