#ifndef FILEMATTERS_H
#define FILEMATTERS_H
#include <iostream>

#include <fstream>
#include <fstream>
#include <vector>
static int matrixSize;
typedef std::vector<std::vector<int>> r2Vec;
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
		for(auto i = 0; i< matrixSize*matrixSize; i++) {
			numbers.push_back(std::rand() %100);
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
	{//Read the matrix values from the generated file
		int test;
		std::ifstream inStream("matrix", std::ios::binary);
		if(inStream.is_open())
		{
			while(inStream.peek() != EOF)
			{
			for(auto i = 0; i < matrixSize; i++){
				std::vector<int> tempVec;
				for(auto j = 0; j<matrixSize; j++){
					inStream.read(reinterpret_cast<char*>(&test), sizeof(int));	
					tempVec.push_back(test);
				}
				matrix.push_back(tempVec);
			}
			
			}
			
			inStream.close();
		}
		
	}
	
	void printCurMatrixInMem()
	{//Prints the current stored matrix
		for(auto i = 0; i < matrixSize; i++){
			
			for(auto j = 0; j<matrixSize; j++){
				std::cout<<matrix.at(i).at(j)<<' ';
			}
			std::cout<<'\n';
			}
	}
	
	void printMatrix(const auto &inMatrix)
	{
		for(auto i = 0; i < matrixSize; i++){
			
			for(auto j = 0; j<matrixSize; j++){
				std::cout<<inMatrix.at(i).at(j)<<' ';
			}
			std::cout<<'\n';
			}
	}
	
	r2Vec getMatrix()
	{//Returns the current matrix
		return matrix;
	}
private:
	r2Vec matrix;
};

#endif // FILEREADER_H
