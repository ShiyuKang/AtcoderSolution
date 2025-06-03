#include <bits/stdc++.h>

using ll = long long;

auto solve(ll A, ll B, ll C, ll D) -> std::pair<ll, ll>
{
    auto x = A / B;

    // std::cerr << A << " " << B << " " << C << " " << D << std::endl;
    if (C - x * D > D)
        return {x + 1, 1};
    auto [p, q] = solve(D, C - x * D, B, A - x * B);
    // std::cerr << p << " " << q << std::endl;

    return {q + p * x, p};
}

int Main()
{
    ll A, B, C, D;
    scanf("%lld%lld%lld%lld", &A, &B, &C, &D);
    auto [p, q] = solve(A, B, C, D);
    std::cout << q << std::endl;
    return 0;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
        Main();
}