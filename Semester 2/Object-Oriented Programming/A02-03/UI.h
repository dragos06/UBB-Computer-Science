#pragma once
#include "Service.h"

typedef struct {
	Service* service;
}UI;


UI* createUI();
void destroyUI(UI* ui);

void startUI(UI* ui);