#ifndef _GRAPH_IMPL_H_
#define _GRAPH_IMPL_H_
#include <algorithm>

using Edge = typename Graph::Edge;

void Graph::addEdge(int from, int to, double weight){	//����ͼ�� 
	if(from < 0 || from > V || to < 0 || to > V){
		cerr << "illegal arguments! " << endl;
		return;
	}
	if(from == to){
		cerr << "can't add the same point! " << endl;
		return;
	}
	if(find_if(begin(adj[from]), end(adj[from]), [=](const Edge & e){return e.to == to;}) != end(adj[from])){	//Ѱ���Ƿ��Ѿ�����to�� 
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

const list<Edge> & Graph::getAdj(int v){	//������˼����Topological_sort.cpp�У����жԴ˷���ֵfor-eachʱ����ʾ��list�е�ÿ��Edge��������const�ģ����ǲ�����ζ��ʲô�� 
	return adj[v];							//û���뵽��Ȼ�������е�ÿ��Ԫ��Ҳ��const�ģ���д��һ��list<Edge> l = g.getAdj(v);˵��list����const�ģ� 
}

int Graph::getDegree(int v){
	if(v < 0 || v > V){
		cerr << "illegal arguments! " << endl;
	}
	return adj[v].size();
} 

Graph Graph::reverse(){	//�÷��ض���ʱ��һ��Ҫ���ض��󡣲��ܷ���const����Item21. http://harttle.com/2015/08/18/effective-cpp-21.html 
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
