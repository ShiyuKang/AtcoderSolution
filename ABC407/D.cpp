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
    int h, w;
    std::cin >> h >> w;

    std::vector a(h + 1, std::vector<ll>(w + 1));

    for (int i = 1; i <= h; ++i)
        for (int j = 1; j <= w; ++j)
            std::cin >> a[i][j];

    ll ans = 0;
    std::vector s(h + 1, std::vector<ll>(w + 1));
    auto search = [&](auto &&self, int x, int y, ll res) -> void
    {
        if (x > h)
            return ans = std::max(ans, res), void();

        // 0
        s[x][y] = 0;

        if (s[x - 1][y] == 1 || s[x][y - 1] == 2)
            self(self, x + (y == w), (y == w) ? 1 : y + 1, res);
        else
        {
            self(self, x + (y == w), (y == w) ? 1 : y + 1, res ^ a[x][y]);

            if (x != h)
                s[x][y] = 1, self(self, x + (y == w), (y == w) ? 1 : y + 1, res);

            if (y != w && s[x - 1][y + 1] != 1)
                s[x][y] = 2, self(self, x + (y == w), (y == w) ? 1 : y + 1, res);
        }
        s[x][y] = 0;
    };

    search(search, 1, 1, 0);
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