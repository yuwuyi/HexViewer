#ifndef Renderer_h__
#define Renderer_h__

#include <QtOpenGL>
#include <vector>

class HexMesh;
class HexMeshRenderData;

class Renderer {
public:
	virtual ~Renderer() {}
	virtual void render() = 0;
};

class PickingRenderer : public Renderer {
public:
	virtual ~PickingRenderer() {}
	virtual void render4picking() = 0;
	virtual bool processHits(int id) = 0;
	virtual void unpick() { m_pickid = -1; }
protected:
	int m_pickid;
};

class HexMeshRenderer : public PickingRenderer {
public:
	HexMeshRenderer(HexMeshRenderData *hexmeshdata);
	~HexMeshRenderer();

	virtual void render();
	virtual void render4picking();
	virtual bool processHits(int id);

	void prepareData();
protected:
	void render_edges();

private:
	HexMeshRenderData *m_hexmeshdata;
	std::vector<GLfloat> m_vertices, m_normals, m_colors; 
	std::vector<GLuint> m_indices;

	std::vector<GLfloat> m_edge_vertices, m_edge_colors; 
	std::vector<GLuint> m_edge_indices;

};
#endif // Renderer_h__