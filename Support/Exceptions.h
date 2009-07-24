#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <QString>

class QException : public std::runtime_error
{
		public:
	QException(QString msg) : runtime_error(msg.toStdString()) {}

	QString what() { return runtime_error::what(); }
};

class ObjectNotFound : public QException
{
		public:
	ObjectNotFound(QString msg = "Object not found") : QException(msg) {}
};

class InvalidArgument : public QException
{
		public:
	InvalidArgument(QString msg = "Invalid argument") : QException(msg) {}
};

class InvalidFile : public QException
{
		public:
	InvalidFile(QString msg = "Invalid file") : QException(msg) {}
};

#endif // EXCEPTIONS_H
