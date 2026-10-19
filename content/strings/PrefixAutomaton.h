/**
 * Author: José Grayson
 * Date: 2026-10-18
 * License: CC0
 * Source: Based on https://cp-algorithms.com/string/prefix-function.html#building-an-automaton-according-to-the-prefix-function
 * Description: Prefix automaton. Useful for speeding up matching (e.g. within DP) and matching
 * on a string computed on-the-fly.
 * Time: O(26n)
 * Status: tested
 */
#pragma once

vector<vi> prefixAutomaton(const string& t, vi& p) {
	vector<vi> next(26, vi(sz(t)+1));
	rep(i, 0, sz(t)+1)
		rep(c, 0, 26)
			if (i == sz(t) || (i && t[i] != 'a'+c))
				next[c][i] = next[c][p[i-1]];
			else
				next[c][i] = i + (t[i] == 'a'+c);
	return next;
}
