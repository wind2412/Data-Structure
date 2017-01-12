#ifndef _KOSARAJU_SCC_H_
#define _KOSARAJU_SCC_H_
#include <iostream>
#include "Graph.hpp"
#include <stack>
#include <vector>
using namespace std;

/**
 *	Kosarajuǿ��ͨ�����㷨��
 *  ������һ��ͼ��ʹreverse�ˣ���ԭͼ���Ǿ�����ͬ��ǿ��ͨ���������ʣ�
 *	�ǳ�ͨ���׶���ACM֮��blog��http://www.acmerblog.com/strongly-connected-components-6099.html
 *	��һ��ͼ�ر��׶���
 * 
 *  �㷨���裺
 *	1.�����еĽ�����DFS��ȱ�����mark����ȥ���ĵ㡣�ڷ���һ����v����ʱ����v����stack�С� 
 *	2.�õ�ͼg��reverse�汾��Ȼ���stack���ϵ������Է������ʽ�ڷ���ͼ��DFS����ÿ�����ʹ��ĵ㡣Ȼ��˳��union-find�ӵ�id�����С� 
 *  
 *  ʹ��stack����Ϊ����gͼ��Դ������յ㡣 �������stack�������ڷ���ͼ��˳�������0~g.getV()һ��ʼ�ĵ�ȫ����յ��ˡ� 
 *
 */

class KosarajuSCC{
private:
	Graph & g;
	Graph && rev;
	vector<bool> marked;
	vector<int> id;	//union-find���鼯
	stack<int> s; 
	int count; //���鼯��������ǿ��ͨ�����ĸ����� 
public:
	KosarajuSCC(Graph & g): g(g), rev(g.reverse()), marked(g.getV(), 0), id(g.getV(), 0), count(0){buildSCC();};
	void buildSCC(){
		for(int i = 0; i < g.getV(); i ++){
			if(!marked[i]){
				dfsOrigin(i);
			}
		}
		marked.assign(g.getV(), 0); //����marked
		while(!s.empty()){
			int v = s.top(); s.pop();
			if(!marked[v]){
				dfsReverse(v);
				count ++;
			}
		} 
	}
	void dfsOrigin(int v){	//��ԭͼ����dfs 
		marked[v] = true;
		s.push(v);	//����ջ 
		for(const Edge & e : g.getAdj(v)){
			if(!marked[e.to]){
				dfsOrigin(e.to);
			}
		}
	}
	void dfsReverse(int v){	//��reverseͼ����dfs 
		marked[v] = true;
		for(const Edge & e : rev.getAdj(v)){
			if(!marked[e.to]){
				dfsReverse(e.to);
			}
		}
		id[v] = count;
	}
	vector<int> getId(){
		return id;
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
	g.addEdge(4, 1, -10);
	cout << "1's out_degree: "<<g.getDegree(1) << endl;
	g.reverse().print();
	g.print();
	
	KosarajuSCC k(g);
	vector<int> && v = k.getId();
	for(vector<int>::iterator it = v.begin(); it != v.end(); ++it){
		cout << *it << " ";
	}
}
