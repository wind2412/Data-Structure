#ifndef _TOPOLOGICAL_SP_H_
#define _TOPOLOGICAL_SP_H_
#include <iostream>
#include <deque>
#include <vector>
#include <climits>
#include "Graph.hpp"
using namespace std;

using Edge = Graph::Edge;

//���������˳��������·����	//����������һ�����������л���	//SedgeWick 
class Topological_SP{
private:
	Graph & g;
	int count = 0;	//��¼����q�Ľ����������С��g.getV()�����л�����Topological_Sortһ���� 
	vector<int> indegree;	//������ȡ���������ĳ�Ա������ʼ��̫����ʹ�������ֲ���new 
	deque<int> q;	//�������Ϊ0�ĵ���С� 
	vector<double> distance; 
public:
	//TopologicalҲ�����ҵ�Դ���·����������Ȼ����Dijkstra��ֻ����s��֮��ĵ������Topological������ͼȫ�����������ǻ��ǿ�����ģ�����
	//������Ҫ��ֻ��s�Լ����ܵ���ĵ㣬s֮ǰ�����ܵ���s����s���ﲻ�˵ģ����Խ����ɳڰ��������ɳڵĽ��������ֻ��distance[s]���0��
	//s֮ǰ��distanceȫ�ǡޣ�Ҳ�ɳڲ��˰������Ǹ����ò������ǡ�����s����ģ�Ҳ�϶��ɳ��ˣ���Topologicalȫ���ɳڣ�ֱ��ȡֵ���ɡ� 
	//�������������ϱߵ��뷨Ӧ������Bellman-Ford�С� 
	Topological_SP(Graph & g, int s): g(g), indegree(g.getV()), /*q(g.getV()),*/ distance(g.getV(), INT_MAX){
		//��md������������ʹ���л������Ӳ��ԣ������л�Ҳ�ⲻ����������һ�Ա���������Topological_sortʹ�õ������飬��Topological_SPʹ�õ�deque��
		//�ص�����ʹ����q(g.getV())����ʼ�������һ���Ϊ����reverse()��Ч������û�뵽��Ȼ���ֱ�ӳ�����5��0......Ȼ����push_back��ֵ����
		//��6����7λ�ˡ��������Ի��ȵ���һ��0��������������ǧ��Ҫ������������woc 
		buildSP(s);
	}
	void buildSP(int s){
		distance[s] = 0;	//����ô�������������������ˡ�����������ȫ�ǡޣ�����û���ɳڡ�������+3==�ޡ����� 
		Graph && rev = g.reverse();
		for(int i = 0; i < rev.getV(); i ++){
			indegree[i] = rev.getDegree(i);	//������ȡ�
			if(indegree[i] == 0){
				q.push_back(i);
				count ++; 
			} 
		} 
		while(!q.empty()){
			int v = q.front(); q.pop_front();	//ʵ����һ��ʼ������ˡ�һ��ʼ���뷨Ӧ������Bellman-Ford�ϡ�Topological�����Ƕ������ɳڡ�ֻ��
												//����ʱpop�ĵ���Ԫ�ؽ����ɳڡ� 
			for(const Edge & e : g.getAdj(v)){
				if(--indegree[e.to] == 0){
					q.push_back(e.to);	//����ڽ�ֵ����ȼ�Ϊ0���Ǿͼ���q��
					count ++;
				}
				if(distance[v] + e.weight < distance[e.to]){	//�ɳڡ� 
					distance[e.to] = distance[v] + e.weight;	
				}
			}
		}
		if(count < g.getV()){
			cerr << "there is a circle in the graph!! topological sort failed! " << endl;
			distance.clear();	//�ɻ��ͳ������distance. 
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
	cout << "1������������·�����£�" << endl; 
	for(vector<double>::const_iterator it = v.begin(); it != v.end(); ++it){
		if(*it == INT_MAX)	cout << "MAX" << " "; 
		else cout << *it << " ";
	}
}
