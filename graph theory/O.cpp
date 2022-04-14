#include<cstdio>
#include<iostream>
#include<vector>
#include<queue>
#define maxn 500001
using namespace std;
struct egde {
	int node;
	int value;
}temp;
struct node{
	int num;
	long long dis;
	bool operator>(const node& a)const {
		return dis>a.dis;
	}
};
vector<egde> ve[maxn];
long long dis[maxn];
bool vis[maxn];
priority_queue<node,vector<node>,greater<node> > que;
void dijkstra(int root, int n) {
	for(int i=1; i<=n; i++) {
		dis[i]=10e16;
	}
	dis[root]=0;
	que.push({root,0});
	while(!que.empty()) {
		int u=que.top().num;
		que.pop();
		if(vis[u]) {
			continue;
		}
		vis[u]=1;
		int l=ve[u].size();
		for(int i=0; i<l; i++) {
			int v=ve[u][i].node,w=ve[u][i].value;
			if(dis[v]>dis[u]+w) {
				dis[v]=dis[u]+w;
				que.push({v,dis[v]});
			}
		}
	}
}
int main() {
	int m,n,s,u;
	cin>>n>>m>>s;
	for(int i=0; i<m; i++) {
		scanf("%d %d %d",&u,&temp.node,&temp.value);
		ve[u].push_back(temp);
	}
	dijkstra(s,n);
	for(int i=1; i<=n; i++) {
		cout<<((dis[i]==10e16)?-1:dis[i])<< endl;
	}
	return 0;
}
