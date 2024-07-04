class Solution {
public:
    int specialPerm(vector<int>& nums) {
        int dp[15][1<<14][15]={0,};
        int n=nums.size();
        int B=1e9+7;

        nums.push_back(1);
        dp[0][0][n]=1;
        for(int step=1;step<=n;step++){
            for(int j=0;j<=n;j++){
                for(int k=0;k<n;k++){
                    if(j==k)continue;
                    if(nums[j]%nums[k]&&nums[k]%nums[j])continue;
                    for(int i=0;i<(1<<n);i++){
                        if(i&(1<<k))continue;
                        dp[step][i+(1<<k)][k]+=dp[step-1][i][j];
                        dp[step][i+(1<<k)][k]%=B;
                    }
                }
            }
        }
        int ret=0;
        for(int j=0;j<n;j++)
            for(int i=0;i<(1<<n);i++)
                ret=(ret+dp[n][i][j])%B;

        return ret;
    }
};