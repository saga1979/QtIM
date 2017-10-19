#pragma once

#include <QLabel>

class ImageLabel : public QLabel
{
	Q_OBJECT

public:
	ImageLabel(QWidget *parent);
	~ImageLabel();
	void setImage(const QString& file);
protected:
	void mousePressEvent(QMouseEvent *event);

};
