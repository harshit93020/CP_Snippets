#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define all(v) v.begin(), v.end()

vector<int> fun(int n, vector<vector<int>> & adj) { 
     vector<int> h (n); 
     auto dfs = [&] (auto && dfs, int src, int par) -> int { 
          
          int mx = 0  ;
          for(int c: adj[src] ) {
                if(c==par) continue ;
                mx = max(mx, dfs(dfs, c, src) ); 
          }
          return h[src] = mx+1; 
     }; 
     dfs(dfs, 0, -1) ;

     vector<int> up(n); 
     up[0] = 1; 

     auto dfs2 = [&] (auto && dfs2, int src, int par) { 
          
          int mx = 0 ;
          vector<int> temp; 
          for(int c: adj[src] ) {
                if(c==par) continue ;
                temp.push_back(h[c]);
          }
          sort(all(temp)); reverse(all(temp)); 

          if(temp.size() == 0 ) return; 

          int mxx1 = temp[0]; int mxx2 = -8; 
          if(temp.size() > 1) mxx2 = temp[1]; 

          // if(src == 0) cout << mxx1 << " " << mxx2 << endl ;


          for(int c: adj[src] ) {
               if(c==par) continue ;
               if(mxx1 == h[c]) up[c] = max(up[src]+1, 2+ mxx2) ; 
               else  up[c] = max(up[src]+1, 2 + mxx1) ;
          }

          for(int c: adj[src] ) {
               if(c==par) continue ;
               dfs2(dfs2, c, src) ; 
          }

     }; 

     dfs2(dfs2, 0, -1) ;
     
     for(int i=0; i<n; i++) h[i] = max(h[i], up[i]) ; 
     return h ; 
}

void solve(){
   int n; cin>>n; 
   vector<vector<int>> adj(n);
   for(int i=0; i<n-1; i++) {
      int uu,vv; cin>>uu>>vv; uu--,vv--;
      adj[uu].push_back(vv);
      adj[vv].push_back(uu);
   }
   auto one = fun(n, adj); 

   cin>>n; 
   adj.clear(); adj.resize(n) ; 
    
   for(int i=0; i<n-1; i++) {
      int uu,vv; cin>>uu>>vv; uu--,vv--;
      adj[uu].push_back(vv);
      adj[vv].push_back(uu);
   }

   auto two = fun(n, adj) ; 

   sort(all(one));
   sort(all(two)); 

   int d1 = one.back(), d2 = two.back(); 
   
   int d = max(d1, d2) ; 

//    for(int i: two) cout << i << ' ' ; cout << endl;
//    for(int i: one) cout << i << ' ' ; cout << endl;



   vector<int> pb(all(two)) ; 
   for(int i=n-2; i>=0; i-- ) pb[i] += pb[i+1]; 
   int ans = 0 ; 
   for(int i: one) {
      int req = d-i;
      int id = lower_bound(all(two), req) - two.begin(); 
      int valid = two.size()-id; 
      ans += (d-1)*(n-valid); 
      ans += valid*(i-1);
      if(valid) ans += pb[n-valid] ; 
     //  cout << ans << endl; 
   }
   
   cout << ans << endl; 
   

}

int32_t main(){ ios_base::sync_with_stdio(false); cin.tie(0);
     // int tc; cin>>tc; while(tc--)
     solve();
}
