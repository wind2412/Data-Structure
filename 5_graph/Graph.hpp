#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <iostream>
#include <vector> 
#include <list>
using namespace std;

//�ڽӱ���ʽ�� ��Ȩ����ͼ. 
class Graph{
public:	//�������public......mdzz....... 
	struct Edge{
		int from;
		int to;
		double weight;	 
		
		Edge(int from, int to, double weight = 1) : from(from), to(to), weight(weight){}; 
		bool operator < (const Edge & e) const{	//��������const��������less<Edge>�����Ƚ�<ʱ�ᱨ������Ϊ������const��������޸ĳ�Ա��!
												//http://www.cppblog.com/cppblogs/archive/2012/09/06/189749.html 
			return this->weight < e.weight;
		}
	}; 
private:
	int V;	//������ 
	int E;	//����
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
