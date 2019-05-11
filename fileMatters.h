#ifndef FILEMATTERS_H
#define FILEMATTERS_H
#include <iostream>

#include <fstream>
#include <fstream>
#include <vector>
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
		std::vector<int> numbers;
		//Generate Random Numbers
		for(auto i = 0; i< matrixSize; i++) {
			numbers.push_back(std::rand() %100);
			std::cout<<numbers.at(i)<<std::endl;
		}
		
		std::ofstream outStream("matrix", std::ios::binary);
		if(outStream.is_open()){
			for(auto x:numbers){
			outStream.write(reinterpret_cast<const char*>(&x), sizeof(int));
			}
			}
			outStream.close();
		}
		
		
	
	
	void readFromMatrixFile()
	{
		int test;
		std::ifstream inStream("matrix", std::ios::binary);
		if(inStream.is_open())
		{
			while(!inStream.eof())
			{
			inStream.read(reinterpret_cast<char*>(&test), sizeof(int));	
			}
			
			inStream.close();
		}
	}
private:
};

#endif // FILEREADER_H
