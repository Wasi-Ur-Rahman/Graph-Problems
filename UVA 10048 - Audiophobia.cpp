#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define all(a) a.begin(),a.end()
#define F first
#define S second
#define pb push_back

const int N = 200;
const int inf = 1e13;

vector<pair<int,int>> g[N];
int dis[N];

bool is_possible(int s,int t,int mid) {
  for (int i = 0;i < N;i++) dis[i] = inf;
  priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
  pq.push({0,s});
  dis[s] = 0;

  while (!pq.empty()) {
    int u = pq.top().S;
    int c = pq.top().F;
    pq.pop();

    for (auto it:g[u]) {
      int v = it.F;
      int w = it.S;

      if (c + w < dis[v] && w <= mid) {
        dis[v] = c + w;
        pq.push({dis[v],v});
      }
    }
  }
  if (dis[t] == inf) return false;

  return true;
}


int32_t main() {
  ios_base::sync_with_stdio(NULL);
  cin.tie(NULL);

  int t,test = 1;

  while (1) {
    int n,s,q;
    cin >> n >> s >> q;

    if (n == 0 && s == 0 && q == 0) return 0;

    for (int i = 0;i <= n;i++) g[i].clear();

    int mx = 0,mn = INT_MAX;
    for (int i = 0;i < s;i++) {
      int u,v,w;
      cin >> u >> v >> w;
      mx = max(mx,w);
      mn = min(mn,w);
      g[u].pb({v,w});
      g[v].pb({u,w});
    }

    if (test == 1) {
      cout << "Case #" << test++ << "\n";
    }else cout << "\nCase #" << test++ << "\n";
    while (q--) {
      int u,v;
      cin >> u >> v;

      int l = 0,r = mx,ans = INT_MAX;
      for (int i = 0;i <= 64;i++) {
        int mid = (l + r)/2;
        
        if (is_possible(u,v,mid)) {
          ans = min(ans,mid);
          r = mid - 1;
        }else {
          l = mid + 1;
        }
      }
      if (ans == INT_MAX) {
        cout << "no path\n";
      }else cout << ans << '\n';
    }
  }
  return 0;
}
