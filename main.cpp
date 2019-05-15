#include <stdio.h>
#include <ctime>
#include <vector>
#include <omp.h>
#include <iostream>
#include "fileMatters.h"
#include "blockingKeyValue.h"
#include <mpi.h>
int omp_get_num_threads();
struct Point {
  double x, y, z;
};

using namespace std;
int main(int argc, char **argv)
{
MPI_Init(&argc, &argv);
cout<<"Hello World"<<endl;
	srand(time(0));
	fileMatters myFile(9);
	myFile.generateRandomMatrixFile();
	myFile.readFromMatrixFile();
	r2Vec matrix = myFile.getMatrix();
	//myFile.printMatrix(matrix);

	blockingKeyValue blocker;
	auto mapping =  blocker.blockMatrix(matrix, 3);
	blocker.printMap(mapping);

//https://www.codingame.com/playgrounds/349/introduction-to-mpi/custom-types

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	MPI_Datatype dt_point;
	MPI_Type_contiguous(3, MPI_DOUBLE, &dt_point);
	MPI_Type_commit(&dt_point);

	constexpr int n_points = 9;
	keyValuePair data[n_points];

	if (rank == 0){
    fileMatters myFile(9);
    myFile.generateRandomMatrixFile();
    myFile.readFromMatrixFile();
    r2Vec matrix = myFile.getMatrix();
    //myFile.printMatrix(matrix);

    blockingKeyValue blocker;
    auto mapping =  blocker.blockMatrix(matrix, 3);
    blocker.printMap(mapping);
    data = mapping;
	 MPI_Send(data, n_points, dt_point, 1, 0, MPI_COMM_WORLD);
     //cout<<
	  }

	  else { // Process 1 receives
	    MPI_Recv(data, n_points, dt_point, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	    // Printing
	    for (int i=0; i < n_points; ++i) {
	      std::cout << "Point #" << i << " : (" << data[i].x << "; " << data[i].y << "; "<<")"
			<< std::endl;
	    }
	  }

	  MPI_Finalize();
	//return 0;
}
