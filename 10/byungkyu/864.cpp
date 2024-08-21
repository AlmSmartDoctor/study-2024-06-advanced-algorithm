class Solution {
public:
    int n,m,dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
    int dp[35][35][65];

    int shortestPathAllKeys(vector<string>& grid) {
        n=grid.size(),m=grid[0].size();
        int cnt=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                for(int k=0;k<(1<<6);k++)
                    dp[i][j][k]=-1;
                if(grid[i][j]=='@')dp[i][j][0]=0;
                if('a'<=grid[i][j]&&grid[i][j]<='z')cnt++;
            }
        }
        for(int k=0;k<(1<<cnt);k++){
            queue<pair<int,int>> que;
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    if(dp[i][j][k]>=0)que.push({i,j});
                }
            }
            while(que.size()){
                auto [x,y]=que.front();que.pop();
                for(int dir=0;dir<4;dir++){
                    int nx=x+dx[dir],ny=y+dy[dir];
                    if(nx<0||nx>=n||ny<0||ny>=m||grid[nx][ny]=='#')continue;
                    if(dp[nx][ny][k]!=-1&&dp[nx][ny][k]<=dp[x][y][k]+1)continue;
                    if(grid[nx][ny]=='.'||grid[nx][ny]=='@'){
                        que.push({nx,ny});
                        dp[nx][ny][k]=dp[x][y][k]+1;
                        continue;
                    }
                    if('A'<=grid[nx][ny]&&grid[nx][ny]<='Z'){
                        int ch=grid[nx][ny]-'A';
                        if(k&(1<<ch)){
                            que.push({nx,ny});
                            dp[nx][ny][k]=dp[x][y][k]+1;
                        }
                        continue;
                    }
                    int ch=grid[nx][ny]-'a';
                    if(dp[nx][ny][k|(1<<ch)]==-1||dp[nx][ny][k|(1<<ch)]>dp[x][y][k]+1){
                        dp[nx][ny][k|(1<<ch)]=dp[x][y][k]+1;
                        if(k&(1<<ch)){
                            que.push({nx,ny});
                        }
                    }
                }
            }
        }
        int ret=1e9;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(dp[i][j][(1<<cnt)-1]>=0)ret=min(ret,dp[i][j][(1<<cnt)-1]);
            }
        }
        return ret==1e9?-1:ret;
    }
    
};