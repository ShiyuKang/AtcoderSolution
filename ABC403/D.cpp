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

int Main()
{
    int n, d;
    read(n, d);
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    if (d == 0)
    {
        std::sort(a.begin() + 1, a.end());
        int ans = std::unique(a.begin() + 1, a.end()) - a.begin() - 1;
        printf("%d\n", n - ans);
        return 0;
    }
    int mx = *std::max_element(a.begin() + 1, a.end());
    std::vector<int> cnt(1e6 + 1);
    for (int i = 1; i <= n; ++i)
        cnt[a[i]]++;
    std::vector dp(1e6 + 1, std::array<int, 2>{});

    for (int i = 0; i < d; ++i)
        dp[i][1] = cnt[i], dp[i][0] = 0;

    for (int i = d; i <= mx; ++i)
    {
        dp[i][1] = dp[i - d][0] + cnt[i];
        dp[i][0] = std::max(dp[i - d][0], dp[i - d][1]);

        // printf("dp[%d] = {%d %d}\n", i, dp[i][0], dp[i][1]);
    }

    int ans = n;
    for (int i = mx; i >= mx - d + 1 && i >= 0; --i)
    {
        ans -= std::max(dp[i][0], dp[i][1]);
    }
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