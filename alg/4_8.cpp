#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
class point
{
public:
    float x;
    float y;
    point(){};
    point(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
};
point *X, *Y;
int n;

bool compx(point a, point b)
{
    return a.x < b.x;
}

bool compy(point a, point b)
{
    return a.y < b.y;
}

float distance(point a, point b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

float find_distance_min(int begin, int end)
{
    int length = end - begin + 1;
    if (length == 1)
        return INFINITY;
    else if (length == 2)
        return distance(X[begin], X[end]);
    else
    {
        vector<point> S;
        float min_left = find_distance_min(begin, begin + length / 2 - 1);
        float min_right = find_distance_min(begin + length / 2, end);
        float min_side = min_left < min_right ? min_left : min_right;
        float mid_x = X[length / 2].x;
        float min = min_side;
        for (int i = 0; i < n; i++)
        {
            if (abs(Y[i].x - mid_x) < min_side)
                S.push_back(Y[i]);
        }
        for (int i = 0; i < S.size(); i++)
        {
            for (int j = i + 1; j < S.size() && (S[j].y - S[i].y) < min_side; j++)
            {
                min = min > distance(S[i], S[j]) ? distance(S[i], S[j]) : min;
            }
        }
        return min;
    }
}
int main()
{
    cin >> n;
    X = new point[n];
    Y = new point[n];
    for (int i = 0; i < n; i++)
    {
        float a, b;
        cin >> a >> b;
        point z(a, b);
        X[i] = Y[i] = z;
    }
    sort(X, X + n, compx);
    sort(Y, Y + n, compy);
    float min = find_distance_min(0, n - 1);
    cout << min;
    return 0;
}