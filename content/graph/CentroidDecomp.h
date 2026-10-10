/**
 * Author: José Grayson
 * Date: 2026-10-09
 * License: CC0
 * Source: own work
 * Description: Centroid decomposition.
 * Time: O(N \log N) given O(N) processing per centroid
 * Status: tested
 */
#pragma once

const int MAXN = 2 * 1e5;
bool removed[MAXN];
vi adj[MAXN];
int tsz[MAXN];

void solve() {
  int n, k;
  // Read input

  auto get_sz = [&](auto &&self, int i, int p) -> int {
    tsz[i] = 1;
    for (int j : adj[i])
      if (j != p and not removed[j])
        tsz[i] += self(self, j, i);
    return tsz[i];
  };

  auto get_centroid = [&](auto &&self, int i, int p, int sz) -> int {
    for (int j : adj[i])
      if (j != p and not removed[j] and 2 * tsz[j] > sz)
        return self(self, j, i, sz);
    return i;
  };

  auto process = [&](int c) {
    // Init processing
    for (int j : adj[c]) {
      if (removed[j])
        continue;
      // Process subtree
    }
    // Clean up
  };

  auto decompose = [&](auto &&self, int i) -> void {
    int sz = get_sz(get_sz, i, i);
    int c = get_centroid(get_centroid, i, i, sz);
    process(c);
    removed[c] = true;
    for (int j : adj[c])
      if (not removed[j])
        self(self, j);
  };

  decompose(decompose, 0);
}
