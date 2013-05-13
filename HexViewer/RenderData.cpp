#include <QtOpenGL>
#include "RenderData.h"
#include "HexEdge.h"
#include "HexVertex.h"
#include "HalfQuad.h"
#include "Hex.h"
#include "Quad.h"
#include "HexMesh.h"
#include "HexIterators.h"
#include "HexMeshUtils.h"
#include "PotentialRGB.h"
#include "JacobianEva.h"
#include <set>
#include <algorithm>
#include <iostream>


HexMeshRenderData::HexMeshRenderData(HexMesh *hexmesh)
: m_hexmesh(hexmesh)
{

}

HexMeshRenderData::~HexMeshRenderData() {

}


void HexMeshRenderData::prepareData() {
	m_render_quads = m_hexmesh->getBoudnary();
	compute_halfquad_normals();
	compute_vertex_normals();
}


void HexMeshRenderData::compute_halfquad_normals() {
	for (size_t i = 0 ; i < m_render_quads.size(); ++i) {
		HalfQuad *halfquad = m_render_quads[i];
		Point pts[3] = {halfquad->vertex(0)->point(), halfquad->vertex(1)->point(), halfquad->vertex(3)->point()};
		Point norm = (pts[1] - pts[0]) ^ (pts[2] - pts[0]);
		norm /= norm.norm();
		quad_normals[halfquad] = norm;
	}
}

void HexMeshRenderData::compute_vertex_normals() {
	std::map<HexVertex*, std::vector<HalfQuad*> > vquadmap;
	for (size_t i = 0; i < m_render_quads.size(); ++i) {
		HalfQuad *halfquad = m_render_quads[i];
		for (int j = 0; j < 4; ++j) {
			HexVertex *v = halfquad->vertex(j);
			vquadmap[v].push_back(halfquad);
		}
	}

	for (std::map<HexVertex*, std::vector<HalfQuad*> >::iterator b = vquadmap.begin(),
		e = vquadmap.end(); b != e; ++b) {
		HexVertex *v = (*b).first;
		std::vector<HalfQuad*>& halfquads = (*b).second;
		
		Point vnorm;
		for (size_t i = 0; i < halfquads.size(); ++i) {
			HalfQuad *halfquad = halfquads[i];
			vnorm += quad_normals[halfquad];
		}
		vnorm /= halfquads.size(); 

		vertex_normals[v] = vnorm;
	}
}

std::vector<GLfloat> HexMeshRenderData::getVertexArray() {
	std::vector<GLfloat> ver_array;

	for (size_t i = 0; i < m_render_quads.size(); ++i) {
		HalfQuad *halfquad = m_render_quads[i];
		for (int j = 0; j < 4; ++j) {
			ver_array.push_back(halfquad->vertex(j)->point()[0]);	
			ver_array.push_back(halfquad->vertex(j)->point()[1]);	
			ver_array.push_back(halfquad->vertex(j)->point()[2]);	
		}
	}
	return ver_array;
}

std::vector<GLfloat> HexMeshRenderData::getNormalArray() {
	std::vector<GLfloat> norm_array;
	for (size_t i = 0; i < m_render_quads.size(); ++i) {
		HalfQuad *halfquad = m_render_quads[i];
		for (int j = 0; j < 4; ++j) {
			norm_array.push_back(vertex_normals[halfquad->vertex(j)][0]);	
			norm_array.push_back(vertex_normals[halfquad->vertex(j)][0]);	
			norm_array.push_back(vertex_normals[halfquad->vertex(j)][0]);	
		}
	}
	return norm_array;
}

std::vector<GLfloat> HexMeshRenderData::getColorArray() {
	std::vector<GLfloat> color_array;
		//Point BlueColor(63/255.0, 161/255.0, 253/255.0);	
Point BlueColor(63/255.0, 161/255.0, 253/255.0);	
	for (size_t i = 0; i < m_render_quads.size(); ++i) {
		HalfQuad *halfquad = m_render_quads[i];
		for (int j = 0; j < 4; ++j) {
			color_array.push_back(BlueColor[0]);	
			color_array.push_back(BlueColor[1]);	
			color_array.push_back(BlueColor[2]);	
		}
	}
	return color_array;
}


std::vector<GLuint> HexMeshRenderData::getIndexArray() {
	std::vector<GLuint> index_array;
	int count = 0;
	for (size_t i = 0; i < m_render_quads.size(); ++i) {
		HalfQuad *halfquad = m_render_quads[i];
		for (int j = 0; j < 4; ++j, ++count) {
			index_array.push_back(count);	
		}
	}

	return index_array;
}


std::vector<GLfloat> HexMeshRenderData::getEdgeVertexArray() {
	std::vector<GLfloat> ver_array;

	for (size_t i = 0; i < m_render_quads.size(); ++i) {
		HalfQuad *halfquad = m_render_quads[i];
		for (int j = 0; j < 4; ++j) {
			HexEdge *hedge = halfquad->quad()->hexedge(j);
			Point pt0 = hedge->vertex(0)->point();
			Point pt1 = hedge->vertex(1)->point();

			ver_array.push_back(pt0[0]);	
			ver_array.push_back(pt0[1]);	
			ver_array.push_back(pt0[2]);	

			ver_array.push_back(pt1[0]);	
			ver_array.push_back(pt1[1]);	
			ver_array.push_back(pt1[2]);	
		}
	}
	return ver_array;

}

std::vector<GLfloat> HexMeshRenderData::getEdgeColorArray() {
	std::vector<GLfloat> color_array;
		//Point BlueColor(63/255.0, 161/255.0, 253/255.0);	
Point BlackColor(0, 0, 0);
	for (size_t i = 0; i < m_render_quads.size(); ++i) {
		HalfQuad *halfquad = m_render_quads[i];
		for (int j = 0; j < 4; ++j) {
			color_array.push_back(BlackColor[0]);	
			color_array.push_back(BlackColor[1]);	
			color_array.push_back(BlackColor[2]);	

			color_array.push_back(BlackColor[0]);	
			color_array.push_back(BlackColor[1]);	
			color_array.push_back(BlackColor[2]);	
		}
	}
	return color_array;
}

std::vector<GLuint> HexMeshRenderData::getEdgeIndexArray() {
	std::vector<GLuint> index_array;
	int count = 0;
	for (size_t i = 0; i < m_render_quads.size(); ++i) {
		HalfQuad *halfquad = m_render_quads[i];
		for (int j = 0; j < 4; ++j, ++count) {
			/*index_array.push_back(4 * i + j);	
			index_array.push_back(4 * i + (j + 1) % 4);	*/
			index_array.push_back(count);
		}
	}

	return index_array;
}

/*
RenderData::RenderData(void) : m_hexmesh(0),  m_offset(0), m_dir(0), isJacobianColoring(false), isNSJColoring(false), m_level(0)
{
}

RenderData::~RenderData(void)
{
	delete m_hexmesh;
}


/
void RenderData::compute_halfquad_normals() {
	for (size_t i = 0 ; i < render_quads.size(); ++i) {
		HalfQuad *halfquad = render_quads[i];
		Point pts[3] = {halfquad->vertex(0)->point(), halfquad->vertex(1)->point(), halfquad->vertex(3)->point()};
		Point norm = (pts[1] - pts[0]) ^ (pts[2] - pts[0]);
		norm /= norm.norm();
		quad_normals[halfquad] = norm;
	}
}


void RenderData::compute_vertex_normals() {
	std::map<HexVertex*, std::vector<HalfQuad*> > vquadmap;
	for (size_t i = 0; i < render_quads.size(); ++i) {
		HalfQuad *halfquad = render_quads[i];
		for (int j = 0; j < 4; ++j) {
			HexVertex *v = halfquad->vertex(j);
			vquadmap[v].push_back(halfquad);
		}
	}

	for (std::map<HexVertex*, std::vector<HalfQuad*> >::iterator b = vquadmap.begin(),
		e = vquadmap.end(); b != e; ++b) {
		HexVertex *v = (*b).first;
		std::vector<HalfQuad*>& halfquads = (*b).second;
		
		Point vnorm;
		for (size_t i = 0; i < halfquads.size(); ++i) {
			HalfQuad *halfquad = halfquads[i];
			vnorm += quad_normals[halfquad];
		}
		vnorm /= halfquads.size(); 

		vertex_normals[v] = vnorm;
	}
}

struct sort_func{
	sort_func(int d) : dir(d) {}
	bool operator()(Hex* h1, Hex* h2) {
		return h1->center()[dir] < h2->center()[dir];
	}
	int dir;
};

void RenderData::load(const char *filename) {
	m_hexmesh = new HexMesh;
	//m_hexmesh->read_vtk(filename);
	m_hexmesh->read(filename);
	
	compute_boundingbox();
	m_offset = minpt[0];
	render_quads = m_hexmesh->getBoudnary(); 
	std::set<HexEdge*> hedges;
	for (size_t i = 0; i < render_quads.size(); ++i) {
		HalfQuad *halfquad = render_quads[i];
		Quad *quad = halfquad->quad();
		for (int j = 0; j < 4; ++j) {
			HexEdge *hedge = quad->hexedge(j);
			hedges.insert(hedge);
		}
	}

	for (std::set<HexEdge*>::iterator b = hedges.begin(), e = hedges.end(); b != e; ++b) {
		HexEdge *hedge = *b;
		render_edges.push_back(hedge->vertex(0)->point());
		render_edges.push_back(hedge->vertex(1)->point());
	}

		
	compute_halfquad_normals();
	compute_vertex_normals();
		
	prepare_quads();
	compute_jacobian();
	m_level = maxpt[m_dir];
}

void RenderData::render_quad() {
	glEnable(GL_COLOR_MATERIAL);
	
	if (isJacobianColoring) {
		for (size_t i = 0; i < render_quads.size(); ++i) {
			HalfQuad *halfquad = render_quads[i];
			if (isJacobianColoring) {
				RGBColor rgb = quadColors[halfquad->quad()->index()];
				glColor3f(rgb[R], rgb[G], rgb[B]);
			}

			Point norm = quad_normals[halfquad];

			glBegin(GL_QUADS);
			glNormal3f(norm[0], norm[1], norm[2]);
			for (int j = 0; j < 4; ++j) {
				HexVertex *v = halfquad->vertex(j);
				glVertex3f(v->point()[0], v->point()[1], v->point()[2]);
			}
			glEnd();	
		}
	} else if (isNSJColoring) {
		for (size_t i = 0; i < render_quads.size(); ++i) {
			HalfQuad *halfquad = render_quads[i];
			Point norm = quad_normals[halfquad];

			glBegin(GL_QUADS);
			glNormal3f(norm[0], norm[1], norm[2]);
			for (int j = 0; j < 4; ++j) {
				HexVertex *v = halfquad->vertex(j);
				if (nsj_vertices.find(v) == nsj_vertices.end()) {
					glColor3f(63/255.0, 161/255.0, 253/255.0);	
				} else {
					glColor3f(1.0, 0.1, 0.1);	
				}

				glVertex3f(v->point()[0], v->point()[1], v->point()[2]);
			}
			glEnd();	
		}
	} else {
		glColor3f(63/255.0, 161/255.0, 253/255.0);	
		for (size_t i = 0; i < render_quads.size(); ++i) {
			HalfQuad *halfquad = render_quads[i];
			Point norm = quad_normals[halfquad];

			glBegin(GL_QUADS);
			glNormal3f(norm[0], norm[1], norm[2]);
			for (int j = 0; j < 4; ++j) {
				HexVertex *v = halfquad->vertex(j);
				glVertex3f(v->point()[0], v->point()[1], v->point()[2]);
			}
			glEnd();	
		}
	}

}



void RenderData::render_hexes(std::vector<Hex*>& hexes) {

	std::map<Quad*, HalfQuad*> quadmap;
//	for (stdext::hash_map<int, Hex*>::iterator b = id2Hex.begin(), e = id2Hex.end(); b != e; ++b) {
	for (size_t i = 0; i < hexes.size(); ++i) {
		Hex *hex = hexes[i];
		for (int i = 0; i < 6; ++i) {
			HalfQuad *halfquad = hex->halfquad(i);	
			std::map<Quad*, HalfQuad*>::iterator iter = quadmap.find(halfquad->quad());

			if (iter != quadmap.end()) {
				quadmap.erase(iter);
			} else {
				quadmap[halfquad->quad()] = halfquad;
			}
		}
			
	}


	render_quads.clear();
	for (std::map<Quad*, HalfQuad*>::iterator b = quadmap.begin(), e = quadmap.end(); b != e; ++b) {
		HalfQuad *halfquad = (*b).second;
		render_quads.push_back(halfquad);
	}

	
	std::set<HexEdge*> hedges;
	for (size_t i = 0; i < render_quads.size(); ++i) {
		HalfQuad *halfquad = render_quads[i];
		Quad *quad = halfquad->quad();
		for (int j = 0; j < 4; ++j) {
			HexEdge *hedge = quad->hexedge(j);
			hedges.insert(hedge);
		}
	}

	render_edges.clear();
	for (std::set<HexEdge*>::iterator b = hedges.begin(), e = hedges.end(); b != e; ++b) {
		HexEdge *hedge = *b;
		render_edges.push_back(hedge->vertex(0)->point());
		render_edges.push_back(hedge->vertex(1)->point());
	}

	compute_halfquad_normals();
	compute_vertex_normals();


}

void RenderData::render_egde() {
	glPolygonMode(GL_FRONT, GL_FILL);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0, 1.0);
	glDisable(GL_LIGHTING);
	glEnable (GL_LINE_SMOOTH);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
	glColor3f(0.1, 0.1, 0.1);

	for (size_t i = 0; i < render_edges.size(); i += 2) {
		Point& p0 = render_edges[i];
		Point& p1 = render_edges[i + 1];
		glBegin(GL_LINES);
		glVertex3d(p0[0], p0[1], p0[2]);
		glVertex3d(p1[0], p1[1], p1[2]);
		glEnd();
	}	

	glEnable(GL_LIGHTING);
	glDisable (GL_LINE_SMOOTH);
	glDisable (GL_BLEND);
}

void RenderData::render() {
	render_quad();
	render_egde();
}

void RenderData::get_hexes(int type, double level, std::vector<Hex*>& hexes) {
	hexes.clear();
	for(HexMeshHexIterator hmhit(m_hexmesh); !hmhit.end(); ++hmhit) {
		Hex *hex = *hmhit;
		Point center = hex->center();
		if (center[type] < level) {
			hexes.push_back(hex);
		}
	}
}

void RenderData::compute_boundingbox() {
	minpt = Point(1e4, 1e4, 1e4);
	maxpt = Point(-1e4, -1e4, -1e4);

	for (HexMeshVertexIterator hmvit(m_hexmesh); !hmvit.end(); ++hmvit) {
		HexVertex *vertex = *hmvit;
		Point pt = vertex->point();
		for (int i = 0; i < 3; ++i) {
			if (pt[i] < minpt[i]) {
				minpt[i] = pt[i];
			}
			if (pt[i] > maxpt[i]) {
				maxpt[i] = pt[i];
			}
		}

	}
}



static int binarySearch(std::vector<Hex*> quads, int first, int last, int type, double lvl) {
   
   while (first <= last) {
       int mid = (first + last) / 2;  // compute mid point.
       if (lvl > quads[mid]->center()[type] + 0.1 ) 
           first = mid + 1;  // repeat search in top half.
       else if (lvl < quads[mid]->center()[type] - 0.1) 
           last = mid - 1; // repeat search in bottom half.
	   else {
		   for (; mid < last ; ++mid) {
			   if (quads[mid]->center()[type] > lvl + 0.1 ) {
					return mid - 1;
			   }
		   }
		   return last;
	   }
   }
   return -(first + 1);    // failed to find key
}

void RenderData::prepare_quads() {
	for (HexMeshHexIterator hmhit(m_hexmesh); !hmhit.end(); ++hmhit) {
		Hex *hex = *hmhit;
		m_hexes.push_back(hex);
	}
	std::sort(m_hexes.begin(), m_hexes.end(), sort_func(m_dir));
}


void RenderData::get_quads(int type, double level) {
	static ORIENTATION QUAD_DIR[3] = {RIGHT, BACK, UP};
	render_quads.clear();
	render_edges.clear();

	double delta = (maxpt[type] - minpt[type]) / 10.0;
	delta = 0.1;
	int index1 = binarySearch(m_hexes, 0, m_hexes.size() - 1, type, level);
	if (index1 < 0) {
		index1 = 0;
	}
	int index2 = binarySearch(m_hexes, index1, m_hexes.size() - 1, type, level + 0.5);
	if (index2 < 0) {
		index2 = m_hexes.size();
	}
	
	for (int i = index1; i < index2; ++i) {
		Hex *hex = m_hexes[i];
		render_quads.push_back(hex->halfquad(QUAD_DIR[type]));
	}
	
	growing(render_quads, QUAD_DIR[type]);
	std::vector<HalfQuad*> qquads = render_quads;
	render_quads.clear();
	std::set<Hex*> hexes;

	for (int i = 0; i < qquads.size(); ++i) {
		hexes.insert(qquads[i]->hex());
	}
	
	std::map<Quad*, HalfQuad*> quadmap;
	for (std::set<Hex*>::iterator b = hexes.begin(), e = hexes.end(); b != e; ++b) {
		Hex *hex = *b;
		for (int i = 0; i < 6; ++i) {
			HalfQuad *halfquad = hex->halfquad(i);	
			std::map<Quad*, HalfQuad*>::iterator iter = quadmap.find(halfquad->quad());

			if (iter != quadmap.end()) {
				quadmap.erase(iter);
			} else {
				quadmap[halfquad->quad()] = halfquad;
			}
		}
	} 

	for (std::map<Quad*, HalfQuad*>::iterator b = quadmap.begin(), e = quadmap.end(); b != e; ++b) {
		HalfQuad *halfquad = (*b).second;
		render_quads.push_back(halfquad);
	}
	
	for (int i = 0; i < index2; ++i) {
		Hex *hex = m_hexes[i];
		if (!hex->isBoundary()) {
			continue;
		}
		for (int j = 0; j < hex->boundaryHalfQuads.size(); ++j) {
			render_quads.push_back(hex->boundaryHalfQuads[j]);
		}
	}

	std::set<HexEdge*> hedges;
	for (size_t i = 0; i < render_quads.size(); ++i) {
		HalfQuad *halfquad = render_quads[i];
		Quad *quad = halfquad->quad();
		for (int j = 0; j < 4; ++j) {
			HexEdge *hedge = quad->hexedge(j);
			hedges.insert(hedge);
		}
	}

	for (std::set<HexEdge*>::iterator b = hedges.begin(), e = hedges.end(); b != e; ++b) {
		HexEdge *hedge = *b;
		render_edges.push_back(hedge->vertex(0)->point());
		render_edges.push_back(hedge->vertex(1)->point());
	}

	compute_halfquad_normals();
	compute_vertex_normals();
}



void RenderData::dirChanged(int dir) {
	m_dir = dir;
	std::sort(m_hexes.begin(), m_hexes.end(), sort_func(m_dir));
	offsetChanged(m_level);
	get_quads(m_dir, m_offset);	
	
}

void RenderData::offsetChanged(int level) {
	m_level = level;
	m_offset = (maxpt[m_dir] - minpt[m_dir])  * level / 100.0 + minpt[m_dir];		
	
	if (m_offset > maxpt[m_dir]) {
		m_offset = maxpt[m_dir];
	}
	if (m_offset < minpt[m_dir]) {
		m_offset = minpt[m_dir];
	}
		
	get_quads(m_dir, m_offset);
}





void RenderData::compute_jacobian() {

	JacobianEva je(m_hexmesh);
	je.evaluate();
	
	for (HexMeshVertexIterator hvit(m_hexmesh); !hvit.end(); ++hvit) {
		HexVertex *hv = *hvit;
		if (je.get(hv) < 0) {
			nsj_vertices.insert(hv);
		}
	}

	std::vector<Quad*> quads = m_hexmesh->getQuads();
	quadColors.resize(quads.size());

	PotentialRGB pRgb;
	pRgb.minvalue = 0;
	pRgb.maxvalue = 1;
	pRgb.init();

	for (size_t i = 0; i < quads.size(); ++i) {
		Quad *quad = quads[i];
		double q = 0;
		for (int j = 0; j < 4; ++j) {
			double value = je.get(quad->halfquad(0)->vertex(j));
			q += value;
		}
		
		RGBColor rgb = pRgb.getRGB( 1.0 - q / 4.0);
		quadColors[quad->index()] = rgb;
	}

}


void RenderData::jacobianColoring() {
	isJacobianColoring = !isJacobianColoring;			
}

void RenderData::NSJColoring() {
	isNSJColoring = !isNSJColoring;
}
*/

