#include "Renderer.h"
#include "RenderData.h"

HexMeshRenderer::HexMeshRenderer(HexMeshRenderData *hexdata) 
: m_hexmeshdata(hexdata)
{

}


HexMeshRenderer::~HexMeshRenderer() {

}


void HexMeshRenderer::prepareData() {
	m_hexmeshdata->prepareData();
	m_vertices = m_hexmeshdata->getVertexArray();
	m_normals = m_hexmeshdata->getNormalArray();
	m_colors = m_hexmeshdata->getColorArray();
	m_indices = m_hexmeshdata->getIndexArray();

	m_edge_vertices = m_hexmeshdata->getEdgeVertexArray();
	m_edge_colors = m_hexmeshdata->getEdgeColorArray();
	m_edge_indices = m_hexmeshdata->getEdgeIndexArray();
}

void HexMeshRenderer::render() {

	// enable and specify pointers to vertex arrays
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, &m_vertices[0]);
	glNormalPointer(GL_FLOAT, 0, &m_normals[0]);
	glColorPointer(3, GL_FLOAT, 0, &m_colors[0]);

	glDrawElements(GL_QUADS, m_indices.size(), GL_UNSIGNED_INT, &m_indices[0]);

	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	//edge
/*
	glPolygonMode(GL_FRONT, GL_FILL);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0, 1.0);
	glDisable(GL_LIGHTING);
	glEnable (GL_LINE_SMOOTH);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glColorPointer(3, GL_FLOAT, 0, &m_edge_colors[0]);
	glVertexPointer(3, GL_FLOAT, 0, &m_edge_vertices[0]);

	glDrawElements(GL_LINES, m_edge_indices.size(), GL_UNSIGNED_INT, &m_edge_indices[0]);
	//glDrawElements(GL_POINTS, m_edge_indices.size(), GL_UNSIGNED_INT, &m_edge_indices[0]);
	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);

	glEnable(GL_LIGHTING);
	glDisable (GL_LINE_SMOOTH);
	glDisable (GL_BLEND);
	*/

	render_edges();
}

void HexMeshRenderer::render_edges() {
	glPolygonMode(GL_FRONT, GL_FILL);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0, 1.0);
	glDisable(GL_LIGHTING);
	glEnable (GL_LINE_SMOOTH);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
	glColor3f(0.1, 0.1, 0.1);

	//for (size_t i = 0; i < render_edges.size(); i += 2) {
	for (size_t i = 0; i < m_edge_vertices.size(); i+=6) {
		glBegin(GL_LINES);
		glVertex3f(m_edge_vertices[i], m_edge_vertices[i + 1], m_edge_vertices[i + 2]);
		glVertex3f(m_edge_vertices[i + 3], m_edge_vertices[i + 4], m_edge_vertices[i + 5]);
		glEnd();
	}

	glEnable(GL_LIGHTING);
	glDisable (GL_LINE_SMOOTH);
	glDisable (GL_BLEND);
}

void HexMeshRenderer::render4picking() {

}

bool HexMeshRenderer::processHits(int id) {

	return true;
}


