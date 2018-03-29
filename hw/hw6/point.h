#ifndef __POINT_H__
#define __POINT_H__

// =============================================================
// | This class stores the grid representation of point.       |
// =============================================================

class Point{
public:
	Point() : row(0), col(0) {}
	Point(int y, int x) : row(y), col(x) {}
	int y() const { return row; }
	int x() const { return col; }
	
private:
	int row;
	int col;	
};

#endif