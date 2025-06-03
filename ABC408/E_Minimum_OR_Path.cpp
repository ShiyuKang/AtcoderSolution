#include <bits/stdc++.h>
#include <cstdint>
#include <vector>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n, m;
    std::cin >> n >> m;

    std::vector edges(m + 1, std::array<int, 3>{});

    for (int i = 1; i <= m; ++i)
    {
        auto &[u, v, w] = edges[i];
        std::cin >> u >> v >> w;
    }

    std::vector<int> flag(m + 1);

    std::vector<int> dsu(n + 1);

    std::function<int(int)> find = [&](int u) -> int {
        if (dsu[u] == u)
            return u;
        return dsu[u] = find(dsu[u]);
    };

    auto merge = [&](int u, int v) {
        u = find(u), v = find(v);
        dsu[u] = v;
    };

    int ans = 0;

    for (int p = 29; p >= 0; --p)
    {
        std::iota(dsu.begin(), dsu.end(), 0);
        for (int i = 1; i <= m; ++i)
        {
            if (flag[i])
                continue;
            auto [u, v, w] = edges[i];
            if (w >> p & 1)
                continue;

            merge(u, v);
        }
        if (find(1) == find(n))
        {
            for (int i = 1; i <= m; ++i)
                if (edges[i][2] >> p & 1)
                    flag[i] = true;
        }
        else
            ans |= (1 << p);
    }
    std::cout << ans << "\n";
}