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

struct Info
{
    ll mn = INF<int>;
    ll mx = -INF<int>;
    ll sum = 0;
    int size = 0;
};

Info operator+(const Info &a, const Info &b)
{
    Info res;
    res.mn = std::min(a.mn, b.mn);
    res.mx = std::max(a.mx, b.mx);
    res.sum = a.sum + b.sum;
    res.size = a.size + b.size;
    return res;
}

struct Tag
{
    ll tag = -INF<int>;
    ll delta = 0;
};

void apply(Info &a, const Tag &b)
{
    if (b.tag != -INF<int>)
    {
        a.mn = a.mx = b.tag;
        a.sum = 1ll * b.tag * a.size;
    }
    if (b.delta)
    {
        a.mn += b.delta, a.mx += b.delta;
        a.sum += 1ll * b.delta * a.size;
    }
}

void apply(Tag &a, const Tag &b)
{
    if (b.tag != -INF<int>)
        a.tag = b.tag, a.delta = 0;
    if (b.delta != 0)
        a.delta += b.delta;
}

template <typename Info, typename Tag, typename Merge = std::plus<Info>>
struct LazySegmentTree
{
    const int n;
    const Merge merge;
    struct node
    {
        Info info;
        Tag tag;
    };
    std::vector<node> tree;
    LazySegmentTree(int _n) : n(_n), merge(Merge()), tree(_n * 4 + 5)
    {
    }
    LazySegmentTree(std::vector<Info> &init, int _n) : LazySegmentTree(_n)
    {
        std::function<void(int, int, int)> build = [&](int p, int l, int r)
        {
            if (l == r)
            {
                tree[p].info = init[l];
                return;
            }
            int mid = (l + r) / 2;
            build(p << 1, l, mid);
            build(p << 1 | 1, mid + 1, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p)
    {
        tree[p].info = merge(tree[p << 1].info, tree[p << 1 | 1].info);
    }
    void apply(int p, const Tag &v)
    {
        ::apply(tree[p].info, v);
        ::apply(tree[p].tag, v);
    }
    void push(int p)
    {
        apply(p << 1, tree[p].tag);
        apply(p << 1 | 1, tree[p].tag);
        tree[p].tag = Tag();
    }
    void modify(int p, int l, int r, int x, const Info &v)
    {
        if (l == r)
            return tree[p].info = v, void();
        int mid = (l + r) >> 1;
        push(p);
        if (x <= mid)
            modify(p << 1, l, mid, x, v);
        else
            modify(p << 1 | 1, mid + 1, r, x, v);
        pull(p);
    }
    void modify(int p, const Info &v)
    {
        modify(1, 0, n, p, v);
    }
    Info query(int p, int l, int r, int x, int y)
    {
        if (l == x && r == y)
            return tree[p].info;
        int mid = (l + r) >> 1;
        push(p);
        if (y <= mid)
            return query(p << 1, l, mid, x, y);
        else if (x > mid)
            return query(p << 1 | 1, mid + 1, r, x, y);
        else
            return merge(query(p << 1, l, mid, x, mid), query(p << 1 | 1, mid + 1, r, mid + 1, y));
    }
    Info query(int l, int r)
    {
        return query(1, 0, n, l, r);
    }
    void apply(int p, int l, int r, int x, int y, const Tag &v)
    {
        if (l == x && r == y)
        {
            apply(p, v);
            return;
        }
        int mid = (l + r) >> 1;
        push(p);
        if (y <= mid)
            apply(p << 1, l, mid, x, y, v);
        else if (x > mid)
            apply(p << 1 | 1, mid + 1, r, x, y, v);
        else
            apply(p << 1, l, mid, x, mid, v), apply(p << 1 | 1, mid + 1, r, mid + 1, y, v);
        pull(p);
    }
    void apply(int l, int r, const Tag &v)
    {
        if (l > r)
            return;
        return apply(1, 0, n, l, r, v);
    }

    template <typename Func>
    int lower_bound(int p, int l, int r, Func &&f)
    {
        if (l == r)
        {
            if (f(tree[p].info))
                return l;
            else
                return l + 1;
        }

        push(p);
        int mid = (l + r) >> 1;
        if (f(tree[p * 2 + 1].info))
            return lower_bound(p * 2, l, mid, f);
        else
            return lower_bound(p * 2 + 1, mid + 1, r, f);
    }
    template <typename Func>
    int lower_bound(Func &&f)
    {
        return lower_bound(1, 0, n, f);
    }
};

int Main()
{
    constexpr int M = 1e5;
    int N, C, D;
    read(N, C, D);
    std::vector<int> X(N + 1);
    for (int i = 1; i <= N; ++i)
        read(X[i]);

    std::vector<Info> init(M + M);
    for (int i = 0; i <= M - 1; ++i)
        init[i] = {-C, -C, -C, 1};
    for (int i = M; i <= M + M - 1; ++i)
        init[i] = {C, C, C, 1};
    LazySegmentTree<Info, Tag> segment_tree(init, M * 2 - 1);
    ll fl = 1ll * M * C;
    std::vector<int> l(N + 1), r(N + 1);
    for (int i = 1; i <= N; ++i)
    {
        auto check_right = [&](const Info &info)
        {
            return info.mn > C;
        };
        r[i] = segment_tree.lower_bound(check_right);

        auto check_left = [&](const Info &info)
        {
            return info.mn >= -C;
        };

        l[i] = segment_tree.lower_bound(check_left) - 1;

        if (r[i] <= M + M - 1)
            segment_tree.apply(r[i], M + M - 1, {C, 0});
        r[i] = std::min(r[i], M + M);
        if (0 <= l[i])
        {
            ll pre = segment_tree.query(0, l[i]).sum;
            segment_tree.apply(0, l[i], {-C, 0});
            ll after = 1ll * (l[i] + 1) * (-C);
            fl -= after - pre;
        }
        l[i] = std::max(0, l[i] + 1);

        // printf("%d %d\n", l[i] - M, r[i] - M);

        if (0 <= X[i] - 1 + M)
            segment_tree.apply(0, X[i] - 1 + M, {-INF<int>, -D});
        if (X[i] + M <= M + M - 1)
            segment_tree.apply(X[i] + M, M + M - 1, {-INF<int>, D});
        fl += 1ll * std::abs(X[i] + M) * D;
    }

    ll ans = fl;
    int best = 0;
    for (int i = 0; i < M + M; ++i)
    {
        if (auto tmp = fl + segment_tree.query(0, i).sum; tmp < ans)
        {
            ans = tmp;
            best = i + 1;
        }
    }

    std::vector<int> b(N + 1);
    for (int i = N - 1; i >= 1; --i)
    {
        b[i + 1] = best;
        best = std::max(l[i + 1], best);
        best = std::min(r[i + 1], best);
    }
    b[1] = best;

    printf("%lld\n", ans);
    for (int i = 1; i <= N; ++i)
        printf("%d%c", b[i] - M, " \n"[i == N]);
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