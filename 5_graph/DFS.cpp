#ifndef _DFS_H_
#define _DFS_H_
#include "Graph.hpp"
#include <deque> 

//深度优先搜索。搜索无权有向图的最短路径。注意一定是无权或者权相同！因为遍历一次marked[]标记为true之后，下一次找到的路径
//即使比这次短，由于marked已经标记了，也不会再访问该点了。因此只适用于【无权有向图】！！ 
class DFS{	//【可惜。。。并没有想出静态工长模式应该怎么用在这里。。。。】【以后一定要好好想这里！！】 
private:
	Graph g;
	deque<bool> marked;	//因为初始化的时候不确定长度，bitset无法动态初始化，而vector<bool>是非标准话容器，故而使用deque<bool> 
	vector<int> distance;
public:
	DFS(Graph & g, int v): g(g), marked(g.getV()), distance(g.getV()){
		if(v < 0 || v > g.getV() - 1){
			cerr << "illegal argument of v！" << endl;
			return;
		}
		dfs(v, 0);
	} 
	void dfs(int v, int hopNum){	//得到v到所有其他点的【无权】路径长！！ 	//hop:跳数。 
		distance[v] = hopNum;	//写在前边也同样漂亮！！ 
		marked[v] = true;	//放到前边漂亮！！我一开始放到for循环中间。。。简直是错误的设计。。。。【***重点***】 
		for(const Edge & e : g.getAdj(v)){
			if(!marked[e.to]){
				dfs(e.to, hopNum+1);	//注意！！千万注意！！这里要写成hopNum + 1	！！！千万不是++hopNum ！！！由于是递归！那样会真的改变hopNum值！！			
			}
		}
	}
	vector<int> getDistance(){
		return distance;
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
	g.print();
	g.reverse().print();
	
	DFS dfs(g, 1);	//1能通向哪？
	for(int & i : dfs.getDistance()){
		cout << i << " ";
	} 
	cout << endl;
}
