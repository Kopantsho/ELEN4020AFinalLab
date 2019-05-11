#ifndef FILEMATTERS_H
#define FILEMATTERS_H
#include <iostream>

#include <fstream>
#include <fstream>
static int matrixSize;
class fileMatters
{
public:
	fileMatters(const int inMatrixSize)
	{
		matrixSize = inMatrixSize;
		std::cout<<"Object Created"<<std::endl;
	}
	~fileMatters()
	{
	}
	void generateRandomMatrixFile()
	{//Generate file of row column order matrix in binary file
		int value = 2505;
		std::ofstream outStream("matrix", std::ios::binary);
		if(outStream.is_open()){
			outStream.write(reinterpret_cast<const char*>(&value), sizeof(int));
			outStream.close();
		}
		
	}
	
	void readFromMatrixFile()
	{
		int test;
		std::ifstream inStream("matrix", std::ios::binary);
		if(inStream.is_open())
		{
			inStream.read(reinterpret_cast<char*>(&test), sizeof(int));
			std::cout<<test<<'\n';
		}
	}
private:
};

#endif // FILEREADER_H
