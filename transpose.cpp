#include <stdio.h>
#include <ctime>
#include <vector>
#include <omp.h>
#include <iostream>
#include "fileMatters.h"
#include "blockingKeyValue.h"
using namespace std;
typedef std::vector<std::vector<int>> r2Vec;

void SerialMatrixTranspose(auto* inMatrix)
//Transposes a NxN matrix without any threading
{
    cout<<"Transposing Blocks"<<endl;
    auto N = inMatrix->size();
    for(auto k = 0; k < N; k++)
    {
        auto M = inMatrix->at(k).subBlock.size();
        auto tempVec = inMatrix->at(k).subBlock;
         for(auto i = 0; i < M; i++)
        {
            for(auto j = i; j < M; j++){
                auto tempVar = tempVec.at(i).at(j);
                tempVec.at(i).at(j) = tempVec.at(j).at(i);
                tempVec.at(j).at(i) = tempVar;
            }
        }
        inMatrix->at(k).subBlock = tempVec;
    }
    /*
   
     * */
}



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
    SerialMatrixTranspose(&mapping);
    blocker.printMap(mapping);
    
    

	return 0;
}
