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

	fileMatters() {
		readFromMatrixFile();
	}
	fileMatters(const int inMatrixSize)
	{
		matrixSize = inMatrixSize;
		generateRandomMatrixFile(inMatrixSize);
		//readFromMatrixFile();
		std::cout<<"Object Created"<<std::endl;
	}
	~fileMatters()
	{
	}
	void generateRandomMatrixFile(int matrixSize)
	{//Generate file of row column order matrix in binary file
		std::vector<int> numbers;

		for(auto i = 0; i< matrixSize*matrixSize; i++) {
			numbers.push_back(std::rand() %100);
			std::cout<<numbers.at(i)<<'\n';
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
				//int *result = new int[matrixSize*matrixSize];
				for(auto i = 0; i< matrixSize*matrixSize; i++){
					inStream.read(reinterpret_cast<char*>(&test), sizeof(int));
					elements.push_back(test);
				}
			}
			inStream.close();
		}

	}

	void printCurMatrixInMem()
	{//Prints the current stored matrix
		for(auto i = 0; i < elements.size(); i++){
			std::cout<<elements.at(i)<<' '<<std::endl;

			}
	}



auto getElements()
{
	return elements;
}
private:
	int matrixSize;
	std::vector<int> elements;
};

#endif // FILEREADER_H
