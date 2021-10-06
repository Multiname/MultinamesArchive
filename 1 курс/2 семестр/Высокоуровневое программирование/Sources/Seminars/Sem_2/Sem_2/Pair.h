#ifndef PAIR_H
#define PAIR_H

class Pair
{
public:
	virtual Pair SumNums(Pair & pair) = 0;
	virtual Pair SubNums(Pair & pair) = 0;
	virtual void setFirst(int first) = 0;
	virtual int getFirst() = 0;
	virtual int getSec() = 0;

protected:
	int m_first_num{};
	int m_second_num{};
};

#endif // !PAIR_H