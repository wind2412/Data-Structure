#ifndef _GRAPH_IMPL_H_
#define _GRAPH_IMPL_H_
#include <algorithm>

using Edge = typename Graph::Edge;

void Graph::addEdge(int from, int to, double weight){	//有向图！ 
	if(from < 0 || from > V || to < 0 || to > V){
		cerr << "illegal arguments! " << endl;
		return;
	}
	if(from == to){
		cerr << "can't add the same point! " << endl;
		return;
	}
	if(find_if(begin(adj[from]), end(adj[from]), [=](const Edge & e){return e.to == to;}) != end(adj[from])){	//寻找是否已经存在to点 
		cerr << "the \"to\" vertex has been existed and its value is " << to << endl;
		return;
	}
	adj[from].push_front(Edge(from, to, weight));
	if(!directed){
		adj[to].push_front(Edge(to, from, weight));
		E ++;
	}
	E ++;
}

int Graph::getV(){
	return V;
}

int Graph::getE(){
	return E;
}

const list<Edge> & Graph::getAdj(int v){	//很有意思。在Topological_sort.cpp中，进行对此返回值for-each时，提示我list中的每个Edge的类型是const的！这是不是意味着什么？ 
	return adj[v];							//没有想到竟然是容器中的每个元素也是const的？而写了一句list<Edge> l = g.getAdj(v);说明list不是const的？ 
}

int Graph::getDegree(int v){
	if(v < 0 || v > V){
		cerr << "illegal arguments! " << endl;
	}
	return adj[v].size();
} 

Graph Graph::reverse(){	//该返回对象时候一定要返回对象。不能返回const＆！Item21. http://harttle.com/2015/08/18/effective-cpp-21.html 
	if(!directed)	return *this;
	Graph rev(V);
	for(vector<list<Edge>>::size_type i = 0; i < adj.size(); i ++){
		for(auto & e : adj[i]){
			rev.addEdge(e.to, i, e.weight);
		}
	}
	return rev; 
}

void Graph::print(){
	cout << "*********************************" << endl;
	for(vector<list<int>>::size_type i = 0; i < adj.size(); i ++){
		cout << i << "->   " ;
		for(Edge & e : adj[i]){
			cout << e.to << "(" << e.weight << ")" << " "; 
		}
		cout << endl;
	}
	cout << "*********************************" << endl;
}

#endif

//int main()	//for test
//{
//	Graph g(5, false);
//	g.addEdge(1, 3);
//	g.addEdge(1, 4);
//	g.addEdge(0, 1);
//	g.addEdge(1, 6);
//	g.addEdge(1, 3);
//	cout << "1's out_degree: "<<g.getDegree(1) << endl;
//	g.reverse().print();
//	g.print();
//}
