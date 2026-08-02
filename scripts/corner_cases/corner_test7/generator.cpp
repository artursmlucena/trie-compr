#include<bits/stdc++.h>

using namespace std;

#define endl "\n"
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rep(i,a,b) for(int i = (a);i < (b);i++)

typedef long long ll;

void solve_tc() {
    int N = 1e3 + 10;

    vector<pair<int,string>> ops;

    string s = "";

    rep(i,0,N) {
        s += 'a';
        ops.push_back({1,s});
    }

    for(int i = N - 1;i >= 1e2;i--) {
        ops.push_back({4,s});
        s.pop_back();
    }

    s = "";
    rep(i,0,N) {
        s += 'a';
        ops.push_back({2,s});
    }

    cout << 1 << endl;
    cout << sz(ops) << endl;

    for(auto [t,s] : ops) {
        cout << t << " " << s << endl;
    }

} 

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int tc = 1;//cin >> tc;
    while(tc--) solve_tc();

    return 0;
}

