#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_
#include "Graph.hpp"
#include "../4_heap/MinHeap.cpp"
#include <climits>	//�ҳ�int���ֵ�ĺ꣺ #define _I16_MAX 32767 
#include <functional>

/**
 * Dijkstra�㷨��	�����Ȩͼ�������޸�Ȩ�����Գɻ���	��̶����v�ĵ���������������·������Ȩ��Ϊ·�����ȣ���
 * 1.�����q������㡣���Ѿ���s = 0����distance�� 
 * 2.����һ����s����Ȼ����һ��һ�������s����
 * 3.����s������adj��Edge����Edge.to�����ɳڲ�����weight(s->s) + weight(s->to) < weight(s->to) �����distance[Edge.to].
 * 4.�ظ�3 ֱ��q.emptyΪֹ�� 
 */
class Dijkstra{	//û�뵽 д�����Dijkstra���������ջ����ľ�Ȼ�ǲ������ģʽ����������Ϊ����ƱȽ�����ʱ�������˲����鷳��������Ȥ������ 
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
	Less l;	//���ܰ�l��qֱ�ӳ�ʼ������ΪlҪ��*this��ֻ�г�ʼ���б�ִ��֮ʱ�Ż���this����Ĳ���������˱���Ҫ�ó�ʼ���б��� 
	MinPQ<int, Less> q;	//�ڶ���������priority_queue�ײ�ʹ��ʲô����������priority_queue. //�������ñȽ����ˡ�C++������<���ء����Ƚ�������ʵ�ڼ��Ѱ��� 
	vector<double> distance;
public:
	bool compare(int v1, int v2){
		return distance[v1] < distance[v2];
	}
public:
	Dijkstra(Graph & g, int v): g(g), l(*this), q(l), distance(g.getV(), INT_MAX){
		if(v < 0 || v > g.getV() - 1){
			cerr << "illegal argument of v��" << endl;
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
			v = q.getMin(); q.deleteMin();	//ʹ��Ŀǰ��v������̵ĵ�Ը�������ɳڡ� 
			for(const Edge & e : g.getAdj(v)){	//�޸ĳ�for(Edge e: g.getAdj(v))ͬ����������q.top()���е�ע�Ͱɡ��������޸�֮����������Ҫ����ȡ����ռ�����ڴ氡���� ��˲������޸ġ� 
				if(distance[v] + e.weight < distance[e.to]){	//�ɳڡ� 
					distance[e.to] = distance[v] + e.weight;
					int index = q.getIndex(e.to);	//�õ�minPQ��from��λ��
					q.changeValue(index, e.to);	//�����Լ�ʵ�ֵ�API���������index�±��ϵ�ֵҲ��e.to����˲����ı�value��ֻ�������index�ϸ�/�³��ˡ� 
				}								//ע�������less<T>��Ҫ�����<���أ���������<ʱ������const��������������error �� passing " "as" " discards qualifiers��
												//���http://www.cppblog.com/cppblogs/archive/2012/09/06/189749.html 
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
	cout << "1������������·�����£�" << endl; 
	for(vector<double>::const_iterator it = v.begin(); it != v.end(); ++it){
		if(*it == INT_MAX)	cout << "MAX" << " "; 
		else cout << *it << " ";
	}
}
