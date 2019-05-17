#include <stdio.h>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>




using namespace std;
int main(int argc, char **argv)
{
    srand(time(NULL));
    vector<int> numbers;
      int matrixSize = 128;

    for(auto i = 0; i< matrixSize*matrixSize; i++) {
      numbers.push_back(std::rand() %100);
      std::cout<<numbers.at(i)<<'\n';
    }

    ofstream outStream("matrix", ios::binary);
    if(outStream.is_open()){
      for(auto x:numbers){
      outStream.write(reinterpret_cast<const char*>(&x), sizeof(int));
      }
      }
      outStream.close();
	return 0;
}
