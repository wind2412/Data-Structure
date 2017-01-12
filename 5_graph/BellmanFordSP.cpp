#ifndef _BELLMANFORD__SPFA__H_
#define _BELLMANFORD__SPFA__H_
#include <iostream>
#include <climits>
#include <deque> 
#include "Graph.hpp"
using namespace std;

/**
 *Bellman-Ford��Դ���·���㷨 O(|V|*|E|)	���ձ�from-to���ֵ�˳�����g.getV()-1����ѯ�ɳ� Dijkstra�޷����и�Ȩ�߼��� ��
 *Bellman-FordֻҪû�и���·���ɡ�
 *SedgeWick��pdf����������˵��
 *�����ݽṹ���㷨��������C++����������4th����������Bellman-Ford�Ķ����Ż��㷨SPFA�����Խ���O(kE). ������� k <= 2. 
 *���ַ���������ʵ�֡� 
 *ʵ�ֵ�α����μ�wikipedia.  
 *https://zh.wikipedia.org/wiki/%E8%B4%9D%E5%B0%94%E6%9B%BC-%E7%A6%8F%E7%89%B9%E7%AE%97%E6%B3%95 
 */ 
 
class BellmanFordSP{
private:
	Graph & g;
	deque<int> q;	//����ֻ��һ����ͨ�Ķ��У������ֵ�˳����ӡ�û����������á�
	vector<double> distance;
public:
	BellmanFordSP(Graph & g, int s): g(g), distance(g.getV(), INT_MAX){
		buildSP(s);
	}
	void buildSP(int s){
		//1.��ʼ��ͼ 
		distance[s] = 0;
		q.push_back(s);
		
		//2.�ظ���ÿ���߽����ɳ� 
		for(int t = 0; t < g.getV() - 1; t ++){	//g.getV()-1��ѭ�� ��������ʹ�и�Ȩ��Ҳ��ǿ����g.getV()-1���˳��ˡ���������ѭ���� 
			for(int i = 0; i < g.getV(); i ++){
				for(const Edge & e : g.getAdj(i)){	//�˷�����ͬ���ǣ���Dijkstra��Topological��ͬ����ÿ���߾����в����ɳ�ֱ������Ϊֹ�� 
					if(distance[i] + e.weight < distance[e.to]){
						distance[e.to] = distance[i] + e.weight;
					}
				}
			}
		}
		
		//3.����Ƿ��и�Ȩ�� //��ʵ���ǿ���û�б߻��ܱ�ø��� 
		for(int i = 0; i < g.getV(); i ++){
			for(const Edge & e : g.getAdj(i)){
				if(distance[i] + e.weight < distance[e.to]){	//��Ϊ�и�Ȩ���ͻ��������������distance[e.to]���ǻ������С�ģ�
																//��˼�������᲻�������С�����ˣ�
																//ע�ⲻ�ܼ�����Ƿ��Ǹ��ģ���Ϊû׼ÿ���ɳ�-0.001��������������Ҳ�ǿ��ܵġ� 
					cerr << "��ͼ�и�Ȩ������" << endl;
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
	deque<int> q;	//����ֻ��һ����ͨ�Ķ��У������ֵ�˳����ӡ�û����������á�
	vector<double> distance;
	vector<bool> isInQueue;	//ͨ�����ñ�־λ���ܹ����ٲ鿴ĳһ������Ƿ���q�С����͵��Կռ任ʱ�䡣
	vector<int> count;	//����ÿ����������ܴ���������SPFA������������·������֤��������������Ӵ������ᳬ��g.getV(). 
public:
	SPFA(Graph & g, int s): g(g), distance(g.getV(), INT_MAX), isInQueue(g.getV(), 0), count(g.getV(), 0){
		buildSP(s);
	}
	void buildSP(int s){
		//1.��ʼ��ͼ 
		distance[s] = 0;
		q.push_back(s);
		isInQueue[s] = true;
		count[s] ++;
		
		//2.�����Ż�
		while(!q.empty()){
			int v = q.front(); q.pop_front();	//��һ���BFS��� 
			isInQueue[v] = false;	//count[]���ܼ�С ��Ϊ��¼����ܴ��� 
			for(const Edge & e : g.getAdj(v)){
				if(distance[v] + e.weight < distance[e.to]){
					distance[e.to] = distance[v] + e.weight;	//�ɳ� 
				}
				if(!isInQueue[e.to]){
					q.push_back(e.to);
					isInQueue[e.to] = true; 
					if(++count[e.to] >= g.getV()){
						cerr << "��ͼ�и�Ȩ������" << endl;
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
	g.addEdge(4, 1, -1);	//spfa����bug�� 
	cout << "1's out_degree: "<<g.getDegree(1) << endl;
	g.reverse().print();
	g.print();
	
	BellmanFordSP b(g, 4);
	vector<double> && v = b.getDistance();
	cout << "1������������·�����£�" << endl; 
	for(vector<double>::const_iterator it = v.begin(); it != v.end(); ++it){
		if(*it == INT_MAX)	cout << "MAX" << " "; 
		else cout << *it << " ";
	}
	cout << endl << endl;
	
	SPFA spfa(g, 1);
	vector<double> && v2 = b.getDistance();
	cout << "1������������·�����£�" << endl; 
	for(vector<double>::const_iterator it = v2.begin(); it != v2.end(); ++it){
		if(*it == INT_MAX)	cout << "MAX" << " "; 
		else cout << *it << " ";
	}
}
