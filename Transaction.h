#pragma once
#include <vector>

typedef char object_t;

class Transaction : public std::vector<object_t>
{
public:
	Transaction(vector<object_t> data, char origClass);
	~Transaction();
	void setOriginalClass(char value);
	char getOriginalClass();
	void setLabelCluster(int value);
	int getLabelCluster();

private:
	int labelCluster;
	char originalClass;
};

