#ifndef _BFS_H_
#define _BFS_H_
#include "Graph.hpp"
#include <deque>
#include <queue>

//������������� ������Ȩͼ 
//ͬ��ʹ��deque<bool>�������޷���̬��ʼ����bitset 
class BFS{
private:
	Graph g;
	deque<bool> marked;
	vector<int> distance;
public:
	BFS(Graph & g, int v): g(g), marked(g.getV()), distance(g.getV()){
		if(v < 0 || v > g.getV() - 1){
			cerr << "illegal argument of v��" << endl;
			return;
		}
		bfs(v);
	}
	void bfs(int v){
		queue<int> q;
		q.push(v);
		marked[v] = true;
		while(!q.empty()){
			int v = q.front(); q.pop();
			for(const Edge & e : g.getAdj(v)){
				if(marked[e.to] == false){
					q.push(e.to);
					marked[e.to] = true;
					distance[e.to] = distance[v] + 1;	//Ư����ʡȥ��һ���������� 
				}
			}
		}
	} 
	vector<int> getDistance(){
		return distance;
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
	g.print();
	g.reverse().print();
	
	BFS bfs(g, 1);	//1��ͨ���ģ�
	for(int & i : bfs.getDistance()){
		cout << i << " ";
	} 
	cout << endl;
}

