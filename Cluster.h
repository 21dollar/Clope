#pragma once
adsfadas
#include <map>

#include "Transaction.h"

class Cluster
{
public:
	Cluster();
	~Cluster();
	//std::set<object_t> D();	// ìíîæåñòâî óíèêàëüíûõ îáúåêòîâ
	size_t Occ(object_t i);		// êîëè÷åñòâî âõîæäåíèé (÷àñòîòà) îáúåêòà i â êëàñòåð C;
	double S();					// Ïëîùàäü
	double W();					// Øèðèíà
	double H();					// Âûñîòà
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