#include <iostream>
#include <cstdlib>

#include <cmath>
#include <limits>
#include <climits>

#include "program.h"

int main()
{
	AntOptimization::Program program({ 1366, 768 }, "Ant Colony Optimization");
	program.Run();

	// reworked ant algorithm and combine with CityGen functions

	/*ANTS -> printGRAPH ();

	ANTS -> printPHEROMONES ();

	ANTS -> optimize (ITERATIONS);

	ANTS -> printRESULTS ();*/

	return 0;
}
