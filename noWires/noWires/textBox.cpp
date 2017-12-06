#include "textBox.h"

#include <QtCore/QDebug>

/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: textBox.cpp
--
-- PROGRAM: noWries
--
-- FUNCTIONS:
-- void putData()
-- void setLocalEchoEnabled()
-- void keyPressEvent()
--
-- DATE: Dec 05, 2017
--
-- REVISIONS: None
--
-- DESIGNERS: Tim Bruecker, JC Tee, Keir Forster, Alex Xia
--
-- PROGRAMMERS: Tim Bruecker, JC Tee, Keir Forster, Alex Xia
--
-- NOTES:
-- This class handles all output and printing to the main window.
--
----------------------------------------------------------------------------------------------------------------------*/
TextBox::TextBox(QWidget *parent)
	: QPlainTextEdit(parent)
	, localEchoEnabled(false)
{
	document()->setMaximumBlockCount(100);

}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: putData
--
-- DATE: December 05, 2017
--
-- REVISIONS: None
--
-- DESIGNER: Keir Forster
--
-- PROGRAMMER: Keir Forster
--
-- INTERFACE: void putData()
--
-- RETURNS: void
--
-- NOTES:
-- This function should be called every time the data is read after passing error detection.
--
----------------------------------------------------------------------------------------------------------------------*/
void TextBox::putData(const QByteArray &data)
{
	insertPlainText(QString(data));
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setLocalEchoEnabled
--
-- DATE: December 05, 2017
--
-- REVISIONS: None
--
-- DESIGNER: Keir Forster
--
-- PROGRAMMER: Keir Forster
--
-- INTERFACE: void setLocalEchoEnabled()
--
-- RETURNS: void
--
-- NOTES:
-- This function should be called when the main window is constructed to set whether or not text is echoed to the main window.
--
----------------------------------------------------------------------------------------------------------------------*/
void TextBox::setLocalEchoEnabled(bool set)
{
	localEchoEnabled = set;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: keyPressEvent
--
-- DATE: December 05, 2017
--
-- REVISIONS: None
--
-- DESIGNER: Keir Forster
--
-- PROGRAMMER: Keir Forster
--
-- INTERFACE: void keyPressEvent()
--
-- RETURNS: void
--
-- NOTES:
-- This function should be called for each character when echoing is enabled.
--
----------------------------------------------------------------------------------------------------------------------*/
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