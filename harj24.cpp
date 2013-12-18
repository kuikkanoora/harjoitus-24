/*************************************************************************************************************************************************************
*Tehtävä: Harjoitus24
*Tekijä: Noora Kuikka
*PVM: 9.12.2013
*Kuvaus:
*Harjoitus 24 (Palautus vko 50)
*Muuta harjoitusta 22 niin, etta valikko nayttaa seuraavalta:
*
*VALIKKO
*0 Lopeta
*1 Lisaa henkilo
*2 Nayta henkilo
*3 Nayta kaikki henkilot
*4 Poista henkilon tiedot
*5 Tallenna tiedot tiedostoon
*6 Hae tiedot tiedostosta
*
*
*ja toteuta valikossa näkyvät toiminnot.
*
*Valitse haluamasi tallennusformaatti.
*Versio 1.0 H4719 9.12.2013
**************************************************************************************************************************************************************/

#include <iostream>
#include <fstream>
using namespace std;

struct PEOPLE
{
	char name[20];
	double journey;
	int size;
};

const int MAX_ARRAY = 10;

int Menu(void);
void PrintAll(PEOPLE per[], int num);
void AddPerson(PEOPLE [], int *num);
void PrintPerson(PEOPLE num[]);
void RemovePerson(PEOPLE per[], int *per_num);
void SaveToFile(PEOPLE per[], int num);
void SearchFile(PEOPLE [], int *num);

int main()
{
	int choice = 0;
	int num = 0;
	bool cont = true;
	PEOPLE per[MAX_ARRAY];

	do
	{
		cout << "\nThe number of people in the register: " << num << endl;
		cout << "Max. 10." << endl;
		choice = Menu();
		cout << endl;

		switch (choice)
		{
		case 0:
			{
				cout << "\nExiting program...\n";
				cont = false;
				break;
			}
		case 1:
			{
			    if(num < 10)
				{
					AddPerson(per, &num);
				}
                else
				{
					cout << "You have reached the maximum amount of people this register can store." << endl;
				}
				break;
			}
		case 2:
			{
				PrintPerson(per);
				break;
			}
		case 3:
			{
				PrintAll(per, num);
				break;
			}
		case 4:
			{
				RemovePerson(per, &num);
				break;
			}
		case 5:
			{
				SaveToFile(per, num);
				break;
			}
		case 6:
			{
				SearchFile(per, &num);
				break;
			}
		default:
			{
				cout << "\nIncorrect input. Enter either '0', '1', '2' or '3'.\n";
				break;
			}
		}
	}

	while (cont == true);
}

int Menu(void)
{
	int choice;

	cout << "\n*MENU*\n";
	cout << "\n0. Exit\n";
	cout << "\n1. Add person to register\n";
	cout << "\n2. Print person in register\n";
	cout << "\n3. Print all people in register\n";
	cout << "\n4. Remove a person from the register\n";
	cout << "\n5. Save register to file\n";
	cout << "\n6. Search file" << endl;
	cin >> choice;

	return choice;
}

void PrintAll(PEOPLE per[], int num)
{
	cout << "Listing people..." << endl;
	for (int ind = 0; (ind < num); ind++)
	{
		cout << "\nName: " << per[ind].name << endl;
		cout << "Distance: " << per[ind].journey << "km" << endl; 
		cout << "Hat size: " << per[ind].size << endl;
		cout << endl;
	}
}

void AddPerson(PEOPLE p_per[], int *per_num)
{
	cout << "\nEnter the first name:\n";
	cin >> p_per[*per_num].name;
	cout << "\nEnter the distance to school:\n";
	cin >> p_per[*per_num].journey;
	cout << "\nEnter the hat size:\n";
	cin >> p_per[*per_num].size;

	(*per_num)++;
}

void PrintPerson(PEOPLE p_per[])
{
	int numb;
	cout << "Enter a number:" << endl;
	cin >> numb;
	if (numb > 10)
	{
		cout << "Incorrect input, the maximum number of people in the register is 10." << endl;
	}
	else
	{
		cout << "Name: " << p_per[numb-1].name << endl;
		cout << "Distance: " << p_per[numb-1].journey << "km" << endl;
		cout << "Hat size: " << p_per[numb-1].size << endl;
	}
}

void RemovePerson(PEOPLE p_per[], int *per_num)
{
	int numb;

	cout << "Enter the number of the person you wish to delete from the register: " << endl;
	cin >> numb;

	*p_per[numb-1].name = NULL;
	p_per[numb-1].journey = 0;
	p_per[numb-1].size = 0;

	for(numb; numb <= *per_num; numb++)
	{
		p_per[numb-1] = p_per[numb];
	}

	(*per_num)--;
}

void SaveToFile(PEOPLE per[], int num)
{
	ofstream file("People.csv");

	file << "PERSON #; NAME; DISTANCE; SIZE" << endl;

	for(int ind = 0; (ind < num); ind++)
	{
		file << ind+1 << ';' << per[ind].name << ';' << per[ind].journey << ';' << per[ind].size << endl;
	}
}

void SearchFile(PEOPLE p_per[], int *per_num)
{
	char head[40];
	int ind = 0;
	int numb;
	ifstream reader("People.csv");

	reader.getline(head, 40);

	do
	{
		reader >> numb;
		reader.get();
		reader.get(p_per[ind].name, 20, ';');
		reader.get();
		reader >> p_per[ind].journey;
		reader.get();
	    reader >> p_per[ind].size;
		reader.get();
		ind++;
	}
	while(reader.good());

	(*per_num) = ind-1;
	reader.close();
}