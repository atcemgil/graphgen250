//============================================================================
// Name        : graphgen250.cpp
// Author      : A. Taylan Cemgil
// Description : Random graph construction using Interval Graphs
//============================================================================

#include "graph.h"

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
		vector<int> uplink;
		g.MST(0, uplink);

		for (unsigned int i=0;i<uplink.size();i++) {
			if (uplink[i]!=-1) {
				cout << char(i+'A') << "--" << char(uplink[i]+'A') << endl;
				g.FindAndMarkEdge(uplink[i], i);
				g.FindAndMarkEdge(i, uplink[i]);
			}
		};


		os.open(fn.c_str());
		g.PrintUndirectedHypergraph2DotFile(os);
		//	g.PrintUndirected2DotFile(os);
		os.close();

		system("dot -Teps deneme.dot > deneme.eps");
		system("dot -Gsize=35,30 -Tpng deneme.dot > deneme.png");
	};


	return 0;

}
