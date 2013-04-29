/*
 * dot_output.cpp
 *
 *  Created on: 26 Apr 2013
 *      Author: cemgil
 */

#include "graph.h"

void Graph::PrintUndirected2DotFile(ofstream& co, bool PrintWeights = false) {
		co << "graph D {" <<endl;
		co << "size=\"3,3\"" <<endl;
		co << "rankdir = \"LR\"" <<endl;
		co << "overlap=\"false\"" <<endl;
		co << "sep=\"0\"" <<endl;
		co << "edge[style=\"bold\",color=\"black\"]" <<endl;
		co << "node[shape=\"circle\"]" <<endl;

		for (unsigned int i=0;i<N;i++) {
			for (list<Edge>::iterator jt=al[i].begin(); jt!=al[i].end();jt++)
				if (PrintWeights) {if (i<(jt->target)) co << char(i+'A') << "--" << char(jt->target+'A') << "[label=\"" << jt->Weight << "\"];" << endl;}
				else {if (i<(jt->target)) co << char(i+'A') << "--" << char(jt->target+'A') << ";" << endl;}
		}
		co << "}" <<endl;
	}

	void Graph::PrintDirected2DotFile(ofstream& co, bool PrintWeights = false) {
		co << "digraph D {" <<endl;
		co << "size=\"3,3\"" <<endl;
		co << "rankdir = \"LR\"" <<endl;
		co << "overlap=\"false\"" <<endl;
		co << "sep=\"0\"" <<endl;
		co << "edge[style=\"bold\",color=\"black\"]" <<endl;
		co << "node[shape=\"circle\"]" <<endl;

		for (unsigned int i=0;i<N;i++) {
			for (list<Edge>::iterator jt=al[i].begin(); jt!=al[i].end();jt++)
				if (PrintWeights) {
					co << char(i+'A') << "->"
					   << char(jt->target+'A')
					   << "[label=\"" << jt->Weight << "\""
					   << ((jt->UserData==1)? ", color=red, penwidth = 5.0" : "")
					   << "];" << endl;}
				else {co << char(i+'A') << "->" << char(jt->target+'A') << ((jt->UserData==1)? " [color=red, penwidth = 5.0];" : ";") << endl;}
		}
		co << "}" <<endl;
	}

	void Graph::PrintUndirectedHypergraph2DotFile(ofstream& co) {
		co << "graph D {" <<endl;
		co << "size=\"3,3\"" <<endl;
		co << "rankdir = \"LR\"" <<endl;
		co << "overlap=\"false\"" <<endl;
		co << "sep=\"0\"" <<endl;
		co << "edge[style=\"bold\",color=\"black\"]" <<endl;
		co << "node[shape=\"circle\"]" <<endl;

		int ec=0;
		for (unsigned int i=0;i<N;i++) {
			for (list<Edge>::iterator jt=al[i].begin(); jt!=al[i].end();jt++)
				if (i<(jt->target)) {
					if (jt->UserData!=1) {
						co << "Edge" << ec << " [height=.01, width=0.01, shape=none, label=\"" << jt->Weight << "\"];" << endl;
					}
					else {
						co << "Edge" << ec << " [height=.01, width=0.01, shape=box, label=\"" << jt->Weight << "\"];" << endl;
					}

					if (N>26) {
						if (jt->UserData==1) {
							co << "V" << i+1 << " -- " << " Edge" << ec << " [penwidth=5.0]" << endl;
							co << " Edge" << ec << " -- " << "V" << jt->target +1 << " [penwidth =5.0]" << endl;
						}
						else {
							co << "V" << i+1 << " -- " << " Edge" << ec << endl;
							co << " Edge" << ec << " -- " << "V" << jt->target +1 << endl;
						}
					}
					else {
						co << char(i + 'A') << " -- " << " Edge" << ec << ((jt->UserData==1)? " [color=red, penwidth = 5.0];" : ";") << endl;
						co << " Edge" << ec << " -- " << char(jt->target+'A') << ((jt->UserData==1)? " [color=red, penwidth = 5.0];" : ";") << endl;
					}
					ec++;
				}
		}
		co << "}" <<endl;
	}


	void Graph::PrintDirectedHypergraph2DotFile(ofstream& co) {
		co << "digraph D {" <<endl;
		co << "size=\"3,3\"" <<endl;
		co << "rankdir = \"LR\"" <<endl;
		co << "overlap=\"false\"" <<endl;
		co << "sep=\"0\"" <<endl;
		co << "edge[style=\"bold\",color=\"black\"]" <<endl;
		co << "node[shape=\"circle\"]" <<endl;

		int ec=0;
		for (unsigned int i=0;i<N;i++) {
			for (list<Edge>::iterator jt=al[i].begin(); jt!=al[i].end();jt++)
			{
					if (jt->UserData!=1) {
						co << "Edge" << ec << " [height=.01, width=0.01, shape=none, label=\"" << jt->Weight << "\"];" << endl;
					}
					else {
						co << "Edge" << ec << " [height=.01, width=0.01, shape=box, label=\"" << jt->Weight << "\"];" << endl;
					}

					if (N>26) {
						if (jt->UserData==1) {
							co << "V" << i+1 << " - " << " Edge" << ec << " [penwidth=5.0]" << endl;
							co << " Edge" << ec << " -> " << "V" << jt->target +1 << " [penwidth =5.0]" << endl;
						}
						else {
							co << "V" << i+1 << " - " << " Edge" << ec << endl;
							co << " Edge" << ec << " -> " << "V" << jt->target +1 << endl;
						}
					}
					else {
						co << char(i + 'A') << " -> " << " Edge" << ec << ((jt->UserData==1)? " [color=red, penwidth = 5.0];" : ";") << endl;
						co << " Edge" << ec << " -> " << char(jt->target+'A') << ((jt->UserData==1)? " [color=red, penwidth = 5.0];" : ";") << endl;
					}
					ec++;
			}
		}
		co << "}" <<endl;
	}
