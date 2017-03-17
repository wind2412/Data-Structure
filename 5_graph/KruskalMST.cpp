#ifndef _KRUSKAL_H_
#define _KRUSKAL_H_
#include <iostream>
#include <vector>
#include "Graph.hpp"
#include "../4_heap/MinHeap.cpp"
#include "../0_union_find/union-find.hpp"
using namespace std;

using Edge = typename Graph::Edge;

//最小生成树(Minimum Spanning Tree)  Kruskal算法	//SedgeWick
class KruskalMST{	//血的教训。。。使用各种容器，如果内部装有class复合类型。。怎么也要使用指针啊！！一是效率高，节省空间，
					//二是如果像是MinPQ这种第0个位置不可用的状况，就要造一个默认对象。。如果对象没有默认初始构造函数，那就崩了。。。
					//但是指针默认是nullptr，所以千万要使用指针啊！！ 
private:
	Graph & g;
	MinPQ<Edge*> q;//对Edge的weight排序，贪心 
	UnionFind uf;	//防止MST连接Edge之后成环的现象 
	vector<Edge*> v;	//保存所有构成MST的Edge 
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
		while(!q.isEmpty() && v.size() < g.getV() - 1){	//结束条件！！还可以是全部节点生成完毕，就不用再管其他的边了。 
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
