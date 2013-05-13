#include "viewer_stub.h"
#include "RenderData.h"
#include "slicedlg.h"

extern RenderData gRenderData;

viewer_stub::viewer_stub(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags), m_slicedlg(NULL)
{
	ui.setupUi(this);
}

viewer_stub::~viewer_stub()
{
}


void viewer_stub::dirChanged(int dir) {
	/*gRenderData.dirChanged(dir);*/
	ui.widget->update();
}

void viewer_stub::offsetChanged(int offset) {
	/*gRenderData.offsetChanged(offset);*/
	ui.widget->update();
}


void viewer_stub::closeEvent(QCloseEvent *event) {
	if (m_slicedlg) {
		m_slicedlg->hide();	
		delete m_slicedlg;
		m_slicedlg = NULL;
	}
	
}
void viewer_stub::showSliceDlg() {
	if (!m_slicedlg) {
		m_slicedlg = new SliceDlg(0);
		QObject::connect(m_slicedlg, SIGNAL(dirChanged(int)), this, SLOT(dirChanged(int)));
		QObject::connect(m_slicedlg, SIGNAL(offsetChanged(int)), this, SLOT(offsetChanged(int)));
	}

	m_slicedlg->show();
}


void viewer_stub::jacobianColoring() {
	//gRenderData.jacobianColoring();
	ui.widget->update();
}

void viewer_stub::NSJColoring() {
	//gRenderData.NSJColoring();
	ui.widget->update();
}


void viewer_stub::addRenderer(Renderer *r) {
	ui.widget->addRenderer(r);
}