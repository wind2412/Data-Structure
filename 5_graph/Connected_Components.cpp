#ifndef _CC_H_
#define _CC_H_
#include <iostream>
#include <vector>
#include "Graph.hpp"
using namespace std;

//连通分量算法。	类似于并查集。	//from SedgeWick 
class ConnectedComponents{
private:
	Graph & g;
	int count;
	vector<bool> marked;
	vector<int> id;
public:
	ConnectedComponents(Graph & g): g(g), count(0), marked(g.getV()), id(g.getV()){
		for(int i = 0; i < g.getV(); i ++){
			if(!marked[i]){
				dfs(i);
				count ++;	//count放在里边漂亮！！原先放在外边的设计简直差劲！里边只有找到新的连通分量之后才会count++！！ 
			}
//			count++;	//差劲！ 
		}
	}
public:
	void dfs(int v){
		marked[v] = true;
		id[v] = count;
		for(const Edge & e : g.getAdj(v)){
			dfs(e.to);
		}
	}
	vector<int> getId(){
		return id;
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
	
	ConnectedComponents cc(g);
	vector<int> v = cc.getId();
	for(vector<int>::iterator it = v.begin(); it != v.end(); ++it){
		cout << *it << " ";
	}
}
