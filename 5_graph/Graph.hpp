#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <iostream>
#include <vector> 
#include <list>
using namespace std;

//邻接表形式。 加权有向图. 
class Graph{
public:	//必须设成public......mdzz....... 
	struct Edge{
		int from;
		int to;
		double weight;	 
		
		Edge(int from, int to, double weight = 1) : from(from), to(to), weight(weight){}; 
		bool operator < (const Edge & e) const{	//这里必须加const！！否则less<Edge>做到比较<时会报错！！因为不声明const代表可以修改成员！!
												//http://www.cppblog.com/cppblogs/archive/2012/09/06/189749.html 
			return this->weight < e.weight;
		}
	}; 
private:
	int V;	//顶点数 
	int E;	//边数
	vector<list<Edge>> adj;
	bool directed;
public:
	explicit Graph(int V, bool directed = true): V(V), E(0), adj(V), directed(directed){};
public:
	void addEdge(int from, int to, double weight = 1);
	int getV();
	int getE();
	int getDegree(int v);
	const list<Edge> & getAdj(int v);
	Graph reverse();
public: 
	void print();
};

#include "Graph.cpp"

#endif 
