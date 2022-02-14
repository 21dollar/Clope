#include "Clope.h"

Clope::Clope()
{
}

Clope::~Clope()
{
}

double Clope::addCost(Cluster& C, Transaction& T, double r)
{
	double S = C.S(); /* текущий размер кластера */
	double N = C.size(); /* количество транзакций в кластере */
	double W = C.W(); /* текущая ширина кластера (количество уникальных элементов) */
	double Snew = S + T.size();
	double Nnew = N + 1.;
	double Wnew = W;

	for (object_t& O_k : T)
	{
		if (C.Occ(O_k) == 0)
		{
			Wnew += 1.;
		}
	}
	if (W == 0)
	{
		return (Snew * Nnew) / pow(Wnew, r);
	}
	return (Snew * Nnew) / pow(Wnew, r) - (S * N) / pow(W, r);
}

double Clope::removeCost(Cluster& C, Transaction& T, double r)
{
	double S = C.S(); /* текущий размер кластера */
	double N = C.size(); /* количество транзакций в кластере */
	double W = C.W(); /* текущая ширина кластера (количество уникальных элементов) */
	double Snew = S - T.size();
	double Nnew = N - 1.;
	double Wnew = W;

	for (object_t& O_k : T)
	{
		if (C.Occ(O_k) == 1)
		{
			Wnew -= 1.;
		}
	}
	if (Wnew == 0)
	{
		return -(S * N) / pow(W, r);
	}
	return (Snew * Nnew) / pow(Wnew, r) - (S * N) / pow(W, r);
}



void Clope::clope(std::vector<Transaction>& T, std::vector<Cluster>& C, double r)
{
	std::map<size_t, size_t> transactionsCluster;

	size_t bestChoice = 0;
	bool moved;

	C.push_back(Cluster());

	for (size_t i = 0; i < T.size(); i++)
	{
		double maxCost = 0;
		for (size_t j = 0; j < C.size(); j++)
		{
			double dblAddCost = addCost(C[j], T[i], r);
			if (dblAddCost > maxCost)
			{
				maxCost = dblAddCost;
				bestChoice = j;
			}
		}
		if (C[bestChoice].empty())
		{
			C.push_back(Cluster());
		}
		C[bestChoice].add(T[i]);
		T[i].setLabelCluster(int(bestChoice));
		transactionsCluster[i] = bestChoice;
	}

	int k = 0;
	do
	{
		std::cout << "--Iteration " << k++ << std::endl;
		moved = false;
		for (size_t i = 0; i < T.size(); i++)
		{
			double maxCost = 0;

			size_t act = transactionsCluster[i];
			double remCost = removeCost(C[act], T[i], r);

			for (size_t j = 0; j < C.size(); j++)
			{
				if (j != act)
				{
					double dblAddCost = addCost(C[j], T[i], r);
					if (dblAddCost + remCost > maxCost)
					{
						maxCost = dblAddCost + remCost;
						bestChoice = j;
					}
				}
			}
			if (maxCost > 0)
			{
				if (C[bestChoice].empty())
				{
					C.push_back(Cluster());
				}
				C[act].remove(T[i]);
				C[bestChoice].add(T[i]);
				T[i].setLabelCluster(int(bestChoice));
				transactionsCluster[i] = bestChoice;
				moved = true;
			}
		}
	} while (moved == true);
}