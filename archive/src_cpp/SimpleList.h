#ifndef __SIMPLELIST_H__
#define __SIMPLELIST_H__

template<class NodeType>
class SimpleList  
{
public:
	SimpleList();
	virtual ~SimpleList() {}
	void Clear();

	bool EOL() const { return !m_pCur; }
	void Append(const NodeType&);

	NodeType GetData() const { return m_pCur->GetData(); }
	void MoveFirst();
	void MoveNext();
	void MoveLast();
private:
	template<class NodeType>
	class SimpleListNode
	{
	friend class SimpleList<NodeType>;
	public:
		SimpleListNode(const NodeType& data) : m_pNext(0), m_data(data) {}
		NodeType GetData() const { return m_data; }
	private:
		NodeType m_data;
		SimpleListNode* m_pNext;
	};

private:
	SimpleListNode<NodeType>* m_pFirst;
	SimpleListNode<NodeType>* m_pCur;
	SimpleListNode<NodeType>* m_pLast;
	bool m_bEol;
};

// Constructor
template<class NodeType>
SimpleList<NodeType>::SimpleList()
: m_pFirst(0), m_pCur(0), m_pLast(0), m_bEol(true)
{}

template<class NodeType>
void SimpleList<NodeType>::MoveFirst()
{
	m_pCur=m_pFirst;
}

template<class NodeType>
void SimpleList<NodeType>::MoveLast()
{
	m_pCur=m_pLast;
}

template<class NodeType>
void SimpleList<NodeType>::MoveNext()
{
	if(m_pCur) m_pCur=m_pCur->m_pNext;
}

template<class NodeType>
void SimpleList<NodeType>::Clear()
{
	SimpleListNode<NodeType>* pTmp=0;
	While(m_pFirst)
	{
		pTmp = m_pFirst;
		m_pFirst = m_pFirst->m_pNext;
		delete pTmp;
	}
	m_pFirst=m_pCur=m_pLast=0;
}

template<class NodeType>
void SimpleList<NodeType>::Append(const NodeType& data)
{
	SimpleListNode<NodeType>* pNode = 
		new SimpleListNode<NodeType>(data);
	if(m_pLast)
	{
		m_pLast->m_pNext = pNode;
		m_pLast = pNode;
	}
	else
	{
		m_pFirst=m_pLast=pNode;
	}
}

#endif 
