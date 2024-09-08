class Solution {
public:
    int vis[1005];
    int minCostConnectPoints(vector<vector<int>>& points) {
        priority_queue<pair<int,int>,vector<pair<int,int>>, greater<pair<int,int>>> pq;
        int n=points.size();
        for(int i=0;i<n;i++)
            vis[i]=0;
        pq.push({0,0});    
        int ret=0;
        while(pq.size()){
            auto [w,a]=pq.top();pq.pop();
            if(vis[a])continue;
            vis[a]=1;
            ret+=w;
            for(int i=0;i<n;i++){
                if(vis[i])continue;
                pq.push({abs(points[a][0]-points[i][0])+abs(points[a][1]-points[i][1]),i});
            }
        }
        return ret;
    }
};