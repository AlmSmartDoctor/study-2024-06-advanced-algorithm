class Solution {
public:

    vector<long long> ans,ch[20005];

    vector<long long> get(int now,int from,vector<int>& cost){
        vector<long long> vec;
        for(auto a : ch[now])if(a!=from){
            vector<long long> tmp=get(a,now,cost);
            vec.insert(vec.end(),tmp.begin(),tmp.end());
        }
        vec.push_back(cost[now]);
        sort(vec.begin(),vec.end(),greater<long long>());
        if(vec.size()<3){
            ans[now]=1;
            return vec;
        }
        int l=vec.size();
        ans[now]=max(0ll,max(vec[0]*vec[1]*vec[2],vec[0]*vec[l-1]*vec[l-2]));
        if(vec.size()<6){
            return vec;
        }
        return {vec[0],vec[1],vec[2],vec[l-1],vec[l-2]};
    }

    vector<long long> placedCoins(vector<vector<int>>& edges, vector<int>& cost) {
        int n=edges.size();
        for(int i=0;i<n;i++){
            int a=edges[i][0],b=edges[i][1];
            ch[a].push_back(b);
            ch[b].push_back(a);
        }
        for(int i=0;i<n+1;i++)ans.push_back(0);
        get(0,0,cost);
        return ans;
    }
};