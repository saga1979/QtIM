#pragma once

#include <QLabel>

class ImageLabel : public QLabel
{
	Q_OBJECT

public:
	ImageLabel(QWidget *parent);
	~ImageLabel();
	void setImage(const QString& file);
	const QString& getImage() const;
protected:
	void mousePressEvent(QMouseEvent *event);
private:
	QString m_file;

};
