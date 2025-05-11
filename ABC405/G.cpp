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

#include <atcoder/modint>
using modint = atcoder::modint998244353;

template <class T>
struct Combinatorics
{
    int n = 0;
    std::vector<T> fac;
    std::vector<T> invfac;
    std::vector<T> inv;
    Combinatorics(int _n = 0) : fac{1}, invfac{1}, inv{0}
    {
        init(_n);
    }

    void init(int m)
    {
        if (n >= m)
            return;
        fac.resize(m + 1), invfac.resize(m + 1), inv.resize(m + 1);

        for (int i = n + 1; i <= m; ++i)
            fac[i] = fac[i - 1] * i;
        invfac[m] = fac[m].inv();
        for (int i = m; i > n + 1; --i)
            invfac[i - 1] = invfac[i] * i;
        for (int i = m; i > n; --i)
            inv[i] = invfac[i] * fac[i - 1];
        n = m;
    }

    T operator()(int x, int y)
    {
        if (x < y)
            return 0;
        return fac[x] * invfac[y] * invfac[x - y];
    }
};

int Main()
{
    int n, q;
    read(n, q);
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    constexpr int unit = 500; // for 10^5

    struct Query
    {
        int l, r, x;
        int id;
        bool operator<(const Query &rhs) const
        {
            if (l / unit != rhs.l / unit)
                return l < rhs.l;
            if ((l / unit) & 1)
                return r < rhs.r; // 注意这里和下面一行不能写小于（大于）等于
            return r > rhs.r;
        }
    };
    std::vector<Query> Qry(q + 1);
    for (int i = 1; i <= q; ++i)
    {
        int l, r, x;
        read(l, r, x);
        Qry[i] = {l, r, x, i};
    }
    struct Block
    {
        int sum = 0;
        modint prod = 1;

        void add(int delta)
        {
            sum += delta;
        }
        void multi(modint p)
        {
            prod *= p;
        }
    };

    Combinatorics<modint> combinatorics(n);

    std::vector<Block> b(n / unit + 2);
    std::vector<int> blk(n + 1);
    for (int i = 1; i <= n; ++i)
        blk[i] = (i - 1) / unit + 1;

    std::sort(Qry.begin() + 1, Qry.end());
    std::vector<modint> ans(q + 1);
    std::vector<int> cnt(n + 1);
    auto add = [&](int x)
    {
        int id = blk[a[x]];
        b[id].add(1);
        b[id].multi(combinatorics.fac[cnt[a[x]]]);
        cnt[a[x]]++;
        b[id].multi(combinatorics.invfac[cnt[a[x]]]);
    };
    auto del = [&](int x)
    {
        int id = blk[a[x]];
        b[id].add(-1);
        b[id].multi(combinatorics.fac[cnt[a[x]]]);
        cnt[a[x]]--;
        b[id].multi(combinatorics.invfac[cnt[a[x]]]);
    };
    for (int i = 1, L = 1, R = 0; i <= q; ++i)
    {
        auto [l, r, x, id] = Qry[i];

        while (L > l)
            add(--L);
        while (R < r)
            add(++R);
        while (R > r)
            del(R--);
        while (L < l)
            del(L++);

        int sum = 0;
        modint p = 1;
        x--;
        if (x == 0)
            ans[id] = 1;
        else
        {
            for (int j = 1; j < blk[x]; ++j)
                sum += b[j].sum, p *= b[j].prod;
            for (int j = (blk[x] - 1) * unit + 1; j <= x; ++j)
            {
                sum += cnt[j];
                p *= combinatorics.invfac[cnt[j]];
            }
            // printf("%d\n", sum);
            ans[id] = combinatorics.fac[sum] * p;
            // perform query
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