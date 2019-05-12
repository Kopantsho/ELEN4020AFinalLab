#ifndef BLOCKINGKEYVALUE_H
#define BLOCKINGKEYVALUE_H
#include <vector>
#include <iostream>

typedef std::vector<std::vector<int>> r2Vec;
struct keyValuePair
{//Struct for the key value pair
	int x;
	int y;
	r2Vec subBlock;
}

class blockingKeyValue
{
public:
	blockingKeyValue()
	{
	}
	~blockingKeyValue()
	{
	}
	 std::vector<keyValuePair> blockMatrix(const auto &inMatrix, const int blockSize)
	 {//Creates a map of sub matrices. The key will be the position of the sub matrix relative to the large Matrix. The value will be the sub matrix
		 auto runTotals = inMatrix.size()/blockSize; // A 8x8 matrix devided into 2x2 blocks will have 4x4 sub blocks
		 runTotals = runTotals*runTotals;// There will be a square amount of sub matrices
		std::vector<keyValuePair> subBlockMapping;
		
	 }
private:
	r2Vec blockMatrix(const auto &inMatrix, auto starti, auto endi, auto startj, auto endj)
	{
		r2Vec subBlock;	
		for(auto i = starti; i < endi; i++)
		{
			std::vector<int> tempVec;
			for(auto j = startj; j < endj; j++)
			{
				tempVec.push_back(inMatrix.at(i).at(j));
			}
			subBlock.push_back(tempVec);
		}
		return subBlock;
	}

};

#endif // BLOCKINGKEYVALUE_H
