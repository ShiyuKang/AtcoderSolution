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

#include <algorithm>

int Main()
{
    int n;
    read(n);
    std::vector dp(2001, std::array<int, 3>{(int)1e9, (int)1e9, (int)1e9});
    std::vector best(2001, std::array<std::string, 3>{});

    dp[1][0] = 1;
    dp[11][0] = 2;
    dp[111][0] = 3;
    dp[1111][0] = 4;
    best[1][0] = "1", best[11][0] = "11", best[111][0] = "111", best[1111][0] = "1111";
    std::vector<int> vis(n + 1);

    auto solve = [&](auto &&self, int x) -> void
    {
        if (vis[x])
            return;
        vis[x] = true;

        for (int i = 1; i <= x / 2; ++i)
        {
            self(self, i), self(self, x - i);
            for (int p = 0; p < 3; ++p)
                for (int q = 0; q < 3; ++q)
                {
                    if (dp[i][p] + dp[x - i][q] + 1 < dp[x][1])
                    {
                        dp[x][1] = std::min(dp[x][1], dp[i][p] + dp[x - i][q] + 1);
                        best[x][1] = best[i][p] + "+" + best[x - i][q];
                    }
                }
            // dp[x][1] = std::min(dp[x][1], std::min({dp[i][0], dp[i][1], dp[i][2]}) + std::min({dp[x - i][0], dp[x - i][1], dp[x - i][2]}) + 1);
        }

        for (int i = 2; i * i <= x; ++i)
        {
            if (x % i == 0)
            {
                self(self, i);
                self(self, x / i);
                for (int p = 0; p < 3; ++p)
                    for (int q = 0; q < 3; ++q)
                    {
                        int lb = p == 1, rb = q == 1;
                        if (dp[i][p] + dp[x / i][q] + lb * 2 + rb * 2 + 1 < dp[x][2])
                        {
                            dp[x][2] = dp[i][p] + dp[x / i][q] + lb * 2 + rb * 2 + 1;
                            if (lb)
                                best[x][2] = std::string("(");
                            else
                                best[x][2] = "";
                            best[x][2] += best[i][p];
                            if (lb)
                                best[x][2] += std::string(")");
                            best[x][2] += std::string("*");
                            if (rb)
                                best[x][2] += std::string("(");
                            best[x][2] += best[x / i][q];
                            if (rb)
                                best[x][2] += std::string(")");
                        }
                    }
            }
        }
    };

    solve(solve, n);
    std::string ans;
    ll res = 1e9;
    for (int i = 0; i < 3; ++i)
        if (dp[n][i] < res)
            ans = best[n][i], res = dp[n][i];
    std::cout << ans << "\n";
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