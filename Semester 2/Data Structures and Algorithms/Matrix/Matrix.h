#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;

#define NULL_TELEM 0
class Matrix {
	friend class Node;
private:
	int nrL;
	int nrC;
	Node** T;
	int m;
	int size;
	
public:
	//constructor
	Matrix(int nrLines, int nrCols);

	~Matrix();

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);


	void setElemsOnCol(int col, TElem elem);
	int getSize();
private:
	int hashFunction(int i, int j) const;
	void resize();
};

class Node {
private:
	int i;
	int j;
	TElem info;
	Node* next;
public:
	Node(int i, int j, TElem info, Node* next);
	int getI();
	int getJ();
	TElem getInfo();
	Node* getNext();
	void setI(int i);
	void setJ(int j);
	void setInfo(TElem info);
	void setNext(Node* next);

};