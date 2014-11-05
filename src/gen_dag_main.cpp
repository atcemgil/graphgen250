//============================================================================
// Name        : gen_dag_main.cpp
// Author      : A. Taylan Cemgil
// Description : Random directed graph construction using Interval Graphs
//============================================================================

#include "graph.h"



double l1 = 0.3;
double l2 = 4.2;
double pThin = 0.6;

int main(int argc, char **argv) {
  unsigned int N = 8;
  unsigned int sink = N-1, source = 0;

  int  seed = time(NULL); 

  if (argc>1) N = atoi(argv[1]); 
  if (argc>2) source = atoi(argv[2]);
  if (source>=N) source = 0;

  if (argc>3) sink = atoi(argv[3]);
  if (sink>=N) sink = N-1;

  if (argc>4) seed = atoi(argv[4]);

  Graph g(N);

  bool GenerateDirectedGraph = true;
  bool PrintWeights = false;

  cout << "Seed: " << seed << endl;

  g.SampleIntervalGraph(seed, GenerateDirectedGraph, l1, l2, pThin);
  
  ofstream os;
  string fn("dag.dot");
  string fno("dag_orig.dot");
  
  os.open(fno.c_str());
  g.PrintDirected2DotFile(os, PrintWeights);
    //g.PrintDirectedHypergraph2DotFile(os);
  os.close();
  
  system("dot -Teps dag_orig.dot > dag_orig.eps");
  system("dot -Gsize=35,30 -Tpng dag_orig.dot > dag_orig.png");

  g.Print();

  int found_link;
  list<unsigned int> path;
  found_link = g.DFS(source, sink, path);
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
    
  system("dot -Teps dag.dot > dag.eps");
  system("dot -Gsize=35,30 -Tpng dag.dot > dag.png");

  return 0;
}
