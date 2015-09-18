#FLOYD WARSHALL ALGORITHM
##COMPLEXITY :- O(v^3)

1. ALL PAIRS SHORTEST-PATH
	Input Weight-matrix 'w'\.
	if\(\(u,v\)\!=set\(E\)\) w\[u\]\[v\]=Inf,w\[i\]\[i\] = 0\.
	Input parent matrix 'pa'\.
	if\(w\[u\]\[v\]==Inf or u==v\) pa\[u\]\[v\] = NIL, else pa\[u\]\[v\]=u\.

	Output 'w' is as  shortest path's graph. w\[u\]\[v\]==Inf if no path \(u~v\)\.
	Output path matrix pa for path's
	where pa\[i\]\[j\] is the predecessor of 'j' on path \(i~j\)\.

2. TRANSITIVE CLOSURE
	Input boolean matrix of relation R\.
	Output Transitive closure R\+ of relation\.
	function is w\[i\]\[j\] = w\[i\]\[j\] || \(w\[i\]\[k\] && w\[k\]\[j\]\)\.

``` cpp
int w[MX][MX];
int pa[MX][MX];

void floyd_warshall(int size)
{
	FOR(k,1,size)
	{
		FOR(i,1,size)
		{
			FOR(j,1,size)
			{
				if(w[i][k] + w[k][j] < w[i][j])
				{
					w[i][j]=w[i][k]+w[k][j];
					pa[i][j]=pa[k][j];
				}
			}
		}
	}
	return;
}

void print_path(int i,int j)
{
	if(i==j)
	{
		pi(i);pn;
		return;
	}
	pi(pa[i][j]);pw;
	print_path(i,pa[i][j]);
	return;
}
```
