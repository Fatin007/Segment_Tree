// Problem link: https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/C 
#include <bits/stdc++.h>
#define ll long long
#define endl "\n"
using namespace std;

const int N = 1e5+5;
ll a[N]; 
vector<pair<int,int>> t(4*N);

void build(int n, int b, int e){
    if(b==e){
        t[n]={a[b],1};
        return;
    }
    int m=(b+e)/2;
    int l=2*n, r=2*n+1;
    build(l,b,m);
    build(r,m+1,e);
    if(t[l].first==t[r].first) t[n]={t[l].first,t[l].second+t[r].second};
    else t[n]=min(t[l],t[r]);
}

void update(int n, int b, int e, int i, int v){
    if(i<b || i>e) return;
    if(b==e){
        t[n]={v,1};
        return;
    }
    int m=(b+e)/2;
    int l=2*n, r=2*n+1;
    update(l,b,m,i,v);
    update(r,m+1,e,i,v);
    if(t[l].first==t[r].first) t[n]={t[l].first,t[l].second+t[r].second};
    else t[n]=min(t[l],t[r]);
}

pair<int,int> query(int n, int b, int e, int i, int j){
    if(j<b || i>e) return {1e9,0};
    if(i<=b && e<=j) return t[n];
    int m=(b+e)/2;
    int l=2*n, r=2*n+1;
    pair<int,int> p1=query(l,b,m,i,j);
    pair<int,int> p2=query(r,m+1,e,i,j);
    if(p1.first==p2.first) return {p1.first,p1.second+p2.second};
    return min(p1,p2);
}

void solve(){
    int n,q; cin>>n>>q;
    for(int i=1; i<=n; i++) cin>>a[i];
    for(int i=0; i<4*N; i++) t[i]={1e9,0};
    build(1,1,n);
    while(q--){
        int op; cin>>op;
        if(op==1){
            int i,v; cin>>i>>v;
            update(1,1,n,++i,v);
        }
        else{
            int i,j; cin>>i>>j;
            pair<int,int> ans=query(1,1,n,++i,j);
            cout<<ans.first<<" "<<ans.second<<endl;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    solve();
}