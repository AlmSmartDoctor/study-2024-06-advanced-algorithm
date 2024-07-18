#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll hei[100005];
ll wid[100005];
stack<ll> st;

int main(){
    ll i,j,k,a,b,c,n,h;
    while(1){
        scanf("%lld",&n);
        if(n==0)break;
        a=0;
        for(i=1;i<=n;i++){
            scanf("%lld",&hei[i]);
            wid[i]=0;
        }
        while(st.size())st.pop();
        for(i=1;i<=n;i++){
            h=hei[i];
            b=0;
            j=0;
            while(st.size()&&h<hei[st.top()]){
                j=st.top();st.pop();
                a=max(a,hei[j]*(wid[j]+b));
                b+=wid[j];
            }
            wid[i]=b+1;
            st.push(i);
        }
        b=0;
        while(st.size()){
            j=st.top();st.pop();
            a=max(a,hei[j]*(wid[j]+b));
            b+=wid[j];
        }
        printf("%lld\n",a);
    }
}