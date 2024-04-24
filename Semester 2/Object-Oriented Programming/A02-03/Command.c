/*#include "Command.h"
#include <string.h>
#include <stdlib.h>


Operation* createOperation(Medicine* m, char* operationType)
{
	Operation* o = malloc(sizeof(Operation));
	if (o == NULL) {
		return NULL;
	}
	o->medicine->name = malloc(sizeof(char) * (strlen(m->name)+1));
	if (o->medicine->name == NULL) {
		free(o);
		return NULL;
	}
	strcpy(o->medicine->name, m->name);
	o->medicine->concentration = m->concentration;
	o->medicine->quantity = m->quantity;
	o->medicine->price = m->price;
	if (operationType != NULL) {
		o->operationType = malloc(sizeof(char) * (strlen(operationType) + 1));
		if (o->operationType == NULL) {
			return NULL;
		}
		strcpy(o->operationType, operationType);
	}
	else
		o->operationType = NULL;
	return o;
}

void destroyOperation(Operation* o) {
	if (o == NULL)
		return;
	free(o->medicine);
	free(o->operationType);
	free(o);
}

Operation* copyOperation(Operation* o) {
	Operation* copy = createOperation(getMedicine(o), getOperationType(o));
	return copy;
}

char* getOperationType(Operation* o) {
	return o->operationType;
}

Medicine* getMedicine(Operation* o) {
	return o->medicine;
}

OperationStack* createStack() {
	OperationStack* s = malloc(sizeof(OperationStack));
	if (s == NULL)
		return NULL;
	s->stack = createDynamicArray(10, destroyOperation, equalMedicine);
	if (s->stack == NULL) {
		free(s);
		return NULL;
	}
	return s;
}

void destroyStack(OperationStack* s) {
	if (s == NULL)
		return;
	destroyDynamicArray(s->stack);
	free(s);
}

void push(OperationStack* s, Operation* o) {
	if (s == NULL || o == NULL)
		return;
	addElemToDyanmicArray(s->stack, o);
}

Operation* pop(OperationStack* s) {
	if (s == NULL)
		return NULL;
	int lastPos = getSizeDynamicArray(s->stack) - 1;
	Operation* o = get(s->stack, lastPos);
	Operation* lastOperation = copyOperation(o);
	deleteElement(s->stack, lastPos);//DED HERE
	return lastOperation;
}

int isEmpty(OperationStack* s) {
	if (s == NULL)
		return 1;
	return getSizeDynamicArray(s->stack) == 0;
}
*/