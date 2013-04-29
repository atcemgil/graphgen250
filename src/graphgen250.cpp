//============================================================================
// Name        : graphgen250.cpp
// Author      : A. Taylan Cemgil
// Description : Random graph construction using Interval Graphs
//============================================================================

#include "graph.h"

int main() {
	int N = 20;
	Graph g(N);
	bool GenerateDirectedGraph = true;
	int seed = time(NULL);
	//int seed = 1366468315;

	cout << "Seed: " << seed << endl;
	g.SampleIntervalGraph(seed, GenerateDirectedGraph);

	ofstream os;
	string fn("deneme.dot");
	string fno("deneme_orig.dot");

	bool PrintWeights = true;
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

	int found_link;
	list<unsigned int> path;
	found_link = g.DFS(0, N-1, path);
	if (found_link==-1) cout << "No path found" << endl;
	else {
		unsigned int last; bool last_valid = false;
		for (list<unsigned int>::iterator it=path.begin(); it!=path.end(); it++) {
			cout << char(*it+'A') << "->";
			if (last_valid) {
				g.FindAndMarkEdge(last, *it);
			}
			last_valid = true;
			last = *it;
		}
		cout << endl;
	}
	os.open(fn.c_str());
	// g.PrintUndirectedHypergraph2DotFile(os);
	g.PrintDirected2DotFile(os, PrintWeights);
	os.close();

	system("dot -Teps deneme.dot > deneme.eps");
	system("dot -Gsize=35,30 -Tpng deneme.dot > deneme.png");


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
