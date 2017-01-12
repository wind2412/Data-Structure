#ifndef _BELLMANFORD__SPFA__H_
#define _BELLMANFORD__SPFA__H_
#include <iostream>
#include <climits>
#include <deque> 
#include "Graph.hpp"
using namespace std;

/**
 *Bellman-Ford单源最短路径算法 O(|V|*|E|)	按照边from-to的字典顺序进行g.getV()-1轮轮询松弛 Dijkstra无法进行负权边计算 而
 *Bellman-Ford只要没有负环路即可。
 *SedgeWick的pdf上是如上所说。
 *《数据结构与算法分析——C++语言描述（4th）》给出了Bellman-Ford的队列优化算法SPFA。可以降到O(kE). 绝大多数 k <= 2. 
 *两种方法均予以实现。 
 *实现的伪代码参见wikipedia.  
 *https://zh.wikipedia.org/wiki/%E8%B4%9D%E5%B0%94%E6%9B%BC-%E7%A6%8F%E7%89%B9%E7%AE%97%E6%B3%95 
 */ 
 
class BellmanFordSP{
private:
	Graph & g;
	deque<int> q;	//这里只是一个普通的队列，按照字典顺序出队。没有特殊的作用。
	vector<double> distance;
public:
	BellmanFordSP(Graph & g, int s): g(g), distance(g.getV(), INT_MAX){
		buildSP(s);
	}
	void buildSP(int s){
		//1.初始化图 
		distance[s] = 0;
		q.push_back(s);
		
		//2.重复对每条边进行松弛 
		for(int t = 0; t < g.getV() - 1; t ++){	//g.getV()-1次循环 这样，即使有负权环也会强制在g.getV()-1次退出了。不会无限循环。 
			for(int i = 0; i < g.getV(); i ++){
				for(const Edge & e : g.getAdj(i)){	//此方法不同的是，与Dijkstra和Topological不同，对每条边均进行不断松弛直至完美为止！ 
					if(distance[i] + e.weight < distance[e.to]){
						distance[e.to] = distance[i] + e.weight;
					}
				}
			}
		}
		
		//3.检查是否有负权环 //其实就是看有没有边还能变得更负 
		for(int i = 0; i < g.getV(); i ++){
			for(const Edge & e : g.getAdj(i)){
				if(distance[i] + e.weight < distance[e.to]){	//因为有负权环就会无限重做，因此distance[e.to]还是会持续变小的！
																//因此检查它还会不会继续变小就行了！
																//注意不能检查它是否是负的！因为没准每轮松弛-0.001。。。还是正数也是可能的。 
					cerr << "此图有负权环！！" << endl;
					distance.clear();
					return;
				}
			}
		}
	}
	vector<double> getDistance(){
		return distance;
	}
};

class SPFA{	//https://www.renfei.org/blog/weighted-shortest-path.html
private:
	Graph & g;
	deque<int> q;	//这里只是一个普通的队列，按照字典顺序出队。没有特殊的作用。
	vector<double> distance;
	vector<bool> isInQueue;	//通过设置标志位，能够快速查看某一个结点是否在q中。典型的以空间换时间。
	vector<int> count;	//计入每个结点的入队总次数。由于SPFA，如果能有最短路径，可证明单个结点的总入队次数不会超过g.getV(). 
public:
	SPFA(Graph & g, int s): g(g), distance(g.getV(), INT_MAX), isInQueue(g.getV(), 0), count(g.getV(), 0){
		buildSP(s);
	}
	void buildSP(int s){
		//1.初始化图 
		distance[s] = 0;
		q.push_back(s);
		isInQueue[s] = true;
		count[s] ++;
		
		//2.队列优化
		while(!q.empty()){
			int v = q.front(); q.pop_front();	//这一块和BFS差不多 
			isInQueue[v] = false;	//count[]不能减小 因为记录入队总次数 
			for(const Edge & e : g.getAdj(v)){
				if(distance[v] + e.weight < distance[e.to]){
					distance[e.to] = distance[v] + e.weight;	//松弛 
				}
				if(!isInQueue[e.to]){
					q.push_back(e.to);
					isInQueue[e.to] = true; 
					if(++count[e.to] >= g.getV()){
						cerr << "此图有负权环！！" << endl;
						distance.clear();
						return;
					}
				}
			}
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
	g.addEdge(4, 1, -1);	//spfa发现bug。 
	cout << "1's out_degree: "<<g.getDegree(1) << endl;
	g.reverse().print();
	g.print();
	
	BellmanFordSP b(g, 4);
	vector<double> && v = b.getDistance();
	cout << "1到其他点的最短路径如下：" << endl; 
	for(vector<double>::const_iterator it = v.begin(); it != v.end(); ++it){
		if(*it == INT_MAX)	cout << "MAX" << " "; 
		else cout << *it << " ";
	}
	cout << endl << endl;
	
	SPFA spfa(g, 1);
	vector<double> && v2 = b.getDistance();
	cout << "1到其他点的最短路径如下：" << endl; 
	for(vector<double>::const_iterator it = v2.begin(); it != v2.end(); ++it){
		if(*it == INT_MAX)	cout << "MAX" << " "; 
		else cout << *it << " ";
	}
}
