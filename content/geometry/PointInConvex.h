/**
 * Author: Joaquin Lopez, based on cp-algorithms
 * Date: 2026-11-05
 * Source: https://cp-algorithms.com/geometry/point-in-convex-polygon.html
 * Description: Returns true if p is inside or on the boundary of a
 *  convex polygon h (ccw, no collinear points, at least 3 vertices).
 *  Binary searches the fan of triangles rooted at h[0].
 *  Works with integer coordinates (no division, no abs-area sums).
 * Time: O(\log n) per query
 */
#pragma once

#include "Point.h"

template<class P>
bool inConvex(const vector<P>& h, P p) {
	int n = sz(h) - 1;
	auto v = [&](int i) { return h[i+1] - h[0]; };
	p = p - h[0];

	if (v(0).cross(p) != 0 && sgn(v(0).cross(p)) != sgn(v(0).cross(v(n-1))))
		return false;
	if (v(n-1).cross(p) != 0 && sgn(v(n-1).cross(p)) != sgn(v(n-1).cross(v(0))))
		return false;
	if (v(0).cross(p) == 0) return v(0).dist2() >= p.dist2();

	int l = 0, r = n - 1;
	while (r - l > 1) {
		int m = (l + r) / 2;
		(v(m).cross(p) >= 0 ? l : r) = m;
	}

	return (v(l+1) - v(l)).cross(p - v(l)) >= 0;
}
