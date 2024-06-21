class Solution {
public:
    int longestIdealString(string s, int k) {
        int dp[30];
        for(int j=0;j<30;j++){
            dp[j]=0;
        }
        for(int i=0;i<s.length();i++){
            int ch=s[i]-'a',ma=0;
            for(int j=max(0,ch-k);j<=min(25,ch+k);j++){
                ma=max(ma,dp[j]);
            }
            dp[ch]=max(dp[ch],ma+1);
		    }
        int ret=0;
        for(int i=0;i<26;i++)ret=max(ret,dp[i]);
        return ret;
        
    }
};