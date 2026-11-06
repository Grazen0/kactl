/**
 * Author: Joaquin Lopez, based on cp-algorithms
 * Date: 2026-11-05
 * Source: https://cp-algorithms.com/geometry/minkowski.html
 * Description: Minkowski sum of two convex polygons, i.e. $\{p+q\}$.
 *  Both polygons must be given in ccw order, without repeated points.
 *  Parallel edges are merged, so if the inputs have no collinear
 *  points neither does the result.
 * Time: O(n + m)
 */
#pragma once

#include "Point.h"

template<class P>
vector<P> minkowski(vector<P> p, vector<P> q) {
	auto low = [](P a, P b) { return tie(a.y,a.x) < tie(b.y,b.x); };
	rotate(p.begin(), min_element(all(p), low), p.end());
	rotate(q.begin(), min_element(all(q), low), q.end());

	int n = sz(p), m = sz(q);
	p.push_back(p[0]), p.push_back(p[1]);
	q.push_back(q[0]), q.push_back(q[1]);

	vector<P> r;
	for (int i = 0, j = 0; i < n || j < m;) {
		r.push_back(p[i] + q[j]);
		auto c = (p[i+1] - p[i]).cross(q[j+1] - q[j]);
		if (c >= 0 && i < n) i++;
		if (c <= 0 && j < m) j++;
	}

	return r;
}
