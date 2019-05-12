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
};

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
		 runTotals = runTotals*runTotals;
		 std::cout<<runTotals<<'\n';
		 //runTotals = runTotals*runTotals;// There will be a square amount of sub matrices
		std::vector<keyValuePair> subBlockMapping;
		
		for(auto i = 0; i < runTotals; i = i +blockSize)
		{
			keyValuePair tempBlock;
			for(auto j = 0; j < runTotals; j = j +blockSize)
			{
				
				tempBlock.x = j;
				tempBlock.y = i;
				tempBlock.subBlock=blockSubMatrix(inMatrix, j, j+blockSize, i, i+blockSize);
				subBlockMapping.push_back(tempBlock);
				std::cout<<"Created Block at "<<j<<" "<<i<<'\n';
			}
		}
		/*
		for(auto k = 1; k < runTotals+1; k++){
		for(auto i = 0; i < runTotals*runTotals; i=i+runTotals)
		{
			std::cout<<i<<'\n';
			keyValuePair tempBlock;
			for(auto j = 0; j< runTotals*runTotals; j=j+runTotals){
				tempBlock.x = i;
				tempBlock.y = j;
				tempBlock.subBlock = blockMatrix(inMatrix, i, i+runTotals, j, j+runTotals);
				subBlockMapping.push_back(tempBlock);
			}
		}
		}
		*/
		return subBlockMapping;
	 }
	 
	 void printMap(std::vector<keyValuePair> &inMapping)
	 { 
		 for(auto i = 0; i < inMapping.size(); i++)
		 {
			 std::cout<<"position: "<<inMapping.at(i).x<<' '<<inMapping.at(i).y<<" with sub Matrix "<<'\n';
			 r2Vec tempBlock = inMapping.at(i).subBlock;
			 for(auto j = 0; j < tempBlock.size(); j++)
			 {
				 for(auto k = 0; k<tempBlock.size(); k++)
					 {
						 std::cout<<tempBlock.at(j).at(k)<<' ';
					 }
				std::cout<<'\n';
			 }
		 }
	 }
	 


	 
private:
	r2Vec blockSubMatrix(const auto &inMatrix, auto starti, auto endi, auto startj, auto endj)
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
