#include "textBox.h"

#include <QtCore/QDebug>

//This is a Qt class
TextBox::TextBox(QWidget *parent)
	: QPlainTextEdit(parent)
	, localEchoEnabled(false)
{
	document()->setMaximumBlockCount(100);

}


void TextBox::putData(const QByteArray &data)
{
	insertPlainText(QString(data));
}


void TextBox::setLocalEchoEnabled(bool set)
{
	localEchoEnabled = set;
}


void TextBox::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()) {
	case Qt::Key_Backspace:
	case Qt::Key_Left:
	case Qt::Key_Right:
	case Qt::Key_Up:
	case Qt::Key_Down:
		break;
	default:
		if (localEchoEnabled)
			QPlainTextEdit::keyPressEvent(e);
		emit getData(e->text().toLocal8Bit());
	}
}