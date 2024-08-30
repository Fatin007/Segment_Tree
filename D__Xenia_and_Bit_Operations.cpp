// Problem link: https://codeforces.com/problemset/problem/339/D  
#include <bits/stdc++.h>
#define ll long long
#define endl "\n"
using namespace std;

const int N = 131072+1;
int a[N], t[4*N];

void build(int n, int b, int e){
    if(b==e){
        t[n]=a[b];
        return;
    }
    int m=(b+e)/2;
    int l=2*n, r=2*n+1;
    int dif=log2(e-b+1);
    build(l,b,m);
    build(r,m+1,e);
    if(dif&1) t[n]=t[l] | t[r];
    else t[n]=t[l] ^ t[r];
}

void update(int n, int b, int e, int i, int v){
    if(i<b || i>e) return;
    if(b==e){
        t[n]=v;
        return;
    }
    int m=(b+e)/2;
    int l=2*n, r=2*n+1;
    int dif=log2(e-b+1);
    update(l,b,m,i,v);
    update(r,m+1,e,i,v);
    if(dif&1) t[n]=t[l] | t[r];
    else t[n]=t[l] ^ t[r];
}

void solve(){
    int n,q; cin>>n>>q;
    n=1<<n;
    for(int i=1; i<=n; i++) cin>>a[i];
    build(1,1,n);
    while(q--){
        int i,v; cin>>i>>v;
        update(1,1,n,i,v);
        cout<<t[1]<<endl;
    }
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    solve();
}