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

std::array<int, 26> trie[1000000 + 5];
bool end[1000005];
int sum[1000005];

int Main()
{
    int q;
    std::cin >> q;
    int rx = 1, ry = 2;

    int cnt = 2;
    auto insert = [&](const std::string &s, int root)
    {
        int p = root;
        for (int i = 0; i < s.length(); ++i)
        {
            if (!trie[p][s[i] - 'a'])
                trie[p][s[i] - 'a'] = ++cnt;
            sum[p]++;
            p = trie[p][s[i] - 'a'];
        }
        sum[p]++;
        end[p] = true;
    };

    auto qx = [&](const std::string &s) -> bool
    {
        int p = rx;
        for (int i = 0; i < s.length(); ++i)
        {
            if (!trie[p][s[i] - 'a'])
                return true;
            p = trie[p][s[i] - 'a'];
            if (end[p])
                return false;
        }
        return true;
    };

    auto qy = [&](const std::string &s)
    {
        int p = ry;
        for (int i = 0; i < s.length(); ++i)
        {
            if (!trie[p][s[i] - 'a'])
                return;
            p = trie[p][s[i] - 'a'];
        }
        int q = ry;
        for (int i = 0; i < s.length(); ++i)
        {
            sum[q] -= sum[p];
            if (trie[q][s[i] - 'a'] == p)
                trie[q][s[i] - 'a'] = 0;
            else
                q = trie[q][s[i] - 'a'];
        }
    };

    while (q--)
    {
        int t;
        std::string s;
        std::cin >> t >> s;
        if (t == 1)
        {
            qy(s);
            insert(s, rx);
        }
        if (t == 2)
        {
            if (qx(s))
                insert(s, ry);
        }

        printf("%d\n", sum[ry]);
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