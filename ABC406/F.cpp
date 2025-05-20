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

template <class T, typename Merge = std::plus<T>>
struct FenwickTree
{
    std::vector<T> fwt;
    const Merge merge{};
    int n;

#ifndef lowbit
    inline int lowbit(int x) const
    {
        return (x & (-x));
    }
#endif

    FenwickTree(int _n) : n(_n), fwt(_n + 1)
    {
    }

    void modify(int pos, T delta)
    {
        if (pos == 0)
            return fwt[0] = merge(fwt[0], delta), void();
        for (int i = pos; i <= n; i += lowbit(i))
            fwt[i] = merge(fwt[i], delta);
    }

    T query(int pos) const
    {
        T res{};
        if (pos < 0)
            return res;
        pos = std::min(pos, n);
        for (int i = pos; i; i -= lowbit(i))
            res = merge(res, fwt[i]);
        res = merge(res, fwt[0]);
        return res;
    }
};

int Main()
{
    int n;
    read(n);
    std::vector adj(n + 1, std::vector<int>{});
    std::vector fa(n + 1, 0);
    std::vector<std::pair<int, int>> e(n);
    std::vector in(n + 1, 0);
    std::vector out(n + 1, 0);

    for (int i = 1; i < n; ++i)
    {
        auto &[u, v] = e[i];
        read(u, v);
        adj[u].push_back(v), adj[v].push_back(u);
    }

    fa[1] = 0;
    int cnt = 0;
    auto dfs = [&](auto &&self, int u) -> void
    {
        in[u] = ++cnt;
        if (fa[u] != 0)
            adj[u].erase(std::find(adj[u].begin(), adj[u].end(), fa[u]));

        for (int v : adj[u])
        {
            fa[v] = u;
            self(self, v);
        }
        out[u] = cnt;
    };

    dfs(dfs, 1);

    FenwickTree<ll> fwt(n);
    for (int i = 1; i <= n; ++i)
        fwt.modify(i, 1);
    int q;
    read(q);
    while (q--)
    {
        int t, u, w;
        read(t, u);
        if (t == 1)
        {
            read(w);
            fwt.modify(in[u], w);
        }
        else
        {
            auto [x, y] = e[u];
            if (fa[y] == x)
                std::swap(x, y);
            auto all = fwt.query(n);
            auto tree = fwt.query(out[x]) - fwt.query(in[x] - 1);
            printf("%lld\n", std::abs(tree - (all - tree)));
        }
    }
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