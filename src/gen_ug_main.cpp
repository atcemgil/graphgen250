//============================================================================
// Name        : gen_ug_main.cpp
// Author      : A. Taylan Cemgil
// Description : Random undirected graphs, using Interval Graphs
//============================================================================

#include "graph.h"


double WeightFun1() {static double z=0.0; return (z+=1.0);};
double WeightFun2() {return int(30*uRand())+1;};

double l1 = 0.3;
double l2 = 5.2;
double pThin = 0.3;



int main(int argc, char **argv) {
  unsigned int N = 8;

  double (*myWeightFun)();
  myWeightFun = WeightFun1;
  int  seed = time(NULL); 

  if (argc>1) N = atoi(argv[1]); 
  if (argc>2) myWeightFun = (atoi(argv[2])==1 ? WeightFun1: WeightFun2);
  if (argc>3) seed = atoi(argv[3]);

  Graph g(N);

  bool PrintWeights = true;
  g.SampleIntervalGraph(seed, false, l1, l2, pThin, myWeightFun);
  
  ofstream os;
  string fn("deneme.dot");
  string fno("deneme_orig.dot");
  
  os.open(fno.c_str());
  g.PrintUndirectedHypergraph2DotFile(os);
  os.close();
  
  system("dot -Teps deneme_orig.dot > deneme_orig.eps");
  system("dot -Gsize=35,30 -Tpng deneme_orig.dot > deneme_orig.png");

  g.Print();
  
  vector<int> uplink;
  g.MST(0, uplink);
  //cout << "Uplink Size" << uplink.size() << endl;
  for (unsigned int i=0;i<uplink.size();i++) {
    if (uplink[i]!=-1) {
      // cout << char(i+'A') << "--" << char(uplink[i]+'A') << endl;
      g.FindAndMarkEdge(uplink[i], i);
      g.FindAndMarkEdge(i, uplink[i]);
    }
  };

  os.open(fn.c_str());
  g.PrintUndirectedHypergraph2DotFile(os);
  os.close();    
  system("dot -Teps deneme.dot > deneme.eps");
  system("dot -Gsize=35,30 -Tpng deneme.dot > deneme.png");
  
  
  return 0;
  
}
