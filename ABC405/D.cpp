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
    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> s(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> s[i];
        s[i] = " " + s[i];
    }

    std::queue<std::pair<int, int>> q;
    std::vector d(n + 1, std::vector<int>(m + 1, INF<int>));
    std::vector from(n + 1, std::vector<int>(m + 1)); // 0,1,2,3
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (s[i][j] == 'E')
            {
                d[i][j] = 0;
                q.push({i, j});
            }

    std::array<std::pair<int, int>, 4> delta{std::pair{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    std::array<char, 4> c{'v', '>', '<', '^'};
    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i)
        {
            auto [dx, dy] = delta[i];
            int nx = x + dx, ny = y + dy;
            if (nx <= 0 || nx > n || ny <= 0 || ny > m)
                continue;
            if (s[nx][ny] == '.' && d[nx][ny] == INF<int>)
            {
                d[nx][ny] = d[x][y] + 1;
                from[nx][ny] = i;
                q.push({nx, ny});
            }
        }
    }

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (s[i][j] == '.')
                putchar(c[from[i][j]]);
            else
                putchar(s[i][j]);
        }

        putchar('\n');
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