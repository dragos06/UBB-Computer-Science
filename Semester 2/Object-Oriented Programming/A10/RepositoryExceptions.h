#pragma once
#include <exception>
#include <string>

class FileException : public std::exception
{
protected:
	std::string message;
public:
	FileException(const std::string& msg);
	virtual const char* what();
};

class RepositoryException : public std::exception
{
protected:
	std::string message;
public:
	RepositoryException();
	RepositoryException(const std::string& msg);
	virtual ~RepositoryException() {}
	virtual const char* what();
};

class DuplicateTutorialException : public RepositoryException
{
public:
	const char* what();
};

class InexistentTutorialException : public RepositoryException
{
public:
	const char* what();
};