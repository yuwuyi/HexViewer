#ifndef VIEWER_STUB_H
#define VIEWER_STUB_H

#include <QtGui/QMainWindow>
#include "ui_viewer_stub.h"

class Renderer;
class SliceDlg;
class viewer_stub : public QMainWindow
{
	Q_OBJECT

public:
	viewer_stub(QWidget *parent = 0, Qt::WFlags flags = 0);
	~viewer_stub();
	void addRenderer(Renderer *r);

public slots:
	void showSliceDlg();		
	void dirChanged(int dir);	
	void offsetChanged(int offset);	
	void jacobianColoring();
	void NSJColoring();

protected:
	virtual void closeEvent(QCloseEvent *event);

private:
	Ui::viewer_stubClass ui;
	SliceDlg *m_slicedlg;
};

#endif // VIEWER_STUB_H
