#include <algorithm>
#include <bits/stdc++.h>
#include <vector>

struct SegmentTree
{
    struct node
    {
        int mx = -1;
    };

    node merge(const node &lhs, const node &rhs)
    {
        return {std::max(lhs.mx, rhs.mx)};
    }
    std::vector<node> tree;

    void insert(int p, int l, int r, int x, int v)
    {
        if (l == r)
            return tree[p].mx = v, void();

        auto mid = (l + r) >> 1;
        if (x <= mid)
            insert(p + p, l, mid, x, v);
        else
            insert(p + p + 1, mid + 1, r, x, v);

        tree[p] = merge(tree[p + p], tree[p + p + 1]);
    }

    int query(int p, int l, int r, int ql, int qr)
    {
        if (l == ql && r == qr)
            return tree[p].mx;
        auto mid = (l + r) >> 1;

        if (qr <= mid)
            return query(p + p, l, mid, ql, qr);
        else if (ql > mid)
            return query(p + p + 1, mid + 1, r, ql, qr);
        else
            return std::max(query(p + p, l, mid, ql, mid), query(p + p + 1, mid + 1, r, mid + 1, qr));
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n, d, r;
    std::cin >> n >> d >> r;

    std::vector<int> h(n + 1);
    for (int i = 1; i <= n; ++i)
        std::cin >> h[i];

    std::vector<int> p(n + 1);
    for (int i = 1; i <= n; ++i)
        p[h[i]] = i;

    std::vector<int> dp(n + 1);
    dp[1] = 0;
    SegmentTree segment_tree;
    segment_tree.tree.resize(4 * n + 5);
    for (int i = 2; i <= n; ++i)
    {
        if (int line = i - d; line > 0)
            segment_tree.insert(1, 1, n, p[line], dp[line]);
        dp[i] = segment_tree.query(1, 1, n, std::max(1, p[i] - r), std::min(n, p[i] + r)) + 1;
    }

    int ans = *std::max_element(dp.begin() + 1, dp.end());
    std::cout << ans << "\n";
}