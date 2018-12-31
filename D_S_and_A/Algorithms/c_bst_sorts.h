#pragma once
#include <vector>

template <class MyType, template <class ValType, template <class> class NodeType, typename Operation> class BstType, template <class> class NodeType, typename Operation = std::less<>>
class c_bst_sorts
{
public:
	std::vector<MyType> static& sort(std::vector<MyType>& arr);
};

#include "c_bst_sorts.inl"