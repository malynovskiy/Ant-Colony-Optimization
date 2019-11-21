#include "Program.h"

int main()
{
	AntOptimization::Program program({ 1366, 768 }, "Ant Colony Optimization");
	program.Run();

	return 0;
}
