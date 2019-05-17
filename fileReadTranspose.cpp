#include <stdio.h>
#include <ctime>
#include <vector>
#include <cmath>
#include <iostream>
#include <array>
#include <mpi.h>
#include <fstream>
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

  double start = MPI_Wtime();

int bufsize, count, *buf, matrixSize;
    char filename[128];
    MPI_Datatype type;
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
    cout<<"Buf size: "<< bufsize <<endl;
    buf = (int *) malloc (bufsize * sizeof(int)*100);

    MPI_File_set_view(thefile,(myrank) * bufsize * sizeof(int),
		     MPI_INT, MPI_INT, "native", MPI_INFO_NULL);
    MPI_File_read(thefile, buf, bufsize, MPI_INT, &status);
    MPI_Get_count(&status,MPI_INT, &count);
    cout << "process " << myrank << " read " << count << " ints"
	 << endl;
   matrixSize = count*numprocs;
   matrixSize = sqrt(matrixSize);
   cout<<"Matrix size "<<matrixSize<<endl;
for (size_t i = 0; i < count; i++) {
  cout<<buf[i]<<endl;
}
   MPI_File_close(&thefile);
   //Define contiguous
   MPI_Datatype dt_points;
   MPI_Type_contiguous(3, MPI_INT, &dt_points);
   MPI_Type_commit(&dt_points);


//End of file reading part
auto n_structure_per_process = matrixSize;

matrixElement elements[bufsize];
matrixElement recv[bufsize];

      int counter = 0;
      for(auto i = 0; i < matrixSize/numprocs; i++){
       for(auto j = 0; j < matrixSize; j++){

         elements[counter].x = j;
         elements[counter].y = i;
         elements[counter].val = buf[counter];
         cout<<elements[counter].x<<' '<<elements[counter].y<<' '<<elements[counter].val<<endl;
         counter++;
       }
     }
      free(buf);
       cout<<"From process: "<<myrank<<" counter is "<<counter<<endl;

      SerialMatrixTranspose(elements, count, myrank);
    if(myrank == 0)//send on not zero
    {
      matrixElement matrixElements[numprocs][bufsize];
      for(auto i = 0; i < bufsize; i++)
      {
          matrixElements[0][i] = elements[i];
      }

      for(auto i = 1; i< numprocs; i++){
          MPI_Recv(recv, bufsize, dt_points,i, 0, MPI_COMM_WORLD, &status);
          //matrixElements[i] = &recv;
          cout<<"received from "<<i<<endl;
          for(auto j = 0; j< bufsize; j++){

            matrixElements[i][j] = recv[j];
          }

        }

        for(auto i = 0; i< numprocs; i++)
        {
          for(auto j = 0; j < bufsize; j++)
          {
              int temp = matrixElements[i][j].x;
              matrixElements[i][j].x = temp+matrixSize/numprocs*i;
              cout<<matrixElements[i][j].x<<' '<<matrixElements[i][j].y<<' '<<matrixElements[i][j].val<<endl;

          }
        }
        cout<<"SPLIT"<<endl;
        //Put into array
         matrixElement resultVals[matrixSize];
         int placer = 0;
         int condition = 0;


    //Put into serial
        for (size_t i = 0; i< numprocs; i++){
          for (size_t j = 0; j < bufsize; j++) {
            resultVals[placer] = matrixElements[i][j];
            placer++;
          }
        }

//Bubble sort

for(auto i=0;i<=matrixSize*matrixSize;i++)
{
for(auto j=0;j<=matrixSize*matrixSize-1;j++)
{
if(resultVals[j].y>resultVals[j+1].y)
{
matrixElement temp=resultVals[j];
resultVals[j]=resultVals[j+1];
resultVals[j+1]=temp;
}
}
}

int k=1;
  for(auto j = 0; j < matrixSize*matrixSize; j++){
    cout << resultVals[j].val  << " ";
    if(j == 7*k){
      cout << endl;
      k++;
    }
  }





//Print out file
/*
std::ofstream outStream("matrix_out", std::ios::binary);
if(outStream.is_open()){
  for(auto x=0; x< matrixSize; x++){
  outStream.write(reinterpret_cast<const char*>(&matrixElements[x]), sizeof(int));
  }
  }
  outStream.close();
*/



    } else {//receive on zero

      MPI_Send(&elements, bufsize, dt_points, 0,0,MPI_COMM_WORLD);
      cout<<"Sending from "<<myrank<<endl;


    }


    MPI_Finalize();

    double end = MPI_Wtime();

    cout << "Time in seconds for rank " << myrank<< ": " << end - start << endl;

    return 0;
}
