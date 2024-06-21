class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int cnt[105][105],score[105][105];
        int dx[3]={-1,0,-1},dy[3]={0,-1,-1};
        int B=1e9+7;
        int n=board.size(),m=board[0].length();
        for(int i=0;i<=n;i++){
            for(int j=0;j<=m;j++){
                cnt[i][j]=score[i][j]=0;
            }
        }
        cnt[0][0]=1;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(board[i-1][j-1]=='X')continue;
                for(int k=0;k<3;k++){
                    int x=i+dx[k],y=j+dy[k];
                    if(score[i][j]<score[x][y]){
                        score[i][j]=score[x][y];
                        cnt[i][j]=cnt[x][y];
                    }
                    else if(score[i][j]==score[x][y]){
                        cnt[i][j]+=cnt[x][y];
                        cnt[i][j]%=B;
                    }
                }
                int c=board[i-1][j-1]-'0';
                if(0<=c&&c<10&&cnt[i][j])score[i][j]+=c;
            }
        }
        return vector<int>({score[n][m],cnt[n][m]});
    }
};