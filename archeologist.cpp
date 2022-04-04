#include "archeologist.h"
#include "grid.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

Archeologist::Archeologist()
{
	score = 0;
	bones = 0;
	health = 'H';    //H : healthy, T : trapped
}
