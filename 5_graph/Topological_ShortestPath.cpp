#ifndef _TOPOLOGICAL_SP_H_
#define _TOPOLOGICAL_SP_H_
#include <iostream>
#include <deque>
#include <vector>
#include <climits>
#include "Graph.hpp"
using namespace std;

using Edge = Graph::Edge;

//拓扑排序的顺序计算最短路径。	//和拓扑排序一样，决不能有环。	//SedgeWick 
class Topological_SP{
private:
	Graph & g;
	int count = 0;	//记录加入q的结点次数。如果小于g.getV()即是有环。和Topological_Sort一样。 
	vector<int> indegree;	//结点的入度。由于数组的成员变量初始化太不好使。。。又不想new 
	deque<int> q;	//结点的入度为0的点队列。 
	vector<double> distance; 
public:
	//Topological也可以找单源最短路径！！！虽然比起Dijkstra的只向着s点之后的点遍历，Topological对整个图全都遍历。但是还是可以求的！反正
	//我们需要的只是s以及它能到达的点，s之前（即能到达s但是s到达不了的）可以进行松弛啊。但是松弛的结果，由于只把distance[s]设成0，
	//s之前的distance全是∞，也松弛不了啊。我们根本用不到它们。至于s后面的，也肯定松弛了，（Topological全局松弛）直接取值即可。 
	//————看来上边的想法应该用在Bellman-Ford中。 
	Topological_SP(Graph & g, int s): g(g), indegree(g.getV()), /*q(g.getV()),*/ distance(g.getV(), INT_MAX){
		//【md！！！！！】使用有环的例子测试，发现有环也测不出来。。。一对比拓扑排序，Topological_sort使用的是数组，而Topological_SP使用的deque，
		//重点是它使用了q(g.getV())来初始化！！我还以为能是reverse()的效果。。没想到竟然里边直接出现了5个0......然后再push_back的值就在
		//第6、第7位了。。。所以会先弹出一堆0。。。。用容器千万要谨慎啊！！！woc 
		buildSP(s);
	}
	void buildSP(int s){
		distance[s] = 0;	//不这么处理，接下来都做不了了。。。接下来全是∞，根本没法松弛。。。∞+3==∞。。。 
		Graph && rev = g.reverse();
		for(int i = 0; i < rev.getV(); i ++){
			indegree[i] = rev.getDegree(i);	//保存入度。
			if(indegree[i] == 0){
				q.push_back(i);
				count ++; 
			} 
		} 
		while(!q.empty()){
			int v = q.front(); q.pop_front();	//实际上一开始我想错了。一开始的想法应该用在Bellman-Ford上。Topological并不是对所有松弛。只是
												//对临时pop的点后边元素进行松弛。 
			for(const Edge & e : g.getAdj(v)){
				if(--indegree[e.to] == 0){
					q.push_back(e.to);	//如果邻接值的入度减为0，那就加入q。
					count ++;
				}
				if(distance[v] + e.weight < distance[e.to]){	//松弛。 
					distance[e.to] = distance[v] + e.weight;	
				}
			}
		}
		if(count < g.getV()){
			cerr << "there is a circle in the graph!! topological sort failed! " << endl;
			distance.clear();	//成环就出错，清空distance. 
		}
	}
	vector<double> getDistance(){
		return distance;
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
	cout << "1's out_degree: "<<g.getDegree(1) << endl;
	g.reverse().print();
	g.print();
	
	Topological_SP t(g, 1);
	vector<double> && v = t.getDistance();
	cout << "1到其他点的最短路径如下：" << endl; 
	for(vector<double>::const_iterator it = v.begin(); it != v.end(); ++it){
		if(*it == INT_MAX)	cout << "MAX" << " "; 
		else cout << *it << " ";
	}
}
