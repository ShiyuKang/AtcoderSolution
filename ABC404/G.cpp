#include <bits/stdc++.h>

using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

const int mod = 998244353;
const double PI = std::numbers::pi;
std::mt19937 rng(std::random_device{}());

template <class T>
constexpr T lowbit(T x) noexcept
{
    return x & (-x);
};

template <class T>
struct Inf
{
};

template <>
struct Inf<int>
{
    constexpr static int v = 1e9;
};

template <>
struct Inf<ll>
{
    constexpr static ll v = 1e18;
};

template <typename T>
constexpr T INF = Inf<T>::v;

template <typename T>
    requires std::is_integral_v<T>
constexpr int msb(T x)
{
    using UT = std::make_unsigned_t<T>;
    return std::numeric_limits<UT>::digits - std::countl_zero(UT(x)) - 1;
}

constexpr bool InputStream = 1;

namespace FI
{
    char B[1 << 16], *S = B, *T = B;
    inline char getc()
    {
        return S == T && (T = (S = B) + fread(B, 1, 1 << 16, stdin), S == T) ? EOF : *S++;
    }

    template <typename Tp, typename... Types>
        requires(InputStream == false)
    inline void read(Tp &o, Types &...Args)
    {
        o = 0;
        bool s = 0;
        char c = getc();
        while (c > '9' || c < '0')
            s |= c == '-', c = getc();
        while (c >= '0' && c <= '9')
            o = o * 10 + c - '0', c = getc();
        if (s)
            o = -o;
        if constexpr (sizeof...(Args) > 0)
            read(Args...);
    }
} // namespace FI
using FI::read;

constexpr int MultiTestCases = 0;

int Main()
{
    int n, m;
    std::cin >> n >> m;
    std::vector adj(n + 1, std::vector<std::pair<int, int>>{});
    for (int i = 0; i <= n - 1; ++i)
        adj[i].push_back({i + 1, 1});
    for (int i = 1; i <= m; ++i)
    {
        int l, r, s;
        std::cin >> l >> r >> s;
        adj[l - 1].push_back({r, s});
        adj[r].push_back({l - 1, -s});
    }

    std::queue<int> q{};
    q.push(0);
    std::vector<int> flag(n + 1);
    flag[0] = true;
    std::vector<ll> dist(n + 1, 0);
    dist[0] = 0;
    std::vector<int> cnt(n + 1);
    cnt[0] = 1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (cnt[u] > n + n)
            return printf("-1\n"), 0;
        flag[u] = false;
        for (int i = 0; i < adj[u].size(); ++i)
        {
            int v = adj[u][i].first, w = adj[u][i].second;
            if (dist[v] < dist[u] + w)
            {
                dist[v] = dist[u] + w;
                if (!flag[v])
                    q.push(v), cnt[v]++;
            }
        }
    }
    std::cout << dist[n] << "\n";
    return 0;
}

int main()
{
    if constexpr (InputStream == 1)
        std::ios::sync_with_stdio(false);

    int TestCases = 1;
    if constexpr (MultiTestCases == 1)
    {
        if constexpr (InputStream == 1)
            std::cin >> TestCases;
        else
            scanf("%d", &TestCases);
    }

    while (TestCases--)
        Main();
    return 0;
}