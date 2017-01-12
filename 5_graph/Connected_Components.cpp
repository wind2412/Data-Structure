#ifndef _CC_H_
#define _CC_H_
#include <iostream>
#include <vector>
#include "Graph.hpp"
using namespace std;

//��ͨ�����㷨��	�����ڲ��鼯��	//from SedgeWick 
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
				count ++;	//count�������Ư������ԭ�ȷ�����ߵ���Ƽ�ֱ������ֻ���ҵ��µ���ͨ����֮��Ż�count++���� 
			}
//			count++;	//��� 
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
