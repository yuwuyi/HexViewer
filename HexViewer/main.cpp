#include "viewer_stub.h"
#include <QtGui/QApplication>
#include <QMessageBox>
#include <iostream>
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

	gRenderData.load(argv[1]);

	viewer_stub w;
	w.show();

	return a.exec();
}