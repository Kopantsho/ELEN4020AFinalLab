#include <stdio.h>
#include <ctime>
#include <vector>
#include <iostream>
#include "fileMatters.h"
#include "blockingKeyValue.h"
using namespace std;
int main(int argc, char **argv)
{
	srand(time(0));
	fileMatters myFile(8);
	myFile.generateRandomMatrixFile();
	myFile.readFromMatrixFile();	
	r2Vec matrix = myFile.getMatrix();
	myFile.printMatrix(matrix);
	
	blockingKeyValue blocker;
	auto mapping =  blocker.blockMatrix(matrix, 2);
	blocker.printMap(mapping);

	return 0;
}
