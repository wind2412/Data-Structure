#ifndef _PRIM_MST_H_
#define _PRIM_MST_H_
#include <iostream>
#include <vector>
#include "Graph.hpp"
#include "../4_heap/MinHeap.cpp"
#include "../0_union_find/union-find.hpp"
using namespace std;

using Edge = typename Graph::Edge;

template <typename EdgePointer> 
class Less{
public:
	bool operator()(EdgePointer & e1, EdgePointer & e2){
		return *e1 < * e2;
	} 
};

/**
 * Prim�㷨��Dijkstra�㷨��˼�����
 * ����������ͬ���ǣ�
 * Prim�㷨    MinPQ�Ƚϵ��Ǹ���Ȩֵ�Ĵ�С����sort����ÿ��Edge��weight���Ƚϣ� 
 * Dijkstra�㷨MinPQ�Ƚϵ�Դ��s�������·��Ȩֵ��С����sort�� ��s��ÿ�㾭������Edge��weight֮�ͣ�distance���Ƚϣ� 
 */ 
class PrimMST{	//SedgeWick LazyPrim_Implementation
private:
	Graph & g;
	MinPQ<Edge*, Less<Edge*>> q;
	vector<Edge*> v;	//������Ǳߣ���������g.getV()�����㣬����ڲ�Ӧ�ô���g.getV()-1���ߡ� 
	vector<bool> marked;	//ֻ��0��1����ѡ��Ĳ��鼯���������е�ȫ��true������ȫ�����һ�����鼯�� 
public:
	PrimMST(Graph & g): g(g), q(g.getE()), marked(g.getV(), 0){
		buildMST();
	}
private:
	void buildMST(){ 	//��ʵKruskal�õ���Ҳ��һ����С������ɭ�֡���С����������>=1�� 
		for(int i = 0; i < g.getV(); i ++){	//��ߵ�forѭ����Ϊ�˷�ֹ�ж����ͨ����趨�ġ��õ���С��������ɭ�֡� 
			if(!marked[i]){	//��ߵĴ���һ��ִ����Ͼͻ����һ����С�������� 
				scan(i);
				while(!q.isEmpty()){
					Edge* e = q.getMin(); q.deleteMin();	//ΪʲôtoҪ����Ƿ�mark�ء���Ϊpop���ı��п��ܲ��Ǵ�v����ڱߡ���������ǰ����ıߣ�����weight��С�Ӷ��������� 
					if(marked[e->to])	continue;	//��from��һ�����鼯�У� ��������from��Ȼ��marked�ģ� 
					else {
						v.push_back(e);	//ʵ����SedgeWick��ͬ����ΪAPI���¡�����API��Edge.either() other()�������ȡĳ���˵㣬������Ĳ�ͬ�� 
						scan(e->to);	
					}
				}
			}
		}
	}
	void scan(int v){	//��v���Ϊtrue����g.getAdj(v)ȫ����q����Ȼ������Ѿ���ͬһ�����鼯�Ͳ������ˡ� 
		marked[v] = true;
		for(const Edge & e : g.getAdj(v)){
			if(!marked[e.to]){	//����һ���ж�	�൱�ڲ��鼯�� 
				q.insert(const_cast<Edge*>(&e));
			}
		}
	}
public:
	vector<Edge*> getMST(){
		return v;
	} 
};

#endif

int main()
{
	Graph g(5, false);
	g.addEdge(1, 3);
	g.addEdge(1, 4);
	g.addEdge(0, 1);
	g.addEdge(1, 6);
	g.addEdge(1, 3);
	cout << "1's out_degree: "<<g.getDegree(1) << endl;
	g.reverse().print();
	g.print();
	
	PrimMST p(g);
	vector<Edge*> v = p.getMST();
	cout << "minimum spanning tree: " << endl;
	for(vector<Edge*>::iterator it = v.begin(); it != v.end(); ++it){
		cout << "from: " << (*it)->from << "  to: " << (*it)->to << "  weight: " << (*it)->weight << endl;
	}
}
