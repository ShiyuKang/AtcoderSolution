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
    int n, t, m, k;
    std::cin >> n >> t >> m >> k;

    std::vector dp(t + 1, std::vector<double>(k + 1));
    std::vector dp2(m + 1, std::vector<double>(m + 1));
    dp2[0].assign(m + 1, -1e18);
    dp2[0][0] = 0;
    dp[0][0] = 1.0;
    for (int i = 1; i <= t; ++i)
    {
        dp[i][0] = 1.0;
        for (int j = 1; j <= k; ++j)
        {
            for (int x = 1; x <= m; ++x)
            {
                for (int z = 1; z <= m; ++z)
                {
                    dp2[x][z] = -1e18;
                    for (int y = 1; y <= z; ++y)
                        dp2[x][z] = std::max(dp2[x][z], dp2[x - 1][z - y] + dp[i - 1][std::max(0, j - y)]);
                }
            }
            for (int x = 1; x <= std::min(n, m); ++x)
                dp[i][j] = std::max(dp[i][j], (dp2[x][m] + (n - x) * dp[i - 1][j]) / n);
        }
    }
    printf("%.9lf\n", dp[t][k]);
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