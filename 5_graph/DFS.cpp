#ifndef _DFS_H_
#define _DFS_H_
#include "Graph.hpp"
#include <deque> 

//�������������������Ȩ����ͼ�����·����ע��һ������Ȩ����Ȩ��ͬ����Ϊ����һ��marked[]���Ϊtrue֮����һ���ҵ���·��
//��ʹ����ζ̣�����marked�Ѿ�����ˣ�Ҳ�����ٷ��ʸõ��ˡ����ֻ�����ڡ���Ȩ����ͼ������ 
class DFS{	//����ϧ��������û�������̬����ģʽӦ����ô������������������Ժ�һ��Ҫ�ú���������� 
private:
	Graph g;
	deque<bool> marked;	//��Ϊ��ʼ����ʱ��ȷ�����ȣ�bitset�޷���̬��ʼ������vector<bool>�ǷǱ�׼���������ʶ�ʹ��deque<bool> 
	vector<int> distance;
public:
	DFS(Graph & g, int v): g(g), marked(g.getV()), distance(g.getV()){
		if(v < 0 || v > g.getV() - 1){
			cerr << "illegal argument of v��" << endl;
			return;
		}
		dfs(v, 0);
	} 
	void dfs(int v, int hopNum){	//�õ�v������������ġ���Ȩ��·�������� 	//hop:������ 
		distance[v] = hopNum;	//д��ǰ��Ҳͬ��Ư������ 
		marked[v] = true;	//�ŵ�ǰ��Ư��������һ��ʼ�ŵ�forѭ���м䡣������ֱ�Ǵ������ơ���������***�ص�***�� 
		for(const Edge & e : g.getAdj(v)){
			if(!marked[e.to]){
				dfs(e.to, hopNum+1);	//ע�⣡��ǧ��ע�⣡������Ҫд��hopNum + 1	������ǧ����++hopNum �����������ǵݹ飡��������ĸı�hopNumֵ����			
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
	
	DFS dfs(g, 1);	//1��ͨ���ģ�
	for(int & i : dfs.getDistance()){
		cout << i << " ";
	} 
	cout << endl;
}
