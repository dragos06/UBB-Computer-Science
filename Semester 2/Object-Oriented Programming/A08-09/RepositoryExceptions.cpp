#include "RepositoryExceptions.h"

FileException::FileException(const std::string& msg): message(msg)
{
}

const char* FileException::what()
{
	return this->message.c_str();
}

RepositoryException::RepositoryException() : exception{}, message{""}
{
}

RepositoryException::RepositoryException(const std::string& msg): message{msg}
{
}

const char* RepositoryException::what()
{
	return this->message.c_str();
}

const char* DuplicateTutorialException::what()
{
	return "There is another tutorial with the same title and presenter";
}

const char* InexistentTutorialException::what()
{
	return "There are no tutorials with the given title and presenter";
}
