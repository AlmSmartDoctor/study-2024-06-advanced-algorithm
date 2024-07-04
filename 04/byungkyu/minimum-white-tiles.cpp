class Solution {
public:
    int minimumWhiteTiles(string floor, int numCarpets, int carpetLen) {
        int i,j,k,a,b,c;
        int n=floor.length();
        int sum[1005]={0,};
        for(i=0;i<n;i++)
            sum[i+1]=sum[i]+floor[i]-'0';
        if(numCarpets*carpetLen>=n)
            return 0;
        int dp[1005][1005]={0,};
        for(i=carpetLen;i<=n;i++){
            for(j=1;j<=numCarpets;j++){
                dp[i][j]=max(dp[i-1][j],dp[i-carpetLen][j-1]+sum[i]-sum[i-carpetLen]);
            }
        }
        return sum[n]-dp[n][numCarpets];
    }
};