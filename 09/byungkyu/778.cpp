class Solution {
public:

    int rank[2505]={0,},pa[2505],water[55][55]={0,};
    int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
    pair<int,int> pos[2505];

    int getpa(int a){
        if(a==pa[a])return a;
        return pa[a]=getpa(pa[a]);
    }

    void uni(int a,int b){
        a=getpa(a);b=getpa(b);
        if(a==b)return;
        if(rank[a]<rank[b])swap(a,b);
        pa[b]=a;
        if(rank[a]==rank[b])rank[a]++;
    }

    int swimInWater(vector<vector<int>>& grid) {
        int n=grid.size();
        for(int i=0;i<n*n;i++){
            pa[i]=i;
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                pos[grid[i][j]]={i,j};
            }
        }
        for(int i=0;i<n*n;i++){
            auto [x,y]=pos[i];
            water[x][y]=i+1;
            for(int k=0;k<4;k++){
                if(x+dx[k]>=0&&x+dx[k]<n&&y+dy[k]>=0&&y+dy[k]<n){
                    if(water[x+dx[k]][y+dy[k]]){
                        uni(i,water[x+dx[k]][y+dy[k]]-1);
                    }
                }
            }
            if(getpa(grid[0][0])==getpa(grid[n-1][n-1]))return i;
        }
        return n*n;
    }
};