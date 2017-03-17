#ifndef _PRIM_MST_H_
#define _PRIM_MST_H_
#include <iostream>
#include <vector>
#include "Graph.hpp"
#include "../4_heap/MinHeap.cpp"
#include "../0_union_find/union-find.hpp"
using namespace std;

using Edge = typename Graph::Edge;

template <typename EdgePointer> 
class Less{
public:
	bool operator()(EdgePointer & e1, EdgePointer & e2){
		return *e1 < * e2;
	} 
};

/**
 * Prim算法和Dijkstra算法的思想很像。
 * 但是有所不同的是：
 * Prim算法    MinPQ比较的是各边权值的大小，并sort。（每条Edge的weight做比较） 
 * Dijkstra算法MinPQ比较单源点s到各点的路径权值大小，并sort。 （s到每点经过所有Edge的weight之和：distance做比较） 
 */ 
class PrimMST{	//SedgeWick LazyPrim_Implementation
private:
	Graph & g;
	MinPQ<Edge*, Less<Edge*>> q;
	vector<Edge*> v;	//存入的是边，本来共有g.getV()个顶点，因此内部应该存有g.getV()-1条边。 
	vector<bool> marked;	//只有0和1两个选项的并查集。最终所有点全是true，将会全部变成一个并查集。 
public:
	PrimMST(Graph & g): g(g), q(g.getE()), marked(g.getV(), 0){
		buildMST();
	}
private:
	void buildMST(){ 	//其实Kruskal得到的也是一个最小生成树森林。最小生成树数量>=1。 
		for(int i = 0; i < g.getV(); i ++){	//外边的for循环是为了防止有多个连通域而设定的。得到最小生成树的森林。 
			if(!marked[i]){	//里边的代码一次执行完毕就会产生一个最小生成树。 
				scan(i);
				while(!q.isEmpty()){
					Edge* e = q.getMin(); q.deleteMin();	//为什么to要检查是否mark呢。因为pop出的边有可能不是此v点的邻边。可能是以前加入的边，由于weight较小从而被弹出。 
					if(marked[e->to])	continue;	//和from在一个并查集中， 跳过。（from必然是marked的） 
					else {
						v.push_back(e);	//实现与SedgeWick不同，因为API所致。他的API的Edge.either() other()是随机获取某个端点，和这里的不同。 
						scan(e->to);	
					}
				}
			}
		}
	}
	void scan(int v){	//把v标记为true并把g.getAdj(v)全加入q。当然，如果已经是同一个并查集就不加入了。 
		marked[v] = true;
		for(const Edge & e : g.getAdj(v)){
			if(!marked[e.to]){	//多了一轮判断	相当于并查集。 
				q.insert(const_cast<Edge*>(&e));
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
	Graph g(5, false);
	g.addEdge(1, 3);
	g.addEdge(1, 4);
	g.addEdge(0, 1);
	g.addEdge(1, 6);
	g.addEdge(1, 3);
	cout << "1's out_degree: "<<g.getDegree(1) << endl;
	g.reverse().print();
	g.print();
	
	PrimMST p(g);
	vector<Edge*> v = p.getMST();
	cout << "minimum spanning tree: " << endl;
	for(vector<Edge*>::iterator it = v.begin(); it != v.end(); ++it){
		cout << "from: " << (*it)->from << "  to: " << (*it)->to << "  weight: " << (*it)->weight << endl;
	}
}
