#include <bits/stdc++.h>
#define ll long long
#define endl "\n"
using namespace std;

const int N=1e5+5;
ll a[N],t[4*N],lazy[4*N];

void push(int n,int b,int e){
    if(lazy[n]!=0){
        t[n]+=(e-b+1)*lazy[n]; 
        if(b!=e){ // Propagate to children if not a leaf
            lazy[2*n]+=lazy[n];
            lazy[2*n+1]+=lazy[n];
        }
        lazy[n]=0;//Clear lazy value
    }
}

void build(int n,int b,int e){
    if(b==e){
        t[n]=a[b];
        return;
    }
    int m=(b+e)/2;
    int l=2*n,r=2*n+1;
    build(l,b,m);
    build(r,m+1,e);
    t[n]=t[l]+t[r];
}

void update(int n,int b,int e,int i,int j,ll v){
    push(n,b,e);
    if(j<b||i>e) return;
    if(i<=b&&e<=j){
        lazy[n]+=v;
        push(n,b,e);
        return;
    }
    int m=(b+e)/2;
    int l=2*n,r=2*n+1;
    update(l,b,m,i,j,v);
    update(r,m+1,e,i,j,v);
    t[n]=t[l]+t[r];
}

ll query(int n, int b,int e,int i,int j){
    push(n,b,e);
    if(j<b||i>e) return 0;
    if(i<=b&&e<=j) return t[n]; 
    int m=(b+e)/2;
    int l=2*n,r=2*n+1;
    return query(l,b,m,i,j)+query(r,m+1,e,i,j);
}

void solve(){
    int n,q; cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    build(1,1,n);
    while(q--){
        int op; cin>>op;
        if(op==1){
            int i,v; cin>>i>>v; update(1,1,n,++i,i,v- a[i]); 
            a[i]=v;
        }else if(op==2){
            int i,j,v; cin>>i>>j>>v;
            update(1,1,n,++i,j,v);
        }else{
            int i,j; cin>>i>>j;
            cout<<query(1,1,n,++i,j)<<endl;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
