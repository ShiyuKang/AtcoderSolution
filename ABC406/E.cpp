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

constexpr int MultiTestCases = 1;

#include <atcoder/modint>

using modint = atcoder::modint998244353;

modint dp[2][65][65][2];
bool vis[2][65][65];

std::array<modint, 2> solve(int n, int k, bool limit, std::vector<int> &digit)
{
    if (n == 0)
        return {k == 0, 0};

    if (vis[limit][n][k])
        return {dp[limit][n][k][0], dp[limit][n][k][1]};

    int mx = limit ? digit[n - 1] : 1;
    dp[limit][n][k][0] = 0, dp[limit][n][k][1] = 0;
    for (int i = 0; i <= mx; ++i)
    {
        if (k - i < 0)
            continue;
        auto ret = solve(n - 1, k - i, limit && (i == mx), digit);
        dp[limit][n][k][0] += ret[0];
        dp[limit][n][k][1] += ret[1] + ret[0] * (1ll << (n - 1)) * i;
    }

    vis[limit][n][k] = true;
    return {dp[limit][n][k][0], dp[limit][n][k][1]};
}

int Main()
{
    ll N, K;
    read(N, K);
    memset(vis[1], 0, sizeof(vis[1]));

    std::vector<int> p(65);
    for (int i = 0; N; N >>= 1)
    {
        p[i++] = N & 1;
    }
    // std::reverse(p.begin(), p.end());
    auto [_, ans] = solve(61, K, true, p);

    printf("%d\n", ans);
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