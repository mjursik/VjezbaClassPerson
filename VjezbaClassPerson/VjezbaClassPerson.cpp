#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <math.h>
#include <ctype.h>
#include <regex>
#include <map>

using namespace std;

struct Address
{
	string place;
	string street;
	string houseNumber;
};

struct Tax
{
	string ispostava;
	bool obveznikFiskalizacije;
	Address poreznoNadleznaAdresa;
};

struct date
{
	int year;
	int month;
	int day;
};

#pragma region BaseClass
class Person
{
public:
	string oib;
	string firstName;
	string lastName;
	string email;
	date birthDate;

	string getFullName();
	void setAddress(string place, string street, string houseNumber);
	string getAddress();
	bool isOibValid(string oib);
	bool isEmailValid(const string &email);
private:

protected:
	Address address;
};

string Person::getFullName()
{
	return this->firstName + " " + this->lastName;
};

void Person::setAddress(string place, string street, string houseNumber)
{
	this->address.place = place;
	this->address.street = street;
	this->address.houseNumber = houseNumber;
};

string Person::getAddress()
{
	stringstream ss;
	ss << this->address.place << ", " << this->address.street << " " << this->address.houseNumber;
	return ss.str();
};

bool Person::isOibValid(string oib)
{
	if (oib.length() != 11) {
		return false;
	}
	int n[11];
	for (int i = 0; i<oib.length(); i++)
	{
		if (isdigit(oib[i]))
		{
			n[i] = static_cast<int>(oib[i]) - 48;
		}
		else
		{
			return false;
		}
	}
	int kontrolniBroj = n[10];

	double temp = 10;

	for (size_t i = 0; i < 10; i++)
	{
		temp = fmod((n[i] + temp), 10);
		if (temp == 0) temp = 10;
		temp = (temp * 2) / 11;
		int intPart = floor(temp);
		int decPart = floor((temp - intPart) * 10);
		if (intPart == 0) intPart = 1;
		temp = intPart + decPart;
	}

	double check = 0;
	if (temp == 1)
	{
		check = 0;
	}
	else
	{
		check = 11 - temp;
	}

	if (check == kontrolniBroj)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Person::isEmailValid(const string &email)
{
	const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

	return regex_match(email, pattern);
}

#pragma endregion

#pragma region Student
class Student : public Person
{
public:
	int studentId;

private:

protected:
};
#pragma endregion

#pragma region TaxPayer
class TaxPayer : public Person
{
public:
	Tax tax;
};
#pragma endregion


int main()
{
	char next = 'y';
	map<string, Person> prsn;

	do
	{
		system("cls");

		Person me;

		cout << "Unesite OIB: ";

		string oib;

		do
		{
			cin >> oib;

			if (me.isOibValid(oib))
			{
				me.oib = oib;
			}
			else
			{
				cout << "Unesite ispravan OIB. Pokusajte ponovo." << endl;
				cout << "Unesite OIB: ";
			}
		} while (!me.isOibValid(oib));

		cout << "Unesite ime: ";
		cin >> me.firstName;

		cout << "Unesite prezime: ";
		cin >> me.lastName;

		string email;

		cout << "Unesite email: ";

		do
		{
			cin >> email;

			if (me.isEmailValid(email))
			{
				me.email = email;
			}
			else
			{
				cout << "Unesite ispravnu email adresu. Pokusajte ponovo." << endl;
				cout << "Unesite email: ";
			}
		} while (!me.isEmailValid(email));

		prsn[oib] = me;

		cout << "Unesi novi zapis? (y/n)";
		cin >> next;

	} while (next == 'y');

	system("cls");

	for (auto it : prsn)
	{
		cout << endl << "PERSON" << endl << endl;
		cout << "OIB: " << it.second.oib << endl;
		cout << "Fullname: " << it.second.getFullName() << endl;
		cout << "Email: " << it.second.email << endl;
		cout << "Adress: " << it.second.getAddress() << endl << endl;
	}

	system("pause");

	return 0;
}