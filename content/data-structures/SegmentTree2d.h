/**
 * Author: CP algorithms
 * License: CC0
 * Source:
 * https://cp-algorithms.com/data_structures/segment_tree.html#generalization-to-higher-dimensions
 * Description: 2D Segment Tree.
 * Time: Construction takes O(16nm), Updates and queries take O(log(n)log(m)).
 * Memory: O(16nm)
 */
#pragma once

int t[4*MAXX][4*MAXY];

void build_y(int vx, int lx, int rx, int vy, int ly, int ry) {
    if (ry - ly == 1) {
        if (rx - lx == 1)
            t[vx][vy] = a[lx][ly];
        else
            t[vx][vy] = t[vx*2][vy] + t[vx*2+1][vy];
    } else {
        int my = (ly + ry) / 2;
        build_y(vx, lx, rx, vy*2, ly, my);
        build_y(vx, lx, rx, vy*2+1, my, ry);
        t[vx][vy] = t[vx][vy*2] + t[vx][vy*2+1];
    }
}

void build_x(int vx, int lx, int rx) {
    if (rx - lx > 1) {
        int mx = (lx + rx) / 2;
        build_x(vx*2, lx, mx);
        build_x(vx*2+1, mx, rx);
    }
    build_y(vx, lx, rx, 1, 0, m);
}

int sum_y(int vx, int vy, int tly, int try_, int ly, int ry) {
    if (ry <= tly || try_ <= ly) 
        return 0;
    if (ly <= tly && try_ <= ry)
        return t[vx][vy];
    int tmy = (tly + try_) / 2;
    return sum_y(vx, vy*2, tly, tmy, ly, ry)
         + sum_y(vx, vy*2+1, tmy, try_, ly, ry);
}

int sum_x(int vx, int tlx, int trx, int lx, int rx, int ly, int ry) {
    if (rx <= tlx || trx <= lx)
        return 0;
    if (lx <= tlx && trx <= rx)
        return sum_y(vx, 1, 0, m, ly, ry);
    int tmx = (tlx + trx) / 2;
    return sum_x(vx*2, tlx, tmx, lx, rx, ly, ry)
         + sum_x(vx*2+1, tmx, trx, lx, rx, ly, ry);
}

void update_y(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, int new_val) {
    if (ry - ly == 1) {
        if (rx - lx == 1)
            t[vx][vy] = new_val;
        else
            t[vx][vy] = t[vx*2][vy] + t[vx*2+1][vy];
    } else {
        int my = (ly + ry) / 2;
        if (y <= my)
            update_y(vx, lx, rx, vy*2, ly, my, x, y, new_val);
        else
            update_y(vx, lx, rx, vy*2+1, my, ry, x, y, new_val);
        t[vx][vy] = t[vx][vy*2] + t[vx][vy*2+1];
    }
}

void update_x(int vx, int lx, int rx, int x, int y, int new_val) {
    if (rx - lx > 1) {
        int mx = (lx + rx) / 2;
        if (x <= mx)
            update_x(vx*2, lx, mx, x, y, new_val);
        else
            update_x(vx*2+1, mx, rx, x, y, new_val);
    }
    update_y(vx, lx, rx, 1, 0, m, x, y, new_val);
}

