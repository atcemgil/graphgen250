/*
 * algorithms.cpp
 *
 *  Created on: 26 Apr 2013
 *      Author: cemgil
 */

#include "graph.h"

// Utility for MST, inefficient, need a priority queue here
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


int Graph::MST(unsigned int source, vector<int>& uplink) {
  vector<bool> visited(N);
  vector<double> D(N);
  unsigned int cur;

  uplink.clear();
  uplink.resize(N);

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


  return 0;
}

int Graph::DFS(unsigned int root, unsigned int target, list<unsigned int>& path) {
  // Depth first search driver
  // Finds a route from root to target via dfs
  // Returns -1 if a path is not found
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
