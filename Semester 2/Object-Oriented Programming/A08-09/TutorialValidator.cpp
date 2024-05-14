#include "TutorialValidator.h"
using namespace std;

TutorialException::TutorialException(std::vector<std::string> _errors) : errors{_errors}
{
}

std::vector<std::string> TutorialException::getErrors() const
{
	return this->errors;
}

void TutorialValidator::validate(const Tutorial& tutorial)
{
	vector<string> errors;
	if (tutorial.getTitle().size() < 3)
		errors.push_back(string("The title cannot be less than 3 characters!\n"));
	if (tutorial.getDuration() == 0)
		errors.push_back(string("The duration cannot be 0!\n"));

	size_t posWww = tutorial.getLink().find("www");
	size_t posHttps = tutorial.getLink().find("https");
	if (posWww != 0 && posHttps != 0)
		errors.push_back("The tutorial must what with the following strings: \"www\" or \"https\"");

	if (errors.size() > 0)
		throw TutorialException(errors);

}
