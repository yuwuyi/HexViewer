#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QGLWidget>
#include "Camera.h"

class ViewPort : public QGLWidget
{
	Q_OBJECT

public:
	ViewPort(QWidget *parent);
	~ViewPort();

protected :
	void initialMaterial ();
	void initializeGL ();
	void resizeGL ( int width , int height );
	void paintGL ();

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

	void wheelEvent( QWheelEvent * event );

private:

	void Rotate(float ox, float oy, float nx, float ny);
	void Translate(float dx, float dy, float dz);
	void UpdateDist(float dx, float dy, float dz);
	void Mousei2f(int x, int y, float *xf, float *yf);

private:
	void InitCamera();
	GLfloat rotation[3];
	GLfloat translation[3];
	GLfloat light0Pos[3];

	QPointF lastPos;
	QPointF pressPos;

	//These code from Mesh3D.
	Camera theCamera;
	float rotate_dist;							// How far the center of the trackball is from the camera
	float view_dist;							// How far the center of the world is from the camera
	
	
};

#endif // VIEWPORT_H
