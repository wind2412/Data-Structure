#ifndef _KOSARAJU_SCC_H_
#define _KOSARAJU_SCC_H_
#include <iostream>
#include "Graph.hpp"
#include <stack>
#include <vector>
using namespace std;

/**
 *	Kosaraju强连通分量算法。
 *  利用了一个图即使reverse了，和原图还是具有相同的强连通分量的性质！
 *	非常通俗易懂。ACM之家blog：http://www.acmerblog.com/strongly-connected-components-6099.html
 *	有一个图特别易懂。
 * 
 *  算法步骤：
 *	1.对所有的结点进行DFS深度遍历。mark所有去过的点。在访问一个点v结束时，把v加入stack中。 
 *	2.得到图g的reverse版本。然后把stack不断弹出，以反序的形式在反序图上DFS遍历每个访问过的点。然后顺便union-find加到id数组中。 
 *  
 *  使用stack是因为，在g图的源点会变成终点。 如果不用stack反序，那在反序图上顺序遍历，0~g.getV()一开始的点全变成终点了。 
 *
 */

class KosarajuSCC{
private:
	Graph & g;
	Graph && rev;
	vector<bool> marked;
	vector<int> id;	//union-find并查集
	stack<int> s; 
	int count; //并查集个数。即强连通分量的个数。 
public:
	KosarajuSCC(Graph & g): g(g), rev(g.reverse()), marked(g.getV(), 0), id(g.getV(), 0), count(0){buildSCC();};
	void buildSCC(){
		for(int i = 0; i < g.getV(); i ++){
			if(!marked[i]){
				dfsOrigin(i);
			}
		}
		marked.assign(g.getV(), 0); //归零marked
		while(!s.empty()){
			int v = s.top(); s.pop();
			if(!marked[v]){
				dfsReverse(v);
				count ++;
			}
		} 
	}
	void dfsOrigin(int v){	//对原图进行dfs 
		marked[v] = true;
		s.push(v);	//加入栈 
		for(const Edge & e : g.getAdj(v)){
			if(!marked[e.to]){
				dfsOrigin(e.to);
			}
		}
	}
	void dfsReverse(int v){	//对reverse图进行dfs 
		marked[v] = true;
		for(const Edge & e : rev.getAdj(v)){
			if(!marked[e.to]){
				dfsReverse(e.to);
			}
		}
		id[v] = count;
	}
	vector<int> getId(){
		return id;
	}
};

#endif

int main()
{
	Graph g(5);
	g.addEdge(1, 3, 1.1);
	g.addEdge(1, 4, 3.7);
	g.addEdge(0, 1, 5.1);
	g.addEdge(1, 6, 0.8);
	g.addEdge(3, 4, 1.5); 
	g.addEdge(4, 1, -10);
	cout << "1's out_degree: "<<g.getDegree(1) << endl;
	g.reverse().print();
	g.print();
	
	KosarajuSCC k(g);
	vector<int> && v = k.getId();
	for(vector<int>::iterator it = v.begin(); it != v.end(); ++it){
		cout << *it << " ";
	}
}
