#include "slicedlg.h"

SliceDlg::SliceDlg(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	 Qt::WindowFlags flags = windowFlags();
	flags |= Qt::WindowStaysOnTopHint;
	setWindowFlags(flags);
}

SliceDlg::~SliceDlg()
{

}

void SliceDlg::changeDirection(int dir) {
	emit dirChanged(dir);
}

void SliceDlg::changeOffset(int offset) {
	emit offsetChanged(offset);
}