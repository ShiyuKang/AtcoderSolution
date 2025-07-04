# A、B、C

直接模拟

C题从最末一个数倒着模拟

# D

因为只有  $HW/2 $ 个位置可以放骨牌，  $HW $ 不超过20

大概估量了一下这个复杂度，可以直接爆搜

官方题解似乎给出了严格的证明

# E

首先有一个很自然的DP解法：  $dp[i][j] $ 表示前  $i $ 个数目前有  $j $ 个左括号的最大收益。

注意为了维持括号序列的合法性，  $j\geq i/2 $ 

这是一个背包，但是相当于每个物品的体积都是1。

一般这样的背包可以转化为贪心。

考虑括号序列的意义，  $j\geq i/2 $ ，代表着每放两个空位，你必然要填一个左括号进来。

不妨直接模拟这个过程。首先最左端一定是左括号没毛病

接下来每两个空位你必然要放一个左括号，那么我的最优值肯定是值最大的那个位置。

相当于一堆位置中取最大，用堆来模拟这个过程即可

# F

经典笛卡尔树启发式合并问题。

原题在CF212D

考虑 $a[i] $作为最大值会给哪些滑动窗口做出多少贡献。

单调栈处理 $a[i] $作为最大值的区间 $l[i],r[i] $。

接下来我们发现只要滑动窗口的左端点在 $[l[i],i] $，右端点在 $[i,r[i]] $， $a[i] $就会为这样的滑动窗口做出一次贡献。

假设我枚举左端点的位置 $p $，那么右端点的可行位置是一个区间，对应的滑动窗口长度也是一个区间 $[i-p+1,r[i]-p+1] $， $a[i] $都会为这些长度的滑动窗口做贡献。

假设枚举右端点的位置 $p $，情况是镜像的。

所以我可以选择枚举任意一个端点，来做区间加（转化为差分数组上的单点加）。

一个理所当然的想法是选择 $[l[i],i] $和 $[i,r[i]] $中短的那个区间来枚举端点。

这样做的复杂度不超过 $O(nlog_2n) $。

因为单调栈会形成一棵笛卡尔树。 $a[i] $的左子树是 $[l[i], i] $这个区间的，右儿子是 $[i, r[i]] $这个区间。

我们去枚举短的区间端点，相当于在笛卡尔树上，每棵子树都选择最小的那个儿子子树来枚举。这就是一次启发式合并的过程。

# G

如果 $HW\leq 300 $，其实可以选择轮廓线DP。

这里 $HW\leq 2000 $，可能有一些特殊的解法。

考虑这个棋盘上的日字覆盖，其实有点类似于二分图——把棋盘黑白染色，一个骨牌必然会覆盖一个黑色格子和一个白色格子。

一个骨牌的覆盖带来的减益就是两个格子的和。

我们想让收益最大，必然就是减益最小。

于是就变成了一个二分图匹配问题，要求匹配出的权值和最小，但是不要求匹配数量达到最大。

换句话说，求解的是一个二分图上的最小费用可行流，但不是最大流。

我们可以枚举所有可能的最大流量，然后求最小费用最大流，最后取全局最小值即可。

考虑复杂度的话，因为流量不超过 $HW/2 $，且枚举流量相当于是在残量网络中加边。因此总复杂度等价于对原二分图做最小费用最大流。

这里还有一个技巧——因为一对匹配带权的边只有一条，所以我们可以所有边都加一个基础权值保证每个权值都是正数。这样费用流的最短路部分就可以Dijkstra了。

当然直接原始对偶做费用流就不用搞这些了...

复杂度是 $O(HW/2 * HW log_2 {HW}) $

