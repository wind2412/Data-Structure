#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_
#include "Graph.hpp"
#include "../4_heap/MinHeap.cpp"
#include <climits>	//找出int最大值的宏： #define _I16_MAX 32767 
#include <functional>

/**
 * Dijkstra算法。	有向加权图，必须无负权，可以成环。	求固定结点v的到所有其他点的最短路径（以权重为路径长度）。
 * 1.入队列q所有起点。并把距离s = 0加入distance。 
 * 2.弹出一个点s。当然，第一次一定是起点s咯。
 * 3.对于s的所有adj的Edge，对Edge.to进行松弛操作。weight(s->s) + weight(s->to) < weight(s->to) 则更新distance[Edge.to].
 * 4.重复3 直到q.empty为止。 
 */
class Dijkstra{	//没想到 写完这个Dijkstra。。。我收获最大的竟然是策略设计模式。。。。因为在设计比较器的时候遇到了不少麻烦。。。有趣。。。 
private:
	class Less{
	private:
		Dijkstra & d;
	public:
		Less(Dijkstra & d): d(d){};
		bool operator()(int v1, int v2){
			return d.compare(v1, v2);
		}
	};
private:
	Graph & g;
	Less l;	//不能把l和q直接初始化！因为l要用*this，只有初始化列表执行之时才会有this对象的产生！！因此必须要用初始化列表！！ 
	MinPQ<int, Less> q;	//第二个参数是priority_queue底层使用什么容器来构建priority_queue. //唉。不用比较器了。C++自适配<重载。传比较器函数实在艰难啊。 
	vector<double> distance;
public:
	bool compare(int v1, int v2){
		return distance[v1] < distance[v2];
	}
public:
	Dijkstra(Graph & g, int v): g(g), l(*this), q(l), distance(g.getV(), INT_MAX){
		if(v < 0 || v > g.getV() - 1){
			cerr << "illegal argument of v！" << endl;
			return;
		}
		dijkstra(v);
	}
	void dijkstra(int v){
		distance[v] = 0;
		for(int i = 0; i < g.getV(); i ++){
			q.insert(i);
		}
		
		while(!q.isEmpty()){
			v = q.getMin(); q.deleteMin();	//使用目前与v距离最短的点对各点进行松弛。 
			for(const Edge & e : g.getAdj(v)){	//修改成for(Edge e: g.getAdj(v))同样成立。见q.top()那行的注释吧。【就是修改之后整个对象都要复制取出，占用了内存啊。】 因此不建议修改。 
				if(distance[v] + e.weight < distance[e.to]){	//松弛。 
					distance[e.to] = distance[v] + e.weight;
					int index = q.getIndex(e.to);	//得到minPQ中from的位置
					// q.changeValue(index, e.to);	//由于自己实现的API需求，这里的index下标上的值也是e.to。因此并不改变value，只是让这个index上浮/下沉了。
					q.upfloat(index);	// 这样更好！！
				}								//注意这里！！less<T>需要运算符<重载，但是重载<时必须标记const函数声明！否则error ： passing " "as" " discards qualifiers！
												//详见http://www.cppblog.com/cppblogs/archive/2012/09/06/189749.html 
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
	cout << "1's out_degree: "<<g.getDegree(1) << endl;
	g.reverse().print();
	g.print();
	
	Dijkstra d(g, 1);
	vector<double> && v = d.getDistance();
	cout << "1到其他点的最短路径如下：" << endl; 
	for(vector<double>::const_iterator it = v.begin(); it != v.end(); ++it){
		if(*it == INT_MAX)	cout << "MAX" << " "; 
		else cout << *it << " ";
	}
}
