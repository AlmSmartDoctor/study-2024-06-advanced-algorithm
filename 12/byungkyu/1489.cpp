struct DSU{
	int n,level[105],pa[105];
	void init(int n){
		this->n = n;
		for(int i=0;i<n;i++){
			level[i]=0;
			pa[i]=i;
		}
	}
	int getpa(int x){
		if(x==pa[x])return x;
		return pa[x]=getpa(pa[x]);
	}
	bool uni(int x,int y){
		x=getpa(x);
		y=getpa(y);
		if(x==y)return false;
		if(level[x]<level[y]){
			int t=x;x=y;y=t;
		}
		pa[y]=x;
		if(level[x]==level[y])level[x]++;
		return true;
	}
} dsu;

int getMST(vector<vector<int>>& edges,int n){
    priority_queue<pair<int,int>,vector<pair<int,int>>, greater<pair<int,int>>> pq;
    dsu.init(n);
    for(int i=0;i<edges.size();i++)
        pq.push({edges[i][2],i});
    int ret=0;
    while(pq.size()){
        auto [w,a]=pq.top();pq.pop();
        if(!dsu.uni(edges[a][0],edges[a][1]))continue;
        ret+=w;
    }
    return ret;
}

class Solution {
public:

    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        int m=edges.size();
        vector<int> critical,rest;
        int val=getMST(edges,n);
        for(int i=0;i<m;i++){
            int t=edges[i][2];
            edges[i][2]=1e7;
            if(getMST(edges,n)>val)
                critical.push_back(i);
            else{
                edges[i][2]=0;
                if(getMST(edges,n)+t==val)
                    rest.push_back(i);
            }
            edges[i][2]=t;
        }
        return {critical,rest};
    }
};