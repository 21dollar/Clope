#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>

#include "Transaction.h"
#include "Cluster.h"
#include "Clope.h"

std::vector<Transaction> readTransactions(const char* fName)
{
	std::ifstream fData(fName);
	if (!fData.is_open())
	{
		std::cout << "File not open" << std::endl;
	}
	else if (fData.peek() == EOF)
	{
		std::cout << "File empty" << std::endl;
	}

	std::string str;
	std::vector<Transaction> T;

	while (std::getline(fData, str))
	{
		str.erase(std::remove(str.begin(), str.end(), ','), str.end());
		Transaction tempT({ str.begin() + 1, str.end() }, str[0]); // Набор характеристик без значения классификации, запись классификации
		if (!tempT.empty())
		{
			T.push_back(tempT);
		}
	}

	return T;
}

int main(int argc, char const* argv[])
{
	const char* file;
	double r;
	if (argc == 2)
	{
		file = argv[1];
		r = 2.6;
	}
	else if (argc == 3)
	{
		file = argv[1];
		r = std::atof(argv[2]);
	}
	else
	{
		std::cout << "Usage: clope.exe <filename> [r]" << std::endl;
		file = "1.data";
		r = 2.6;
		//exit(-1);
	}

	std::vector<Cluster> C = {};
	
	Clope CL;

	std::vector<Transaction> T = readTransactions(file);

	CL.clope(T, C, r);


	std::cout << "Number of Clusters: " << C.size() << std::endl;
	int i = 0;
	std::vector<std::vector<int>> stats(C.size(), std::vector<int>(2, 0));
	for (Transaction& t : T)
	{
		stats[t.getLabelCluster()][t.getOriginalClass() == 'p' ? 0 : 1] ++;

	}
	for (size_t i = 0; i < stats.size(); i++)
	{
		std::cout << "Number of Transactions in C" << std::setw(2) << i << " :" << std::setw(4) << C[i].size()
			<< "; E = " << std::setw(4) << stats[i][0]
			<< "; P = " << std::setw(4) << stats[i][1]
			<< std::endl;
	}

	return 0;
}