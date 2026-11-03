/**
 * Author: Joaquin Lopez
 * Date: 2026-11-03
 * Description: TODO
 */
#pragma once

constexpr int MIN = numeric_limits<int>::min();

struct Line {
  int a, b;
  int operator()(int x) const { return a * x + b; }
  explicit Line(int a = 0, int b = MIN)
    : a{a}, b{b} {}
};

constexpr int MIN_RANGE = -1e5;
constexpr int MAX_RANGE = 1e5;
Line ln[4 * (MAX_RANGE - MIN_RANGE)];

void insert(Line L, int cur = 0, int l = MIN_RANGE, int r = MAX_RANGE + 1) {
    int m = midpoint(l, r);
    if (r - l == 1) { if (ln[cur](l) < L(l)) ln[cur] = L; return; }

    if (ln[cur](m) < L(m)) swap(ln[cur], L);
    if (ln[cur](l) < L(l)) insert(L, 2 * cur + 1, l, m);
    if (ln[cur](r - 1) < L(r - 1)) insert(L, 2 * cur + 2, m, r);
}

int query(int x, int cur = 0, int l = MIN_RANGE, int r = MAX_RANGE + 1) {
    int m = midpoint(l, r);
    if (r - l == 1) return ln[cur](x);
    if (l <= x and x < m) return max(ln[cur](x), query(x, 2 * cur + 1, l, m));
    else                  return max(ln[cur](x), query(x, 2 * cur + 2, m, r));
}
