#pragma once
#include <QByteArray>

// From https://stackoverflow.com/questions/30660127/append-quint16-unsigned-short-to-qbytearray-quickly
// Designed and implemented by Matteo Italia https://stackoverflow.com/users/214671/matteo-italia
QByteArray &operator<<(QByteArray& l, quint8 r)
{
	l.append(r);
	return l;
}

// From https://stackoverflow.com/questions/30660127/append-quint16-unsigned-short-to-qbytearray-quickly
// Designed and implemented by Matteo Italia https://stackoverflow.com/users/214671/matteo-italia
QByteArray &operator<<(QByteArray& l, quint16 r)
{
	return l << quint8(r >> 8) << quint8(r);
}

// From https://stackoverflow.com/questions/30660127/append-quint16-unsigned-short-to-qbytearray-quickly
// Designed and implemented by Matteo Italia https://stackoverflow.com/users/214671/matteo-italia
QByteArray &operator<<(QByteArray &l, quint32 r)
{
	return l << quint16(r >> 16) << quint16(r);
}