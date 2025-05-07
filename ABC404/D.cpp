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

constexpr bool InputStream = 1;

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
    int N, M;
    std::cin >> N >> M;
    std::vector<int> c(N);
    for (int i = 0; i < N; ++i)
        std::cin >> c[i];
    std::vector a(N, std::vector<int>{});
    int all = 1;
    for (int i = 0; i < N; ++i)
        all *= 3;
    for (int i = 1; i <= M; ++i)
    {
        int k;
        std::cin >> k;
        for (int j = 1; j <= k; ++j)
        {
            int z;
            std::cin >> z;
            a[z - 1].push_back(i);
        }
    }

    ll ans = INF<ll>;
    for (int mask = 1; mask < all; ++mask)
    {
        ll cost = 0;
        std::vector<int> cnt(M + 1);
        int tmp = mask;
        for (int i = 0; i < N; ++i)
        {
            int t = tmp % 3;
            tmp /= 3;
            for (int j : a[i])
                cnt[j] += t;
            cost += t * c[i];
        }
        bool ok = true;
        for (int j = 1; j <= M; ++j)
            if (cnt[j] < 2)
            {
                ok = false;
                break;
            }
        if (ok)
            ans = std::min(cost, ans);
    }
    std::cout << ans << std::endl;
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