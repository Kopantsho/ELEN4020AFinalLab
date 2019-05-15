#include <stdio.h>
#include <ctime>
#include <vector>
#include <omp.h>
#include <iostream>
#include "fileMatters.h"
#include "blockingKeyValue.h"
#define MATRIX_SIZE 9
using namespace std;
struct matrixElement{
  int x;
  int y;
  int val;
};


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
	fileMatters myFile(MATRIX_SIZE);
  auto arr= myFile.getElements();
  for(auto i = 0; i< MATRIX_SIZE*MATRIX_SIZE; i++){
    cout<<arr[i]<<endl;
  }
  //Serial the elements into coordinate pairs with value. Function was giving segmentation fault
  matrixElement elements[MATRIX_SIZE*MATRIX_SIZE];
  auto counter = 0;
  for(auto i = 0; i < MATRIX_SIZE; i++){
    for(auto j = 0; j < MATRIX_SIZE; j++){
      elements[counter].x = j;
      elements[counter].y = i;
      elements[counter].val = arr[counter];
      counter++;
    }
  }

  for(auto i = 0; i< MATRIX_SIZE*MATRIX_SIZE; i++){
    cout<<elements[i].y<<' '<<elements[i].x<<' '<<elements[i].val<<endl;
  }



	return 0;
}
