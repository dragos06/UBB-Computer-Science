#pragma once
#include "TutorialRepository.h"
#include "Service.h"
#include "Tutorial.h"

class Action {
public:
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;

};

class ActionAdd : public Action {
private:
	TutorialRepositoryBase* repo;
	Tutorial addedTutorial;
public:
	ActionAdd(TutorialRepositoryBase* repo, const Tutorial& tutorial): repo{repo}, addedTutorial{tutorial}{}
	void executeUndo() override {
		this->repo->deleteTutorialRepository(addedTutorial);
	}
	void executeRedo() override {
		this->repo->addTutorialRepository(addedTutorial);
	}
};

class ActionDelete : public Action {
private:
	TutorialRepositoryBase* repo;
	Tutorial deletedTutorial;
public:
	ActionDelete(TutorialRepositoryBase* repo, const Tutorial& tutorial) : repo{ repo }, deletedTutorial{ tutorial } {}
	void executeUndo() override {
		this->repo->addTutorialRepository(deletedTutorial);
	}
	void executeRedo() override {
		this->repo->deleteTutorialRepository(deletedTutorial);
	}
};

class ActionUpdate : public Action {
private:
	TutorialRepositoryBase* repo;
	Tutorial oldTutorial;
	Tutorial newTutorial;
public:
	ActionUpdate(TutorialRepositoryBase* repo, const Tutorial& new_tutorial, const Tutorial& old_tutorial): repo{repo}, newTutorial{new_tutorial}, oldTutorial{old_tutorial}{}
	void executeUndo() override {
		this->repo->deleteTutorialRepository(newTutorial);
		this->repo->addTutorialRepository(oldTutorial);
	}
	void executeRedo() override {
		this->repo->deleteTutorialRepository(oldTutorial);
		this->repo->addTutorialRepository(newTutorial);
	}
};