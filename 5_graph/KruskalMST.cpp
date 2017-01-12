#ifndef _KRUSKAL_H_
#define _KRUSKAL_H_
#include <iostream>
#include <vector>
#include "Graph.hpp"
#include "../4_heap/MinHeap.cpp"
#include "../0_union_find/union-find.hpp"
using namespace std;

using Edge = typename Graph::Edge;

//��С������(Minimum Spanning Tree)  Kruskal�㷨	//SedgeWick
class KruskalMST{	//Ѫ�Ľ�ѵ������ʹ�ø�������������ڲ�װ��class�������͡�����ôҲҪʹ��ָ�밡����һ��Ч�ʸߣ���ʡ�ռ䣬
					//�����������MinPQ���ֵ�0��λ�ò����õ�״������Ҫ��һ��Ĭ�϶��󡣡��������û��Ĭ�ϳ�ʼ���캯�����Ǿͱ��ˡ�����
					//����ָ��Ĭ����nullptr������ǧ��Ҫʹ��ָ�밡���� 
private:
	Graph & g;
	MinPQ<Edge*> q;//��Edge��weight����̰�� 
	UnionFind uf;	//��ֹMST����Edge֮��ɻ������� 
	vector<Edge*> v;	//�������й���MST��Edge 
public:
	KruskalMST(Graph & g): g(g), q(g.getE()), uf(g.getV()){
		buildMST(); 
	};
private:
	void buildMST(){
		for(int i = 0; i < g.getV(); i ++){
			for(const Edge & e : g.getAdj(i)){
				q.insert(const_cast<Edge*>(&e));
			}
		}
		while(!q.isEmpty() && v.size() < g.getV() - 1){	//��������������������ȫ���ڵ�������ϣ��Ͳ����ٹ������ı��ˡ� 
			Edge* e = q.getMin(); q.deleteMin();
			if(!uf.connected(e->from, e->to)){
				uf.Union(e->from, e->to);
				v.push_back(e);
			}
		}
	}
public:
	vector<Edge*> getMST(){
		return v;
	} 
}; 

#endif

int main()
{
	Graph g(5);
	g.addEdge(1, 3);
	g.addEdge(1, 4);
	g.addEdge(0, 1);
	g.addEdge(1, 6);
	g.addEdge(1, 3);
	cout << "1's out_degree: "<<g.getDegree(1) << endl;
	g.reverse().print();
	g.print();
	
	KruskalMST k(g);
	vector<Edge*> v = k.getMST();
	cout << "minimum spanning tree: " << endl;
	for(vector<Edge*>::iterator it = v.begin(); it != v.end(); ++it){
		cout << "from: " << (*it)->from << "  to: " << (*it)->to << "  weight: " << (*it)->weight << endl;
	}
}
