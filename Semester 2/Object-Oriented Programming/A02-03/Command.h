/*#pragma once
#include "Domain.h"
#include "DynamicArray.h"
#include <string.h>


typedef struct {
	Medicine* medicine;
	char* operationType;
}Operation;

Operation* createOperation(Medicine* m, char* operationType);
void destroyOperation(Operation* o);
Operation* copyOperation(Operation* o);
char* getOperationType(Operation* o);
Medicine* getMedicine(Operation* o);

typedef struct {
	DynamicArray* stack;
} OperationStack;

OperationStack* createStack();
void destroyStack(OperationStack* s);
void push(OperationStack* s, Operation* o);
Operation* pop(OperationStack* s);
int isEmpty(OperationStack* s);

//void testsStack();
*/