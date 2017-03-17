#ifndef _TOPOLOGICAL_SORT_
#define _TOPOLOGICAL_SORT_
#include "Graph.hpp"
#include <queue> 

/**
 * 拓扑排序：   使用邻接表的复杂度：O(|E|+|V|) 但是我的程序中因为有reverse()，因此还会变大。算法分析不太会，需要学习。 
 * 1.设置一个队列q。
 * 2.遍历一次，找到所有入度为0的点，顺序加入队列q。
 * 3.出队一个值（删除一个入度==0的点），对于这个出队值，进行广度搜索临接值。对于每个邻接值，让他们的入度虚拟减一（即在indegree表中-1）
 * 4.别忘了把刚才那个出队值加入代表排序顺序的新队列sorted中。如果有哪一个邻接值的入度变成了0，那就继续顺序填入queue中去。 
 * 5.重复3＆4.  直到没有任何入度为0的值加入队列。即：q.empty()发生.
 * 6.检测sorted，如果sorted.size() == V，即等于所有节点数，那就拉倒。如果!=，那就说明一定有环！因为环的入度始终!=0 ！！因此永远无法加入q！！
 * 7.如果是有环图，拓扑排序无法正常工作。这样的话，直接抛异常。 
 */ 
class Topological{
public:
	Topological() = delete;
	static deque<int> sort(Graph & g){
		deque<int> q, sorted; //q储存入度为0的顶点下标。sorted存储q.push_front()之后的拓扑序列。 
		int indegree[g.getV()];	//入度列表 //拓扑排序本来就是根据一轮一轮减少入度实现的。 
		Graph && rev = g.reverse();	//反向。把所有[出度]全部转化为[入度]。 
		for(int i = 0; i < g.getV(); i ++){
			indegree[i] = rev.getDegree(i);	//存入入度的值。	//为什么要单独开辟空间存入度值而不是直接get list.size()呢？因为最后会修改入度值，每轮-1。 
			cout << i << "'s indegree is " << indegree[i] << endl;
			if(indegree[i] == 0){
				q.push_back(i);	//如果是0，就把结点push进q中！ 
			}
		}	
		while(!q.empty()){	//如果查了一圈发现所有入度都>0。。。那真是呵呵了。。源点在哪呢。。直接定成有环。。 
			int v = q.front();q.pop_front();
			sorted.push_back(v);	//加入sorted中，已经有序。 
//			list<Edge> l = g.getAdj(v);	// 【卧槽？？参加Graph.hpp。返回const的list<Edge>，结果list不是const的，这句没报错，而Edge却是const的？？ 
			for(const Edge & e : g.getAdj(v)){
				if(--indegree[e.to] == 0){	//如果邻接值的入度减为0，那就加入q。注意是从indegree[]中减去，不是真的减掉了入度。 
					q.push_back(e.to);
				}
			}
		}
		if(sorted.size() != g.getV()){
			cerr << "there is a circle in the graph!! topological sort failed! " << endl;
			return deque<int>{};	//返回一个啥也没有的queue 
		}
		return sorted;
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
	g.addEdge(4, 1);
	cout << "1's out_degree: "<<g.getDegree(1) << endl;
	g.print();
	g.reverse().print();
	
	deque<int> && sorted = Topological::sort(g);	//失误。。应该用deque。。。queue不是标准STL，不提供迭代器遍历。。。 
	for(int & i : sorted){
		cout << i << " ";
	}
	cout << endl;
}
