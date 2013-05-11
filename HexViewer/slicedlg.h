#ifndef SLICEDLG_H
#define SLICEDLG_H

#include <QWidget>
#include "ui_slicedlg.h"

class SliceDlg : public QWidget
{
	Q_OBJECT

public:
	SliceDlg(QWidget *parent = 0);
	~SliceDlg();

signals:
	void dirChanged(int dir);
	void offsetChanged(int offset);	

public slots:
	void changeDirection(int dir);
	void changeOffset(int offset);
private:
	Ui::SliceDlg ui;
};

#endif // SLICEDLG_H
