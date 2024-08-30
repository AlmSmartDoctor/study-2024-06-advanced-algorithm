class Solution {
public:
    bool vis[305][305];
    int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0},n,m;

    vector<int> bfs(int sx,int sy,vector<vector<int>>& land){
        int x1=sx,x2=sx,y1=sy,y2=sy;
        queue<pair<int,int>> que;
        que.push({sx,sy});
        while(que.size()){
            auto [x,y]=que.front();que.pop();
            for(int k=0;k<4;k++){
                int nx=x+dx[k],ny=y+dy[k];
                if(0<=nx&&nx<n&&0<=ny&&ny<m&&!vis[nx][ny]&&land[nx][ny]){
                    vis[nx][ny]=true;
                    x1=min(x1,nx);x2=max(x2,nx);
                    y1=min(y1,ny);y2=max(y2,ny);
                    que.push({nx,ny});
                }
            }        
        }
        return {x1,y1,x2,y2};
    }

    vector<vector<int>> findFarmland(vector<vector<int>>& land) {
        n=land.size(),m=land[0].size();
        vector<vector<int>> ret;

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(!vis[i][j]&&land[i][j]){
                    vis[i][j]=true;
                    ret.push_back(bfs(i,j,land));
                }
            }
        }
        return ret;
    }
};