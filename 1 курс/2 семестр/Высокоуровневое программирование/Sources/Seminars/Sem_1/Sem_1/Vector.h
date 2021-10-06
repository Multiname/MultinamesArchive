#ifndef VECTOR_H

#define VECTOR_H

class Vector
{
public:
	Vector();
	Vector(int* list, int size);
	Vector(Vector * vector);
	~Vector();

	int GetSize();
	int GetElement(int position);

	int SetElement(int position, int element);

	void AddToEnd(int element);
	void DeleteLast();
	void DeleteAll();
	bool CheckEmpty();

private:
	int* m_list;
	int m_size;
};

#endif // !VECTOR_H