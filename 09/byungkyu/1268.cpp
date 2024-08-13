class Solution {
public:

    int cnt=0;
    vector<char> ch;
    vector<vector<int>> next;
    vector<vector<string>> suggest;
    

    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        cnt=0;
        ch.push_back('*');
        next.push_back({});
        suggest.push_back({});
        sort(products.begin(),products.end());
        for(string s : products){
            int p=0;
            for(char c : s){
                int ne=0;
                for(auto k : next[p]){
                    if(ch[k]==c)ne=k;
                }
                if(ne==0){
                    next[p].push_back(++cnt);
                    ch.push_back(c);
                    next.push_back({});
                    suggest.push_back({});
                    ne=cnt;
                }
                suggest[p].push_back(s);
                sort(suggest[p].begin(),suggest[p].end());
                if(suggest[p].size()>3)suggest[p].pop_back();
                p=ne;
            }
            suggest[p].push_back(s);
            sort(suggest[p].begin(),suggest[p].end());
            if(suggest[p].size()>3)suggest[p].pop_back();
        }
        vector<vector<string>> ret(searchWord.size());
        int p=0,k=0;
        for(char c : searchWord){
            int ne=0;
            for(auto k : next[p]){
                if(ch[k]==c)ne=k;
            }
            if(ne==0)break;
            ret[k]=suggest[ne];
            p=ne;k++;
        }

        return ret;
    }
};