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

constexpr bool InputStream = 0;

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

template <typename cap_type = int, typename cost_type = ll>
struct CostFlow
{
    constexpr static int INF = 1e9;

    struct Edge
    {
        int v;
        cap_type c;
        cost_type f;
        Edge(int v, cap_type c, cost_type f) : v(v), c(c), f(f) {}
    };
    const int n;
    std::vector<Edge> e;
    std::vector<std::vector<int>> g;
    std::vector<cost_type> h, dis;
    std::vector<int> pre;
    bool dijkstra(int s, int t)
    {
        dis.assign(n, std::numeric_limits<cost_type>::max());
        pre.assign(n, -1);
        std::priority_queue<std::pair<cost_type, int>, std::vector<std::pair<cost_type, int>>, std::greater<std::pair<cost_type, int>>> que;
        dis[s] = 0;
        que.emplace(0, s);
        while (!que.empty())
        {
            auto [d, u] = que.top();
            que.pop();
            if (dis[u] < d)
                continue;
            for (int i : g[u])
            {
                auto [v, c, f] = e[i];
                if (c > 0 && dis[v] > d + h[u] - h[v] + f)
                {
                    dis[v] = d + h[u] - h[v] + f;
                    pre[v] = i;
                    que.emplace(dis[v], v);
                }
            }
        }
        return dis[t] != std::numeric_limits<cost_type>::max();
    }
    CostFlow(int n) : n(n), g(n) {}
    void add_edge(int u, int v, cap_type cap, cost_type f)
    {

        g[u].push_back(e.size());
        e.emplace_back(v, cap, f);
        g[v].push_back(e.size());
        e.emplace_back(u, 0, -f);
    }
    std::pair<cap_type, cost_type> flow(int s, int t)
    {
        cap_type flow = 0;
        cost_type cost = 0;
        h.assign(n, 0);
        while (dijkstra(s, t))
        {
            for (int i = 0; i < n; ++i)
                h[i] += dis[i];
            auto aug = std::numeric_limits<cap_type>::max();
            for (int i = t; i != s; i = e[pre[i] ^ 1].v)
                aug = std::min(aug, e[pre[i]].c);
            for (int i = t; i != s; i = e[pre[i] ^ 1].v)
            {
                e[pre[i]].c -= aug;
                e[pre[i] ^ 1].c += aug;
            }
            flow += aug;
            cost += cost_type(aug) * h[t];
        }
        return {flow, cost};
    }
};

int Main()
{
    int h, w;
    read(h, w);
    ll sum = 0;

    std::vector a(h + 1, std::vector<ll>(w + 1));
    for (int i = 1; i <= h; ++i)
        for (int j = 1; j <= w; ++j)
            read(a[i][j]), sum += a[i][j];

    CostFlow G(h * w + 3);
    int S = 0, T = h * w + 1;
    int SS = h * w + 2;

    for (int i = 1; i <= h; ++i)
        for (int j = 1; j <= w; ++j)
        {
            if ((i + j) % 2 == 0)
                G.add_edge(S, (i - 1) * w + j, 1, 0);
            else
                G.add_edge((i - 1) * w + j, T, 1, 0);
        }
    constexpr ll base = 2e12;
    for (int i = 1; i <= h; ++i)
        for (int j = 1; j <= w; ++j)
        {
            if ((i + j) % 2 == 0)
            {
                if (j + 1 <= w)
                    G.add_edge((i - 1) * w + j, (i - 1) * w + j + 1, 1, a[i][j] + a[i][j + 1]);
                if (j - 1 >= 1)
                    G.add_edge((i - 1) * w + j, (i - 1) * w + j - 1, 1, a[i][j] + a[i][j - 1]);
                if (i + 1 <= h)
                    G.add_edge((i - 1) * w + j, i * w + j, 1, a[i][j] + a[i + 1][j]);
                if (i - 1 >= 1)
                    G.add_edge((i - 1) * w + j, (i - 2) * w + j, 1, a[i][j] + a[i - 1][j]);
            }
        }

    ll cost = 0;
    ll ans = 0;
    for (int i = 1; i <= h * w; ++i)
    {
        G.add_edge(SS, S, 1, 0);
        auto [_, delta] = G.flow(SS, T);
        cost += delta;
        ans = std::min(cost, ans);
    }

    ans = sum - ans;
    printf("%lld\n", ans);
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