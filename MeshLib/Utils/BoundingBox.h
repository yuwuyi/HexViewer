#ifndef BoundingBox_h__
#define BoundingBox_h__

#include <vector>
#include "../Point.h"

class HexMesh;
class BoundingBox {
public:
	BoundingBox(HexMesh *hexmesh);
	BoundingBox(std::vector<Point>& points);
	~BoundingBox();
	void compute();	
	double diag();

	Point min() const { return m_minpt; }
	Point max() const { return m_maxpt; }
private:
	std::vector<Point> m_points;
	Point m_minpt;
	Point m_maxpt;
};
#endif // BoundingBox_h__