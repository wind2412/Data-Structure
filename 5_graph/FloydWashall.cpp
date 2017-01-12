#ifndef _FLOYD_WARSHALL_H_
#define _FLOYD_WARSHALL_H_
#include "Graph.hpp"
#include <climits>
#include <cstdio>

using Edge = typename Graph::Edge; 

class FloydWashall{
private:
	Graph & g;
	vector<vector<double>> distance;
public:
	FloydWashall(Graph & g): g(g), distance(g.getV()){
		for(int i = 0; i < g.getV(); i ++){
			distance[i].resize(g.getV());
		}
		for(int i = 0; i < g.getV(); i ++){
			for(int j = 0; j < g.getV(); j ++){
				distance[i][j] = INT_MAX;
				if(i == j)	distance[i][j] = 0;
			}	
		}
		
		build();
	}
	void build(){
		for(int i = 0; i < g.getV(); i ++){
			for(const Edge & e : g.getAdj(i)){
				distance[e.from][e.to] = e.weight;
			}
		}
		for(int t = 0; t < g.getV(); t ++){
			for(int i = 0; i < g.getV(); i ++){
				for(int j = 0; j < g.getV(); j ++){
					//千万注意下标的顺序！！+一定别忘了distance松弛不能有max！！！否则max的值如果碰到另一个是负值，max会减小，比较麻烦。。 
					if(distance[i][t] + distance[t][j] < distance[i][j] && distance[i][t] != INT_MAX && distance[t][j] != INT_MAX){
						distance[i][j] = distance[i][t] + distance[t][j];
					}
				}
			}
		}
	}
	vector<vector<double>> getDistance(){
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
	g.addEdge(4, 1, -1);
	g.reverse().print();
	g.print();
	
	FloydWashall fw(g);
	vector<vector<double>> && v = fw.getDistance();
	for(int i = 0; i < g.getV(); i ++){
		for(int j = 0; j < g.getV(); j ++){
			if(v[i][j] == INT_MAX)	printf("  MAX  ");
			else printf("  %4.2lf ", v[i][j]);		//注意是%lf...
		}
		cout << endl;
	}
}
