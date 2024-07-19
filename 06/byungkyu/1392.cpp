class Solution {
public:
    int pi[100005]={0,};
    void kmpinit(int n,string S){
        int i,j,k,a,b,c;
        a=1;b=0;
        while(a+b<n){
            if(S[a+b]==S[b]){
                pi[a+b]=b+1;
                b++;
            }
            else{
                if(b==0)a++;
                else{
                    a+=b-pi[b-1];
                    b=pi[b-1];
                }
            }
        }
    }

    string longestPrefix(string S) {
        kmpinit(S.length(),S);
        return S.substr(0,pi[S.length()-1]);
    }
};