#DIJKSTRA ALGORITHM
##COMPLEXITY :- O(v^2 + e) || O(v^2)

1. SINGLE SOURCE SHORTEST PATH:

>	Input Weight matrix w, w\[u\]\[v\]=Inf is there is no edge\(u,v\)\.
>	Input parent vector pa with initlized with 0\.
>
>	Output shortest distance dist from source\.
>	parent pa\[v\] of vertex v in shortest path to source\.

``` cpp
bool vst[MX];
int dist[MX];
int w[MX][MX];
int pa[MX];
vector<int> adj[MX]

class cmp
{
	bool operator () const (pair<int,int>& v1,pair<int,int>& v2)
	{
		return (v1.second > v2.second);
	}
};

void dijkstra(int source,int size)
{
	fill(vst,&vst[size],false);
	fill(dist,&dist[size],Inf);

	dist[source]=0;
	pa[source]=0; 

	priority_queue<int,vector<int>,cmp> Q;
	Q.push(make_pair(source,0));

	while(!Q.empty())
	{
		int u=Q.top().first;
		Q.pop();
		if(vst[u]) continue;
		//use if(u==target) return dist[target]; for early return
		for(int i=0;i<adj[u].size();i++)
		{
			int v=adj[u][i];
			if( dist[u] + w[u][v] < dist[v])
			{
				dist[v]=dist[u]+w[u][v];
				pa[v]=u;
				Q.push(make_pair(v,dist[v]));
			}
		}
	}
	return;
}

int print_path(int x) //  from source to v
{
	printf("%d ",pa[x]);
	if(pa[x]==0) // 0 is parent of source
	{
		putchar('\n');return;
	}
	print_path(pa[x]);
	return;
}
```
