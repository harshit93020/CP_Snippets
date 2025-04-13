#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define all(v) v.begin(), v.end()

const int mod = 998244353 ; 

int bp (int base, int exp) { 
     int ret = 1LL; 
     while(exp) { 
          if(exp&1LL ) { 
               ret = (ret*base) % mod;  
          }
          base = (base * base ) % mod ; 
          exp /= 2;  
     }
     return ret ; 
}


struct segtree {
     int size ; vector<int> sums; 
     void init(int n ) {
        size = 1; 
        while(size<n)size*=2LL;
        sums.assign(2*size,0); 
     }

     void op(int & ret, int a, int b) {
          ret = (a+b)%mod;  
     }

     void build(vector<int> & nums, int node, int lx, int rx) { 

          if(rx-lx == 1) {
              if(lx<nums.size()) sums[node] = nums[lx]; 
              return;  
          }
 
          int m= (lx+rx)/2; 
          build(nums,2*node+1,lx,m); 
          build(nums,2*node+2,m,rx); 
          
          op(sums[node], sums[2*node + 1], sums[2*node+2]); 
     }

     void build(vector<int> & nums) { 
          build(nums, 0 , 0, size) ; 
     }

     
     void set(int i, int val, int node, int lx, int rx) { 

         if(rx-lx == 1) {
             sums[node] = val; 
             return;  
         }

         int m= (lx+rx)/2; 
         if(i<m) {
             set(i,val,2*node+1,lx,m); 
         } else {
             set(i,val,2*node+2,m,rx); 
         }
         op(sums[node], sums[2*node + 1], sums[2*node+2]); 
     }

     void set(int i, int val) { 
        set(i,val,0,0,size) ; 
     }
     int calsum (int l, int r, int node, int lx, int rx) {
         if(l>=r) return 0 ; 
         if(l==lx && r==rx) return sums[node]; 
         int m = (lx+rx)/2; 
         int ret= 0; 
         if(l<m) op(ret,ret,calsum(l,min(r,m),2*node + 1, lx, m)); 
         if(r-1>=m) op(ret,ret,calsum(max(m,l),r,2*node + 2, m, rx));
         return ret;    
     }


     int calsum(int l, int r) { 
        return calsum(l,r,0,0,size); 
     }

} ;



void solve(){
     string s; cin>>s ; int n = s.size() ; 
     // lets first calculate the answer for the first time 
     int zStrings = 0, oStrings = 0 ; 
     int zans = 0 , oans = 0 ; 
     int ans = 0 ; 
     for(int i=0; i<n; i++) { 
          if(s[i] == '0') { 
               int extra = 1; 
               extra = ( extra + oans + oStrings) % mod; 
               extra = (extra + zans) % mod; 
               ans = (ans + extra) % mod ; 
               zans = (zans + extra) % mod;  
               zStrings = (zStrings + bp(2, i)) % mod; 
          } else { 
               int extra = 1; 
               extra = ( extra + zans + zStrings) % mod; 
               extra = (extra + oans) % mod; 
               ans = (ans + extra) % mod ; 
               oans = (oans + extra) % mod;  
               oStrings = (oStrings + bp(2, i)) % mod; 
          }
     }

     segtree st ; st.init(n);
     segtree stR ; stR.init(n); 

     vector<int> nums (n); 
     
     for(int i=0; i<n; i++) nums[i]= ((s[i]=='1'? bp(2LL, i): 0)) ; 
     st.build(nums); 
     for(int i=0; i<n; i++) nums[i]= ((s[i]=='1'? bp(2LL, n-1-i): 0)) ; 
     stR.build(nums); 

     

     
     // cout << stR.calsum(1,1) << endl; 
     // cerr << "vlaid]n\n"; 
     
     int q; cin>>q; 
     for(int ii=0; ii<q; ii++ ) { 
          int id; cin>>id; id--; 
          
          int left1 = st.calsum(0,id) % mod; 
          int right1 = (stR.calsum(id+1,n)) % mod; 
          
          int left0 = (bp(2, id)-1 - left1 + mod) % mod; 
          int right0 = (bp(2, n-1-id)-1 - right1 + mod) % mod; 
          
          // cout << left1 << " " << right1 << " " << left0 << " " << right0 << endl; 
          
          if(s[id] == '1') {
               ans = (ans + 2LL*((left1*right1)%mod)) % mod; 
               ans = (ans  + 2ll*mod - 2LL*( (left0*right0)%mod)) % mod; 
               ans = ( ans + (left1 + right1) % mod) % mod; 
               ans = ( ans + 2ll*mod - (left0 + right0) % mod) % mod; 
               
               
               s[id] = '0'; 
               st.set(id, 0); 
               stR.set(id, 0);     
          } else {
               
               ans = (ans + 2LL*((left0*right0)%mod)) % mod; 
               ans = (ans  + 2LL*mod - 2LL*((left1*right1)%mod)) % mod; 
               ans = ( ans + (left0 + right0) % mod) % mod; 
               ans = ( ans + 2ll*mod - (left1 + right1) % mod) % mod; 
               
               s[id] = '1';
               st.set(id, bp(2LL, id)); 
               stR.set(id, bp(2LL, n-1-id)); 
               
          }    
          
          cout << ans << " " ; 
     }
     
     cout  << endl; 
}

int32_t main(){ ios_base::sync_with_stdio(false); cin.tie(0);
     int tc; cin>>tc; while(tc--)
     solve();
}