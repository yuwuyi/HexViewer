#ifndef RenderData_h__
#define RenderData_h__

#include "Point.h"
#include "RGB.h"
#include <vector>
#include <QObject>
#include <map>

class Hex;
class HexMesh; 
class Quad;
class HalfQuad;
class HexVertex;

class RenderData : public QObject
{
	Q_OBJECT

public:
	RenderData(void);
	~RenderData(void);
	void load(const char *filename);
	void render();
	
public slots:
	void dirChanged(int);
	void offsetChanged(int);
	void jacobianColoring(); 

	void NSJColoring();

private:
	void compute_halfquad_normals();
	void compute_vertex_normals();
	void render_quad();
	void render_egde();
	

	void render_hexes(std::vector<Hex*>& hexes);

	void get_hexes(int type, double level, std::vector<Hex*>& hexes);

	void compute_boundingbox();	

	void prepare_quads();

	void get_quads(int type, double level);

	void compute_jacobian();
	
	void normalize();
private:

	Point minpt, maxpt;
	HexMesh *m_hexmesh;
	std::vector<HalfQuad *> render_quads;
	std::vector<Point> render_edges;
	std::map<HalfQuad*, Point> quad_normals;
	std::map<HexVertex*, Point> vertex_normals;

	std::set<HexVertex*> nsj_vertices;

	std::vector<RGBColor> quadColors;

	std::vector<HalfQuad*> m_boundary_quads;
		
	std::vector<Hex*> m_hexes;

	int m_dir, m_level;

	double m_offset;
	bool isJacobianColoring;
	bool isNSJColoring;

};

#endif // RenderData_h__