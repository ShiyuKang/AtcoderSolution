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
    int n;
    read(n);
    std::vector<int> a(n + 2);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    a[0] = a[n + 1] = INF<int>;

    std::stack<int> stack{};
    std::vector<int> ls(n + 1), rs(n + 1);

    stack.push(0);
    for (int i = 1; i <= n + 1; ++i)
    {
        while (stack.size() && a[stack.top()] <= a[i])
        {
            rs[stack.top()] = i;
            stack.pop();
        }
        if (i > n)
            break;
        ls[i] = stack.top();
        stack.push(i);
    }

    std::vector<ll> ans(n + 2);
    for (int i = 1; i <= n; ++i)
    {
        int L = i - ls[i], R = rs[i] - i;
        if (L <= R)
        {
            for (int j = ls[i] + 1; j <= i; ++j)
            {
                int mn = i - j + 1, mx = rs[i] - j + 1;
                ans[mn] += a[i], ans[mx] -= a[i];
            }
        }
        else
        {
            for (int j = i; j < rs[i]; ++j)
            {
                int mn = j - i + 1, mx = j - ls[i] + 1;
                ans[mn] += a[i], ans[mx] -= a[i];
            }
        }
    }

    for (int i = 1; i <= n; ++i)
        ans[i] += ans[i - 1];

    for (int i = 1; i <= n; ++i)
        printf("%lld\n", ans[i]);

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