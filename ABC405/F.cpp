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
    int n, m;
    read(n, m);
    FenwickTree<ll> fwt(n + n + n + n);
    std::vector evt(n + n + n + n + 1, std::vector<int>{});
    for (int i = 1; i <= m; ++i)
    {
        int a, b;
        read(a, b);
        evt[b].push_back(a);
        evt[a + n + n].push_back(b);
        evt[b + n + n].push_back(a + n + n);
    }

    int q;
    read(q);
    std::vector<std::pair<int, int>> qry(q + 1);

    std::vector adj(n + n + n + n + 1, std::vector<std::pair<int, int>>{});
    for (int i = 1; i <= q; ++i)
    {
        int c, d;
        read(c, d);
        adj[d].push_back({c, i});
        adj[c + n + n].push_back({d, i});
    }
    std::vector<int> ans(q + 1, m);
    for (int i = 1; i <= n + n + n + n; ++i)
    {
        for (int v : evt[i])
        {
            fwt.modify(v, 1);
        }

        for (auto [l, idx] : adj[i])
        {
            ans[idx] -= fwt.query(i) - fwt.query(l - 1);
        }
    }

    for (int i = 1; i <= q; ++i)
        printf("%d\n", ans[i]);
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