#include <iostream>
#include "grid.h"

using namespace std;


int main() {
	Grid grid;
	grid.printGrid();
	grid.deploy_resources();
	grid.gamePlay();


	return 0;
}
