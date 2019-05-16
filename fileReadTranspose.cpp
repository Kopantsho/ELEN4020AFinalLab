#include <stdio.h>
#include <ctime>
#include <vector>
#include <cmath>
#include <iostream>

#include <mpi.h>
using namespace std;
struct matrixElement{
  int x;
  int y;
  int val;
};

void SerialMatrixTranspose(matrixElement inMatrix[], int size, int rank)
//Transposes a NxN matrix without any threading
{
    cout<<"Transposing Blocks on Process "<<rank<<endl;
    for(auto i = 0; i < size; i++){
      auto tempVar = inMatrix[i].x;
      inMatrix[i].x = inMatrix[i].y;
      inMatrix[i].y = tempVar;
    }
}


int main(int argc, char **argv)
{
/*
char *fileName = argv[1];
int size, rank;
//, err = 0, errs = 0, *buf, n;
MPI_File matrixFile;
MPI_Datatype filetype;
MPI_Status status;

MPI_Init(&argc, &argv);
MPI_Comm comWorld = MPI_COMM_WORLD;
MPI_Comm_size(MPI_COMM_WORLD, &size); //Number of processes
MPI_Comm_rank(MPI_COMM_WORLD, &rank);//Current Rank

int error = MPI_File_open(MPI_COMM_WORLD, fileName, MPI_MODE_RDONLY, MPI_INFO_NULL, &matrixFile);
if(error){
  MPI_Abort(MPI_COMM_WORLD, 404); //File error
}
auto* buffer = (int*)malloc(sizeof(int));
cout<<"Reading from file"<<endl;

MPI_File_read(matrixFile, buffer, 1, MPI_INT, &status);
int matrixSize = buffer[0];
if(rank == 0)
{

  cout<<"World size:"<<size<<endl;
  cout<<"Matrix size:"<<matrixSize<<endl;
}
auto m = (int)(matrixSize/size);
auto* a = (int*)malloc(m*matrixSize*sizeof(int));
auto* b = (int*)malloc(m*matrixSize*sizeof(int));
int i,j;
MPI_Offset blockLength = m*matrixSize;

MPI_Offset displace = ((rank*blockLength)+1)*sizeof(int);
MPI_File_set_view(matrixFile, displace, MPI_INT, MPI_INT, "native", MPI_INFO_NULL);
MPI_File_read(matrixFile, a, blockLength, MPI_INT, &status);

if(rank == 0)
{
  cout<<a<<endl;
}
MPI_File_close(&matrixFile);
free(buffer);
MPI_Finalize ();
*/
//https://www.codingame.com/playgrounds/349/introduction-to-mpi/custom-types


int bufsize, *buf, count, matrixSize;
    char filename[128];
    MPI_Status status;

    MPI_Init (&argc, &argv);
    int myrank;
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    int numprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    MPI_File thefile;
    MPI_File_open(MPI_COMM_WORLD, "matrix",
                                        MPI_MODE_RDONLY,
                                        MPI_INFO_NULL, &thefile);

    MPI_Offset filesize;
    MPI_File_get_size(thefile, &filesize);  // in bytes
    filesize    = filesize / sizeof(int);    // in number of ints
    bufsize     = filesize / numprocs;   // local number to read
    buf = (int *) malloc (bufsize * sizeof(int));
    MPI_File_set_view(thefile,(myrank) * bufsize * sizeof(int),
		     MPI_INT, MPI_INT, "native", MPI_INFO_NULL);
    MPI_File_read(thefile, buf, bufsize, MPI_INT, &status);
    MPI_Get_count(&status,MPI_INT, &count);
    cout << "process " << myrank << " read " << count << " ints"
	 << endl;
   matrixSize = count*numprocs;
   matrixSize = sqrt(matrixSize);
   cout<<"Matrix size "<<matrixSize<<endl;

//End of file reading part
   auto n_structure_per_process = matrixSize;

   matrixElement elements[count];
   int counter = 0;
   for(auto i = 0; i < matrixSize/numprocs; i++){
    for(auto j = 0; j < matrixSize; j++){
      elements[counter].x = j;
      elements[counter].y = i;
      elements[counter].val = buf[counter];
      counter++;
    }
  }
    cout<<"From process: "<<myrank<<" counter is "<<counter<<endl;
    //for(auto i = 0; i < count;i++){
  //    cout<<elements[i].y<<' '<<elements[i].x<<' '<<elements[i].val<<endl;
    //}
    SerialMatrixTranspose(elements, count, myrank);
    free(buf);
    MPI_File_close(&thefile);
    MPI_Finalize();

    return 0;
}
