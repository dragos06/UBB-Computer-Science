#pragma once
#include "TutorialRepository.h"

class FileTutorialRepository : public TutorialRepository {

private:
	std::string filename;

	void readFromFile();
	void writeToFile();

public:
	FileTutorialRepository(const std::string& filename);

	void addTutorialRepository(const Tutorial& tutorial) override;
};