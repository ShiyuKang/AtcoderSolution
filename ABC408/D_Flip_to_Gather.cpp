#include <bits/stdc++.h>
#include <vector>

using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

const int mod = 998244353;
const double PI = std::numbers::pi;
std::mt19937 rng(std::random_device{}());

template <class T> constexpr T lowbit(T x) noexcept
{
    return x & (-x);
};

template <class T> struct Inf
{
};

template <> struct Inf<int>
{
    constexpr static int v = 1e9;
};

template <> struct Inf<ll>
{
    constexpr static ll v = 1e18;
};

template <typename T> constexpr T INF = Inf<T>::v;

template <typename T>
requires std::is_integral_v<T>
constexpr int msb(T x)
{
    using UT = std::make_unsigned_t<T>;
    return std::numeric_limits<UT>::digits - std::countl_zero(UT(x)) - 1;
}

constexpr bool InputStream = 1;

namespace FI
{
char B[1 << 16], *S = B, *T = B;
inline char getc()
{
    return S == T && (T = (S = B) + fread(B, 1, 1 << 16, stdin), S == T) ? EOF : *S++;
}

template <typename Tp, typename... Types>
requires(InputStream == false) inline void read(Tp &o, Types &...Args)
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

inline bool eof()
{
    auto ch = S == T && (T = (S = B) + fread(B, 1, 1 << 16, stdin), S == T) ? EOF : *S;
    return ch == EOF;
}
} // namespace FI
using FI::read;

enum class MultiTestCaseType
{
    NONE,
    CNT,
    END,
};

constexpr MultiTestCaseType MultiTestCases = MultiTestCaseType::CNT;

int Main()
{
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    s = "#" + s;

    std::vector<int> sum(n + 1);
    for (int i = 1; i <= n; ++i)
        sum[i] = sum[i - 1] + s[i] - '0';
    std::vector<int> f(n + 1);
    for (int i = 1; i <= n; ++i)
        f[i] = i - 2 * sum[i];

    auto ans = INF<int>;
    int max = 0;
    for (int r = 1; r <= n; ++r)
    {
        //(r - l + 1) - (sum[r] - sum[l - 1]) + (sum[n] - sum[r]) + sum[l-1]
        // r - 2*sum[r] - (l - 1 - 2 * sum[l-1]) + sum[n]
        max = std::max(f[r], max);
        ans = std::min(ans, sum[n] + f[r] - max);
    }

    printf("%d\n", ans);

    return 0;
}

int main()
{
    if constexpr (InputStream == 1)
        std::ios::sync_with_stdio(false);

    auto eof = [&]() -> bool {
        if constexpr (InputStream == 1)
            return std::cin.eof();
        else
            return FI::eof();
    };

    int TestCases = 1;
    if constexpr (MultiTestCases == MultiTestCaseType::CNT)
    {
        if constexpr (InputStream == 1)
            std::cin >> TestCases;
        else
            scanf("%d", &TestCases);
    }

    while (TestCases-- && !eof())
        Main();

    return 0;
}