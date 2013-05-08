/*
 * graph.h
 *
 *  Created on: 26 Apr 2013
 *      Author: cemgil
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <utility>
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <list>
#include <ctime>
#include <vector>
#include <limits>
#include <algorithm>
#include <cstdlib>
#include <cmath>

using namespace std;

const double INF = numeric_limits<double>::infinity();
double uRand();

struct Edge {
	unsigned int target;
	double Weight;
	int UserData;
	Edge(unsigned int _target=0, double w = 1.0, int ud = 0 ) {
		target = _target; Weight = w; UserData = ud;
	}
};

class Graph {
	vector< list<Edge> > al;
	unsigned int N;
	int dfs(unsigned int, unsigned int&, vector<bool>&, list<unsigned int>&);
public:
	Graph(unsigned int _N) {
		N = _N;
		al.resize(N);
	}
	void AddEdge(unsigned int source, Edge dest) {
		if (source < N) al[source].push_back(dest);
	}

	void FindAndMarkEdge(unsigned int source, unsigned int target, int ud=1) {
		if (source <N) {
			for (list<Edge>::iterator it=al[source].begin(); it!=al[source].end();it++)
				if (it->target == target) {it->UserData = ud; break;}
		}
	}

	int MST(unsigned int source, vector<int>& uplink);

	int DFS(unsigned int source, unsigned int dest, list<unsigned int>& path);

	void Print() {
		if (N>26) {
		for (unsigned int i=0; i<N; i++) {
			list<Edge>::iterator it = al[i].begin();
			cout << i << " :";
			for (;it!=al[i].end();it++) cout << it->target << " ";
			cout << endl;
		}
		}
		else {
			for (unsigned int i=0; i<N; i++) {
				list<Edge>::iterator it = al[i].begin();
				cout << char(i + 'A') << " :";
				for (;it!=al[i].end();it++) cout << char(it->target  + 'A')<< " ";
				cout << endl;
			}

		}
	}

	void Clear() {
		for (unsigned int i=0; i<N; i++) { al[i].clear();}
	}

	void PrintUndirected2DotFile(ofstream& co, bool PrintWeights);
	void PrintDirected2DotFile(ofstream& co, bool PrintWeights);
	void PrintUndirectedHypergraph2DotFile(ofstream& co);
	void PrintDirectedHypergraph2DotFile(ofstream& co);
	void SampleIntervalGraph(unsigned int Seed, bool isDirected = false, double lam1 = 0.5, double lam2 = 7.2, double probThin = 0.0, double (*WeightFun)() = NULL);
};


#endif /* GRAPH_H_ */
