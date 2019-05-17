#include <stdio.h>
#include <ctime>
#include <vector>
#include <omp.h>
#include <iostream>
#include "fileMatters.h"
#include "blockingKeyValue.h"
#include "mpi.h"
#define MATRIX_SIZE 8
using namespace std;
struct matrixElement{
  int x;
  int y;
  int val;
};


void SerialMatrixTranspose(matrixElement inMatrix[])
//Transposes a NxN matrix without any threading
{
    cout<<"Transposing Blocks"<<endl;
    for(auto i = 0; i < MATRIX_SIZE*MATRIX_SIZE; i++){
      auto tempVar = inMatrix[i].x;
      inMatrix[i].x = inMatrix[i].y;
      inMatrix[i].y = tempVar;
    }
}



using namespace std;
int main(int argc, char **argv)
{

  //char *size = argv[1];
	srand(time(0));
	fileMatters myFile(16);
  /*
  auto arr= myFile.getElements();

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
  for(auto i = 0; i < MATRIX_SIZE*MATRIX_SIZE; i++)
  {
    cout<<elements[i].y<<' '<<elements[i].x<<' '<<elements[i].val<<endl;
  }
  SerialMatrixTranspose(elements);

  for(auto i = 0; i < MATRIX_SIZE*MATRIX_SIZE; i++)
  {
    cout<<elements[i].y<<' '<<elements[i].x<<' '<<elements[i].val<<endl;
  }
*/
/*
MPI_Init(&argc, &argv);
int rank, size;

constexpr int n_structure_per_process = 5; //M =5

//matrixElement data[n_structure_per_process];

//Create mpi struct properties
MPI_Aint displacements[2] ={};
int block_lennths[2] = {};
MPI_Datatype types[2] = {};
MPI_Datatype custom_dt;
*/
//Create type and commit
	return 0;
}
