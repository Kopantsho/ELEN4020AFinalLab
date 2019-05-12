#include <stdio.h>
#include <ctime>
#include <vector>
#include <omp.h>
#include <iostream>
#include "fileMatters.h"
#include "blockingKeyValue.h"
int omp_get_num_threads();

using namespace std;
int main(int argc, char **argv)
{
	
	
	srand(time(0));
	fileMatters myFile(9);
	myFile.generateRandomMatrixFile();
	myFile.readFromMatrixFile();	
	r2Vec matrix = myFile.getMatrix();
	myFile.printMatrix(matrix);
	
	blockingKeyValue blocker;
	auto mapping =  blocker.blockMatrix(matrix, 3);
	blocker.printMap(mapping);

	return 0;
}
