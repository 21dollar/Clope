#pragma once

#include <map>

#include "Transaction.h"

class Cluster
{
public:
	Cluster();
	~Cluster();
	//std::set<object_t> D();	// ��������� ���������� ��������
	size_t Occ(object_t i);		// ���������� ��������� (�������) ������� i � ������� C;
	double S();					// �������
	double W();					// ������
	double H();					// ������
	double G(double r);
	void add(Transaction& t);
	void remove(Transaction& t);
	double size();
	bool empty();


private:
	std::map<object_t, size_t> occ;
	size_t s;
	size_t _size;
};