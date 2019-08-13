#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {
    /** @todo [Part 1] */
    source = png;
    t = tolerance;
    startPoint.x = start.x;
    startPoint.y = start.y;
    current = startPoint;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
    /** @todo [Part 1] */
    Iterator* it = new Iterator(startPoint, source, t, this);

    return *it;

}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
    /** @todo [Part 1] */
    Iterator* it = new Iterator(this);
    return *it;
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
    /** @todo [Part 1] */
    q.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
    /** @todo [Part 1] */
    unsigned x = q.front().x;
    unsigned y = q.front().y;

    //isVisited[y][x] = true;

    //cout<<x<<y<<endl;
    current.x = x;
    current.y = y;
    //cout<<current.x<<current.y<<endl;

    q.pop();
    //return Point(x, y);
    return current;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
    /** @todo [Part 1] */
    return current;
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
    /** @todo [Part 1] */
    if(q.empty())
        return true;
    return false;
}