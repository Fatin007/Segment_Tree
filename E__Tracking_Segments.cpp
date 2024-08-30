// problem link: https://codeforces.com/problemset/problem/1843/E
#include <bits/stdc++.h>
#define ll long long
#define endl "\n"
using namespace std;

const int N = 1e5+5;
int t[4*N];

void build(int n, int b, int e){
    if(b==e){
        t[n]=0;
        return;
    }
    int m=(b+e)/2;
    int l=2*n, r=2*n+1;
    build(l,b,m);
    build(r,m+1,e);
    t[n]=t[l]+t[r];
}

void update(int n, int b, int e, int i, int v){
    if(i<b || i>e) return;
    if(b==e){
        t[n]=v;
        return;
    }
    int m=(b+e)/2;
    int l=2*n, r=2*n+1;
    update(l,b,m,i,v);
    update(r,m+1,e,i,v);
    t[n]=t[l]+t[r];
}

int query(int n, int b, int e, int i, int j){
    if(j<b || i>e) return 0;
    if(i<=b && e<=j) return t[n];
    int m=(b+e)/2;
    int l=2*n, r=2*n+1;
    return query(l,b,m,i,j)+query(r,m+1,e,i,j);
}

bool Predicate(int n, vector<pair<int,int>> &v, vector<int> &a, int m){
    build(1,1,n);
    for(int i=0; i<=m; i++){
        update(1,1,n,a[i],1);
    }
    for(int i=0; i<v.size(); i++){
        int l=v[i].first, r=v[i].second;        
        int o=query(1,1,n,l,r);
        int z=r-l+1-o;
        if(o>z) return true;
    }
    return false;
}

void solve(){
    int n,m; cin>>n>>m;
    vector<pair<int,int>> v;
    for(int i=0; i<m; i++){
        int l,r; cin>>l>>r;
        v.push_back({l,r});
    }
    int q; cin>>q;
    vector<int> a(q);
    for(auto &i:a) cin>>i;
    int l=0, r=q-1;
    while(r-l>4){
        int mid=(l+r)/2;
        if(Predicate(n,v,a,mid)) r=mid;
        else l=mid+1;
    }
    for(int i=l; i<=r; i++){
        if(Predicate(n,v,a,i)){
            cout<<++i<<endl;
            return;
        }
    }
    cout<<-1<<endl;
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int tc=1;
    cin>>tc;
    while(tc--) solve();
}