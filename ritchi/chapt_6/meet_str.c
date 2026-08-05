#include <stdio.h>
#include <math.h>

struct point {
    int x;
    int y;
};

struct rect {
    struct point pt1;
    struct point pt2;
};

struct point makepoint(int x, int y);
struct point addpoint(struct point p1, struct point p2);
int ptinrect(struct rect r, struct point p);
struct rect canonrect(struct rect r);
#define XMAX 200
#define YMAX 100

int main(int argc, char **argv)
{
    double dist;
    struct point pt;
    struct point maxpt = { 320, 200 };
    struct rect screen; /* screen.pt1.x */
    struct point middle;
    struct point *pp;
    dist = sqrt((double)maxpt.x * maxpt.x +(double) maxpt.y * maxpt.y);
    screen.pt1 = makepoint(0, 0);
    screen.pt2 = makepoint(XMAX, YMAX);
    middle = makepoint((screen.pt1.x + screen.pt2.x) / 2,
                       (screen.pt1.y + screen.pt2.y) / 2);
    /*r.ptl.x
      rp->ptl.х
      (r.ptl).х
      (rp->ptl).x */
    printf("%d, %d\n", maxpt.x, maxpt.y);
    printf("%g\n", dist);

    return 0;
}

struct point makepoint(int x, int y)
{
    struct point temp;

    temp.x = x;
    temp.y = y;
    return temp;
}

struct point addpoint(struct point p1, struct point p2)
{
    p1.x += p2.x;
    p1.y += p2.y;
    return p1;
}

int ptinrect(struct rect r, struct point p)
{
    return p.x >= r.pt1.x && p.x < r.pt2.x
        && p.y >= r.pt1.y && p.y < r.pt2.y;
}

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

struct rect canonrect(struct rect r)
{
    struct rect temp;
    temp.pt1.x = MIN(r.pt1.x, r.pt2.x);
    temp.pt1.y = MIN(r.pt1.y, r.pt2.y);
    temp.pt2.x = MAX(r.pt1.x, r.pt2.x);
    temp.pt2.y = MAX(r.pt1.y, r.pt2.y);
    return temp;
}
