#include "resources.h"


Resources::Resources()
{
	sizer = 0;
	representation = new char[1]{'X'}; //initially X means hidden/no resource found.
}


Bones::Bones()
{
	//F - full bone
	//S - Skull
	//O - Ordinary bone
	representation = new char[3]{'F', 'S', 'O'};
}

int Bones::resourcesCriteria(char letter, int score)
{
	int temp = score;
	switch (letter)
	{
		case 'F':
			sizer = 2;
			temp = temp + 100;
			break;
		case 'S':
			sizer = 1;
			temp = temp + 50;
			break;
		case 'O':
			sizer = 1;
			temp = temp + 20;
			break;
	}
	return temp;
}


Traps::Traps()
{
	representation = new char[1]{'T'};
}

int Traps::resourcesCriteria(char letter, int score)
{
	sizer = 1;
	return 0;
}

Food::Food()
{
	//B - Burger
	//N - Nuggets
	//C - Chips
	representation = new char[3]{'B', 'N', 'C'};
}

int Food::resourcesCriteria(char letter, int energy)
{
	int temp = energy;
	switch (letter)
	{
		case 'B':
			sizer = 2;
			temp = temp + 4;
			break;
		case 'N':
			sizer = 2;
			temp = temp + 3;
			break;
		case 'C':
			sizer = 1;
			temp = temp + 2;
			break;
	}
	return temp;
}

Water::Water()
{
	representation = new char[1]{'W'};
}

int Water::resourcesCriteria(char letter, int energy)
{
	energy = energy + 1;
	return energy;
}


MedicalSupplies::MedicalSupplies()
{
	representation = new char[1]{'M'};
}

int MedicalSupplies::resourcesCriteria(char letter, int score)
{
	sizer = 1;
	return 0;
}









