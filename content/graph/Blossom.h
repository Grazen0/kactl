/**
 * Author: https://codeforces.com/blog/entry/92339?#comment-810242
 * Description: Matching for general graphs.
 * Time: O(nm), fast in practice
 */
#pragma once

vi blossom(vector<vi>& g) {
  int n = sz(g), t = -1;
  vi m(n, -1), l(n), p(n), o(n), b(n, -1), q;
  auto lca = [&](int x, int y) {
    for (t++; ; swap(x, y)) {
      if (x == -1) continue;
      if (b[x] == t) return x;
      b[x] = t;
      x = (m[x] == -1 ? -1 : o[p[m[x]]]);
    }
  };
  auto blossom = [&](int v, int w, int a) {
    while (o[v] != a) {
      p[v] = w; w = m[v];
      if (l[w] == 1) l[w] = 0, q.push_back(w);
      o[v] = o[w] = a; v = p[w];
    }
  };
  auto augment = [&](int v) {
    while (v != -1) {
      int pv = p[v], nv = m[pv];
      m[v] = pv; m[pv] = v; v = nv;
    }
  };
  auto bfs = [&](int r) {
    fill(all(l), -1); iota(all(o), 0); q.clear();
    l[r] = 0; q.push_back(r);
    rep(i, 0, sz(q)) {
      int v = q[i];
      for (auto x : g[v]) {
        if (l[x] == -1) {
          l[x] = 1; p[x] = v;
          if (m[x] == -1) return augment(x), 1;
          l[m[x]] = 0; q.push_back(m[x]);
        } else if (l[x] == 0 && o[v] != o[x]) {
          int a = lca(o[v], o[x]);
          blossom(x, v, a); blossom(v, x, a);
        }
      }
    }
    return 0;
  };
  // Time halves if you start with (any) maximal matching.
  rep(i, 0, n) if (m[i] == -1) bfs(i);
  return m;
}
