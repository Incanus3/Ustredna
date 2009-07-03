#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <QString>

class GeneralException : public std::runtime_error
{
		public:
	GeneralException(QString msg) : runtime_error(msg.toStdString()) {}

	QString what() { return runtime_error::what(); }
};

class ObjectNotFound : public GeneralException
{
		public:
	ObjectNotFound(QString msg = "Object not found") : GeneralException(msg) {}
};

#endif // EXCEPTIONS_H
