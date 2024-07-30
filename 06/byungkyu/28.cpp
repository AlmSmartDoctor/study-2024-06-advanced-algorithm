class Solution {
public:
    int pi[10005]={0,};
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

    int kmpfind(string L,string S,int l,int s){
        int i,j,k,a,b;
        a=0;b=0;
        while(a<=l-s){
            if(L[a+b]==S[b]&&b<s){
                b++;
                if(b>=s)return a;
            }
            else{
                if(b==0)a++;
                else{
                    a+=b-pi[b-1];
                    b=pi[b-1];
                }
            }
        }
        return -1;
    }
    int strStr(string haystack, string needle) {
        kmpinit(needle.length(),needle);
        return kmpfind(haystack,needle,haystack.length(),needle.length());
    }
};