#include "grid.h"
#include "resources.h"
#include "archeologist.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>


using namespace std;

Grid::Grid(int n)
{
	gridSize = n;
	gridBoard = new char*[gridSize];
	for (int i = 0; i < gridSize; i++)
    {
		gridBoard[i] = new char[gridSize];
	}

	for (int i = 0; i < gridSize; i++)
    {
		for (int j = 0; j < gridSize; j++)
		{
			gridBoard[i][j] = 'X';
		}
	}

    //a separate grid initialized for resources
	tempResources = new char*[gridSize];
	for (int i = 0; i < gridSize; i++)
    {
		tempResources[i] = new char[gridSize];
	}

	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridSize; j++)
		{
			tempResources[i][j] = 'Z';  //Z : empty
		}
	}
}

void Grid::printGrid()
{
	cout << "\n\n";
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			cout << gridBoard[i][j] << "    ";
		}
		cout << "\n\n";
	}

}

void Grid::deploy_resources()
{
	Bones bones;
	Food food;
	Traps traps;
	Water water;
	MedicalSupplies medicalSupplies;

	int bFNumber = (3 * (gridSize * gridSize)) / 25;  //bone and food
	int tWNumber = (2 * (gridSize * gridSize)) / 25;  //traps and water
	int mNumber = (gridSize * gridSize) / 25;         //medical aid
	int randomX, randomY;
	bool resourceEmpty = false; //true : resource empty, false : resource not empty

	//deploy bones resources
	srand(time(0));
	for (int i = 0; i < bFNumber; i++)
    {
		while (!resourceEmpty)
		{
			randomX = rand() % gridSize;
			randomY = rand() % gridSize;
			if (tempResources[randomX][randomY] == 'Z')
                resourceEmpty = true;
		}
        if (resourceEmpty == true)
        {
			tempResources[randomX][randomY] = bones.representation[rand() % 3];
			resourceEmpty = false;
		}
	}

	//deploy food resources
	srand(time(0));
	for (int i = 0; i < bFNumber; i++)
    {
		while (!resourceEmpty)
		{
			randomX = rand() % gridSize;
			randomY = rand() % gridSize;
			if (tempResources[randomX][randomY] == 'Z')
                resourceEmpty = true;
		}
		if (resourceEmpty == true)
        {
			tempResources[randomX][randomY] = food.representation[rand() % 3];
			resourceEmpty = false;
		}
	}

	//deploy water resources
	srand(time(0));
	for (int i = 0; i < tWNumber; i++)
    {
		while (!resourceEmpty)
		{
			randomX = rand() % gridSize;
			randomY = rand() % gridSize;
			if (tempResources[randomX][randomY] == 'Z')
                resourceEmpty = true;
		}

		if (resourceEmpty == true)
        {
			tempResources[randomX][randomY] = water.representation[rand() % 1];
			resourceEmpty = false;
		}
	}

	//deploy traps resources
	srand(time(0));
	for (int i = 0; i < tWNumber; i++)
    {
		while (!resourceEmpty)
		{
			randomX = rand() % gridSize;
			randomY = rand() % gridSize;
			if (tempResources[randomX][randomY] == 'Z')
                resourceEmpty = true;
		}

		if (resourceEmpty == true)
        {
			tempResources[randomX][randomY] = traps.representation[rand() % 1];
			resourceEmpty = false;
		}
	}

	//deploy medical resources
	srand(time(0));
	for (int i = 0; i < mNumber; i++)
    {
		while (!resourceEmpty)
        {
			randomX = rand() % gridSize;
			randomY = rand() % gridSize;
			if (tempResources[randomX][randomY] == 'Z')
                resourceEmpty = true;
		}

		if (resourceEmpty == true)
        {
			tempResources[randomX][randomY] = medicalSupplies.representation[rand() % 1];
			resourceEmpty = false;
		}
	}
}

int Grid::rollDice()
{
	int roll;
	srand(time(0));
	roll = rand() % 6 + 1;

	return roll;
}

void Grid::gamePlay()
{
	Archeologist cope;
	Archeologist marsh;

	//initializing energies for the players
	int maxi = 2 * gridSize;
	int mini = gridSize;
	srand(time(NULL));
	float energy = rand() % (maxi  + 1 - mini) + mini;
	cope.energy = energy;
	marsh.energy = energy;

	//initializing the stock arrays for players
	cope.stock = new char [2*gridSize];
	marsh.stock = new char [2*gridSize];
	for (int i=0; i < 2*gridSize; i++) //X signifies empty
    {
        cope.stock[i] = 'X';
        marsh.stock[i] = 'X';
    }

	bool gameOver = false;
	bool checkBox = false;
	bool player = true;   //true means player 1 and false means player 2.

	while (gameOver != true)
	{
		int rowInput, columnInput;
		while (checkBox != true)  //checking if grid box empty or no
        {
			if (player == true)
                cout << "Player 1 - Cope's Turn (P):\n";
			else
                cout << "Player 2 - Marsh's Turn (A):\n";
			cout << "Please choose row num:\n";
			cin >> rowInput;
			cout << "Please choose column num:\n";
			cin >> columnInput;

			if ((rowInput == 1 && columnInput == 1) || (rowInput == gridSize && columnInput == gridSize) || (rowInput > gridSize || columnInput > gridSize)
                || (gridBoard[rowInput-1][columnInput-1] == 'P' || gridBoard[rowInput-1][columnInput-1] == 'A'))
            {
				cout << "Wrong input or box already occupied, enter again.\n";
				checkBox = false;

				if (player == true)
                cout << "Player 1 - Cope's Turn (P):\n";
                else
                    cout << "Player 2 - Marsh's Turn (A):\n";
                cout << "Please choose row num:\n";
                cin >> rowInput;
                cout << "Please choose column num:\n";
                cin >> columnInput;
			}
			else
			{
				int diceEffect = rollDice();
				cout << "Dice: " << diceEffect << endl;
				if (player == true)
                    cout << "Cope selected  >>  Row: " << rowInput << ", Col: " << columnInput << endl;
				else
                    cout << "Marsh selected >>  Row: " << rowInput << ", Col: " << columnInput << endl;
				if (tempResources[rowInput-1][columnInput-1] != 'Z')
				{
					char temp = tempResources[rowInput-1][columnInput-1];

					Bones bones;
					Food food;
					Traps traps;
					Water water;
					MedicalSupplies medicalSupplies;

                    static c = 0, m = 0;  //for the stock array of the players

					if (temp == 'F' || temp == 'S' || temp == 'O')
                    {
						cout << "\n***FOUND BONE***\n\n";
						if (player == true)
						{
							cope.score = bones.resourcesCriteria(temp, cope.score);
							cope.bones = cope.bones + 1;
							cope.stock[c] = temp;
							c++;
						}
						else
						{
							marsh.score = bones.resourcesCriteria(temp, marsh.score);
							marsh.bones = marsh.bones + 1;
							marsh.stock[m] = temp;
							m++;
						}
					}
					else if (temp == 'B' || temp == 'N' || temp == 'C')
					{
						cout << "\n***FOUND FOOD***\n\n";
						if (player == true)
                        {
                            cope.energy = food.resourcesCriteria(temp, cope.energy);
                            cope.stock[c] = temp;
                            c++;
                        }
						else
                        {
                            marsh.energy = food.resourcesCriteria(temp, marsh.energy);
                            marsh.stock[m] = temp;
                            m++;
                        }

					}
					else if (temp == 'W')
                    {
						cout << "\n***FOUND WATER***\n\n";
						if (player == true)
                        {
                            cope.energy = water.resourcesCriteria(temp, cope.energy);
                            cope.stock[c] = temp;
                            c++;
                        }
						else
                        {
                            marsh.energy = water.resourcesCriteria(temp, marsh.energy);
                            marsh.stock[m] = temp;
                            m++;
                        }
					}
					else if (temp == 'M')
					{
						cout << "\n***FOUND MEDICAL SUPPLIES***\n\n";
						if (player == true)
                        {
                            cope.health = 'H';
                            cope.stock[c] = temp;
                            c++;
                        }
						else
                        {
                            marsh.health = 'H';
                            marsh.stock[m] = temp;
                            m++;
                        }
					}
					else if (temp == 'T')
					{
						if (diceEffect != 1 || diceEffect != 6)
						{
							cout << "\n***TRAPPED***\n\n";
							if (player == true)
                                cope.health = 'T';
							else
                                marsh.health = 'T';
						}
					}
				}

				if (marsh.bones > (3*(gridSize*gridSize)/25)/2 && cope.energy < 0)
                {
					checkBox = true;
					gameOver = true;
					cout << "Marsh Won!!! Marsh bones collected: " << marsh.bones << "\nGAME OVER\n";
				}
				else if (cope.bones > (3*(gridSize*gridSize)/25)/2 && marsh.energy < 0)
				{
					checkBox = true;
					gameOver = true;
					cout << "Cope Won!!! Cope bones collected: " << cope.bones << "\nGAME OVER\n";
				}
				else if (marsh.energy < 0 && cope.energy < 0)
				{
					checkBox = true;
					gameOver = true;
					if (cope.score > marsh.score)
                        cout << "Cope Won!!! Cope bones collected: " << cope.bones << "\nGAME OVER\n";
                    else
                        cout << "Marsh Won!!! Marsh bones collected: " << marsh.bones << "\nGAME OVER\n";
				}
				else
				{
					if (cope.energy > 0 && player == false) //if cope has energy only then change player
                        player = !player;
                    else if (marsh.energy > 0 && player == true) //if marsh has energy then change player
                        player = !player;
                    else
                        player = player; //no energy of the other player so same player will play

                    cout << "Stats: " << endl;
					cout << "Score >> " << "Cope: " << cope.score << "	  Marsh: " << marsh.score << endl;
					cout << "Energy>> " << "Cope: " << cope.energy << "	  Marsh: " << marsh.energy << endl;
					cout << "Bones >> " << "Cope: " << cope.bones << "	  Marsh: " << marsh.bones << endl;
					cout << "Health>> " << "Cope: " << (cope.health == 'H' ? "Healthy" : "Trapped") << "	  Marsh: " << (marsh.health == 'H' ? "Healthy" : "Trapped") << endl;
				}
			}

            if (player == true)
                gridBoard[rowInput - 1][columnInput - 1] = 'D';  //D for discovered
            else
                gridBoard[rowInput - 1][columnInput - 1] = 'D';  //D for discovered

			//energy spent
            if (player == true)
            {
                if (cope.health == 'H')
                    cope.energy = cope.energy - 1;
                else
                    cope.energy = cope.energy - 1.25;  //trapped
            }
            else
            {
                if (marsh.health == 'H')
                    marsh.energy = marsh.energy - 1;
                else
                    marsh.energy = marsh.energy - 1.25; //trapped
            }
            printGrid();
		}
	}
}


