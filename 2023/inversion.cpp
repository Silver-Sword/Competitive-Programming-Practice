#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vii;
typedef long long ll;
typedef vector<ll> vl;

#define nl '\n'
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

const int DEBUG = false;
int n;

vi buildPerm(vvi &adj)
{
    vi perm (n);
    
    vii out (n);
    for(int i = 0; i < n; i++) 
        out[i] = {sz(adj[i]), i};

    sort(all(out));

    for(int val = 0; val < n; val++)
    {
        perm[out[val].second] = val;
    }

    return perm;
}

vl dp;
const int BLANK = -1;
ll recurse(int idx, vi &perm)
{
    if(dp[idx] != BLANK) return dp[idx];

    int ran_min = 1e9;
    ll ans = 0;
    for(int i = idx + 1; i < n; i++)
    {
        if(perm[i] < perm[idx] || perm[i] > ran_min) continue;

        ran_min = perm[i];
        ans += recurse(i, perm);
    }

    if(ran_min >= (int) 1e9) return dp[idx] = 1;
    if(DEBUG) cout << "dp[idx=" << idx << "] = " << ans << nl;
    return dp[idx] = ans;
}

void solve()
{
    int m; cin >> n >> m;
    vvi matrix (n, vi (n));
    int u, v;
    for(int i = 0; i < m; i++)
    {
        cin >> u >> v;
        u--; v--;
        matrix[u][v] = matrix[v][u] = 1;
    }

    vvi adj (n);
    for(int i = 0; i < n; i ++)
    {
        for(int j = 0; j < i; j++)
        {
            if(matrix[i][j]) adj[j].push_back(i);
            else adj[i].push_back(j);
        }
    }

    vi perm = buildPerm(adj); 

    if(DEBUG)
    {
        cout << "PERM: "; for(int p : perm) cout << p + 1 << " "; cout << nl;
    }

    // must take local min
    int prev_min = 1e9;
    ll total = 0;
    dp = vl (n, BLANK);
    for(int i = 0; i < n; i++)
    {
        if(perm[i] < prev_min)
        {
            prev_min = perm[i];
            total += recurse(i, perm);
        }
    }
    cout << total << nl;
}

int main(){
    cin.tie()->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}