#ifndef __SIMPLESTACK_H__
#define __SIMPLESTACK_H__

template<int STACKSIZE, class StackType>
class SimpleStack  
{
public:
	SimpleStack() : m_iIdx(-1) {}
	virtual ~SimpleStack() {}

	int Size() const { return m_iIdx+1; }
	bool IsFull() const { return Size() == STACKSIZE; }
	bool IsEmpty() const { return Size() == 0; }
	void Push(const StackType& data)
	{	m_cell[++m_iIdx] = data; }
	StackType Pop()
	{	return m_cell[m_iIdx--]; }
	StackType Peek()
	{	return m_cell[m_iIdx]; }

private:
	StackType m_cell[STACKSIZE];
	int m_iIdx;
};

#endif
