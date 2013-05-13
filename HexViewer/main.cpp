#include "viewer_stub.h"
#include <QtGui/QApplication>
#include <QMessageBox>
#include <iostream>
#include "Renderer.h"
#include "RenderData.h"
#include "HexVertex.h"
#include "HexMesh.h"
#include "HexIterators.h"

RenderData gRenderData;


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	if(argc != 2) {
		QMessageBox::information(0, "Usage", "Usage: hexviewer.exe input.grid" );	
		exit(-1);
	}

	HexMesh *hexmesh = new HexMesh;
	hexmesh->read(argv[1]);
	//gRenderData.load(argv[1]);
	HexMeshRenderData *hexdata = new HexMeshRenderData(hexmesh);
	HexMeshRenderer *hexrenderer = new HexMeshRenderer(hexdata);
	hexrenderer->prepareData();

	viewer_stub w;
	//w.ui.widget->addRenderer(hexrenderer);
	w.addRenderer(hexrenderer);
	w.show();

	return a.exec();
}