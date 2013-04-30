/*
 * sample.cpp
 *
 *  Created on: 26 Apr 2013
 *      Author: cemgil
 */

#include "graph.h"

double uRand() {return double(rand())/RAND_MAX; };

struct Event {
	double t;
	unsigned int node;
	bool born;
	Event(double _t=0.0, unsigned int n=0, bool isBorn=true) {t = _t; node = n; born = isBorn;};
	void Print() {cout << t << ":" << node << " " << born << endl;}
};
bool isAfter(Event& a, Event& b) {return a.t > b.t;};

double defaultWeightFun() {return int(uRand()*20)+1;}

void Graph::SampleIntervalGraph(unsigned int Seed, bool isDirected, double lam1, double lam2, double (*WeightFun)()) {
	double t=0, dt, m;

	double probThin = 0.7;
	vector<Event> L; // Array of events, we will build a heap here
	set<unsigned int> active; // Currently alive nodes in interval graph construction
	Clear();

	if (WeightFun==NULL) WeightFun = defaultWeightFun;

	srand(Seed); // time(NULL)
	for (unsigned int i=0;i<N;i++) {
		dt= 1 -lam1*log(uRand()) ;
		//m = -lam2*log(uRand());
		m = lam2;
		//m = 7;
		t = t + dt;
		L.push_back(Event(t, i, true));   // Push Birth
		L.push_back(Event(t+m, i, false));  // Push Death
	}

	make_heap(L.begin(), L.end(), isAfter);

	for (unsigned int i=0;i<2*N;i++) {
		pop_heap(L.begin(), L.end(), isAfter);
		vector<Event>::reverse_iterator e = L.rbegin();
		if (e->born) {
			for (set<unsigned int>::iterator it=active.begin(); it!=active.end(); it++) {
				if (!isDirected) {
				if (uRand()>probThin) {
					double w = WeightFun();
					//double w = 1.;
					AddEdge(*it, Edge(e->node, w));
					AddEdge(e->node, Edge(*it, w));
				}
				}
				else {
					double w;
					if (uRand()>probThin) {
						w = WeightFun();
						AddEdge(*it, Edge(e->node, w));
					}
					if (uRand()>probThin) {
						w = WeightFun();
						AddEdge(e->node, Edge(*it, w));
					}
				}
			}
			active.insert(e->node);
		}
		else {
			set<unsigned int>::iterator it=active.find(e->node);
			if (it!=active.end()) active.erase(it);
		}
		L.pop_back();
	};

}


