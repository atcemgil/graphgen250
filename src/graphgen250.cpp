//============================================================================
// Name        : graphgen250.cpp
// Author      : A. Taylan Cemgil
// Description : Random graph construction using Interval Graphs
//============================================================================

#include "graph.h"

const double INF = numeric_limits<double>::infinity();
double uRand() {return double(rand())/RAND_MAX; };

struct Event {
	double t;
	unsigned int node;
	bool born;
	Event(double _t=0.0, unsigned int n=0, bool isBorn=true) {t = _t; node = n; born = isBorn;};
	void Print() {cout << t << ":" << node << " " << born << endl;}
};
bool isAfter(Event& a, Event& b) {return a.t > b.t;};

void Graph::SampleIntervalGraph(unsigned int Seed, bool isDirected = false, double lam1 = 0.5, double lam2 = 7.2) {
	double t=0, dt, m;
	double probThin = 0.7;
	vector<Event> L; // Array of events, we will build a heap here
	set<unsigned int> active; // Currently alive nodes in interval graph construction
	Clear();

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
					double w = int(uRand()*20)+1;
					//double w = 1.;
					AddEdge(*it, Edge(e->node, w));
					AddEdge(e->node, Edge(*it, w));
				}
				}
				else {
					double w;
					if (uRand()>probThin) {
						w = int(uRand()*20)+1;
						AddEdge(*it, Edge(e->node, w));
					}
					if (uRand()>probThin) {
						w = int(uRand()*20)+1;
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


int find_nearest_unvisited(vector<bool>& visited, vector<double> D, unsigned int N)
{
	int t = -1;
	double val = INF;
	for (unsigned int i=0;i<N;i++) {
		if (!visited[i]) {
			if (D[i]<val) {val = D[i]; t = i;}
		}
	}
	return t;
}


int Graph::MarkMST(unsigned int source = 0) {
	vector<bool> visited(N);
	vector<int> uplink(N);
	vector<double> D(N);
	unsigned int cur;

	for (unsigned int i=0;i<N;i++) {
		D[i] = INF;
		visited[i] = false;
		uplink[i] = -1;
	};

	D[source] = 0.0;

	while ((cur=find_nearest_unvisited(visited, D, N))!=-1) {
		visited[cur] = true;
		for (list<Edge>::iterator it = al[cur].begin(); it!=al[cur].end(); it++) {
			if (!visited[it->target] && D[it->target]>it->Weight) {
				D[it->target] = it->Weight;
				uplink[it->target] = cur;
			}
		}
	}

	for (unsigned int i=0;i<N;i++) {
		if (uplink[i]!=-1) {
			cout << char(i+'A') << "--" << char(uplink[i]+'A') << endl;
			FindAndMarkEdge(uplink[i], i);
			FindAndMarkEdge(i, uplink[i]);
		}
	};


	return 0;
}

int Graph::DFS(unsigned int root, unsigned int target, list<unsigned int>& path) {
	// Depth first search driver
	// Finds a route from root to target via dfs
	vector<bool> visited(N);
	for (unsigned int i=0; i<N; i++) visited[i]=false;
	visited[root] = true;
	return dfs(root, target, visited, path);
}

int Graph::dfs(unsigned int root, unsigned int& dest, vector<bool>& vis, list<unsigned int>& path) {
	int found_link = -1;
	if (root == dest) {
		path.push_front(root);
		return root;
	};
	for (list<Edge>::iterator it = al[root].begin(); it!=al[root].end(); it++) {
		if (!vis[it->target]) {
				vis[it->target] = true;
				found_link = dfs(it->target, dest, vis, path);
				if (found_link!=-1) {
					path.push_front(root);
					return root;
				}
		}
	}
	return -1;
}

int main() {
	int N = 10;
	Graph g(N);
	bool GenerateDirectedGraph = true;
	bool PrintWeights = false;
	int seed = time(NULL);
	//int seed = 1366468315;
	int found_link;

	cout << "Seed: " << seed << endl;
	g.SampleIntervalGraph(seed, GenerateDirectedGraph);

	ofstream os;
	string fn("deneme.dot");
	string fno("deneme_orig.dot");

	os.open(fno.c_str());
	if (GenerateDirectedGraph) {
		g.PrintDirected2DotFile(os, PrintWeights);
		//g.PrintDirectedHypergraph2DotFile(os);
	}
	else {
		g.PrintUndirectedHypergraph2DotFile(os);
		//g.PrintUndirected2DotFile(os);
	};
	os.close();
	system("dot -Teps deneme_orig.dot > deneme_orig.eps");
	system("dot -Gsize=35,30 -Tpng deneme_orig.dot > deneme_orig.png");

	g.Print();
	list<unsigned int> path;
	found_link = g.DFS(0, N-1, path);
	if (found_link==-1) cout << "No path found" << endl;
	else {
		for (list<unsigned int>::iterator it=path.begin(); it!=path.end(); it++)
			cout << char(*it+'A') << "->";
		cout << endl;
	}


	if (false) {
		g.MarkMST();
		os.open(fn.c_str());
		g.PrintUndirectedHypergraph2DotFile(os);
		//	g.PrintUndirected2DotFile(os);
		os.close();

		system("dot -Teps deneme.dot > deneme.eps");
		system("dot -Gsize=35,30 -Tpng deneme.dot > deneme.png");
	};


	return 0;

}
