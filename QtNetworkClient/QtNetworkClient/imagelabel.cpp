#include "imagelabel.h"

#include <QFileDialog>
#include <QImageReader>

ImageLabel::ImageLabel(QWidget *parent)
	: QLabel(parent)
{
}

ImageLabel::~ImageLabel()
{
}

void ImageLabel::setImage(const QString & file)
{
	QImageReader ir(file);
	QPixmap image = QPixmap::fromImageReader(&ir);

	this->setPixmap(image.scaled(this->size()));
}

void ImageLabel::mousePressEvent(QMouseEvent * event)
{
	QLabel::mousePressEvent(event);
	QFileDialog dialog(this);
	dialog.setNameFilter("Images (*.png *.xpm *.jpg)");
	dialog.setViewMode(QFileDialog::Detail);

	if (dialog.exec() == QDialog::Rejected)
	{
		return;
	}

	QStringList files = dialog.selectedFiles();

	setImage(*files.begin());


}
