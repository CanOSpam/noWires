#include "frame.h"
/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: frame.cpp
--
-- PROGRAM: noWires
--
-- FUNCTIONS: None
--
-- DATE: December 05, 2017
--
-- REVISIONS: None
--
-- DESIGNER: Tim Bruecker
--
-- PROGRAMMER: Tim Bruecker
--
-- NOTES:
-- This is the parent class for frames. It is a wrapper around a QByteArray and offers a pure virtual function that is
-- meant to be overriden to provide a method to create frames.
----------------------------------------------------------------------------------------------------------------------*/
frame::frame(QByteArray data)
	:mData(data)
{
}