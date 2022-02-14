#pragma once

#include <iostream>
#include <vector>

#include "Cluster.h"

class Clope
{
public:
	Clope();
	~Clope();
	void clope(std::vector<Transaction>& T, std::vector<Cluster>& C, double r);
	double addCost(Cluster& C, Transaction& t, double r);
	double removeCost(Cluster& C, Transaction& t, double r);


private:

};
