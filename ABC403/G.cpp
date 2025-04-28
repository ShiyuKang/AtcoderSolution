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

template <typename Info, typename Merge = std::plus<Info>>
struct Treap
{
    struct node
    {
        Info info;
        Info cur;
        int ch[2], rnk;
        int val;

        node()
        {
            ch[0] = ch[1] = 0;
            rnk = rng();
        }
    };

    int n;
    const Merge merge;
    std::vector<node> tree;

    Treap(int n_) : n(n_), merge(Merge()), tree(n_ + 1)
    {
    }

    void pull(int u)
    {
        if (!u)
            return;
        tree[u].info = merge(merge(tree[tree[u].ch[0]].info, tree[u].cur), tree[tree[u].ch[1]].info);
    }

    inline void split_by_val(int x, int val, int rt[2])
    {
        if (x == 0)
            return rt[0] = rt[1] = 0, void();

        int nrt[2] = {0, 0};
        bool flag = val < tree[x].val;
        split_by_val(tree[x].ch[flag ^ 1], val, nrt);
        tree[x].ch[flag ^ 1] = nrt[flag];
        rt[flag ^ 1] = nrt[flag ^ 1];
        rt[flag] = x;
        pull(x);
        return;
    }

    int merging(int u, int v)
    {
        if (u == 0 || v == 0)
            return u | v;

        if (tree[u].rnk < tree[v].rnk)
        {
            tree[u].ch[1] = merging(tree[u].ch[1], v);
            return pull(u), u;
        }
        else
        {
            tree[v].ch[0] = merging(u, tree[v].ch[0]);
            return pull(v), v;
        }
    }

    int newnode(const Info &info, int val)
    {
        tree.emplace_back();
        tree.back().cur = info;
        tree.back().val = val;
        return tree.size() - 1;
    }
};

struct Info
{
    int size = 0;
    std::array<ll, 2> val{};
};

struct Merge
{
    Info operator()(const Info &lhs, const Info &rhs) const
    {
        Info res = lhs;
        res.size += rhs.size;
        auto v = rhs.val;
        if (lhs.size % 2 == 1)
            std::swap(v[0], v[1]);
        res.val[0] += v[0];
        res.val[1] += v[1];
        return res;
    }
};

int Main()
{
    int q;
    read(q);
    ll z = 0;
    Treap<Info, Merge> treap(0);
    int root = 0;
    while (q--)
    {
        ll x;
        read(x);
        x += z;
        x %= INF<int>;
        x += 1;
        Info info{1, {0, x}};
        int rt[2];
        treap.split_by_val(root, x, rt);
        int mid = treap.newnode(info, x);
        treap.pull(mid);

        root = treap.merging(rt[0], mid);
        root = treap.merging(root, rt[1]);

        z = treap.tree[root].info.val[1];
        printf("%lld\n", z);
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