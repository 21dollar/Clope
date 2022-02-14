#include "Cluster.h"

Cluster::Cluster() : s(0), _size(0)
{
}

Cluster::~Cluster()
{
}

//std::set<object_t> Cluster::D()
//{
//	//Оптимизировано
//	/*std::set<object_t> uniqeObjects;
//	for (Transaction& transation : *this)
//	{
//		uniqeObjects.insert(transation.cbegin(), transation.cend());
//	}
//	return uniqeObjects;*/
//}

size_t Cluster::Occ(object_t i)
{
	return occ.count(i) ? occ[i] : 0;
}

double Cluster::S()
{
	// Оптимизировано
	/*size_t s = 0;
	for (Transaction& t : *this)
	{
		s += t.size();
	}*/
	return double(s);
}

double Cluster::W()
{
	// Оптимизировано
	//return double(this->D().size());
	return double(occ.size());
}

double Cluster::H()
{
	return S() / W();
}

inline double Cluster::G(double r)
{
	return S() / (pow(W(), r));
}

void Cluster::add(Transaction& t)
{
	for (object_t& o : t)
	{
		++occ[o];
	}
	this->s += t.size();
	++this->_size;
}

void Cluster::remove(Transaction& t)
{
	for (object_t& o : t)
	{
		if (--occ[o] == 0)
		{
			occ.erase(o);
		}
	}
	this->s -= t.size();
	--this->_size;
}

double Cluster::size()
{
	return double(_size);
}

bool Cluster::empty()
{
	return _size == 0;
}