#include "Transaction.h"

Transaction::Transaction(vector<object_t> data, char origClass) :
	labelCluster(-1),
	originalClass(origClass),
	vector<object_t>(data)
{
}

Transaction::~Transaction()
{
}

void Transaction::setOriginalClass(char value)
{
	this->originalClass = value;
}

char Transaction::getOriginalClass()
{
	return originalClass;
}

void Transaction::setLabelCluster(int value)
{
	labelCluster = value;
}

int Transaction::getLabelCluster()
{
	return labelCluster;
}