#include <stdio.h>
#include <ctime>
#include "fileMatters.h"

int main(int argc, char **argv)
{
	srand(time(0));
	fileMatters myFile(32);
	myFile.generateRandomMatrixFile();
	myFile.readFromMatrixFile();
	
	return 0;
}
