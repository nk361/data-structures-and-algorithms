#pragma once
template <class MyType>
class c_node
{
public:
	MyType value;
	//c_node * children[];
	c_node * left, * right;

	c_node() = delete;

	explicit c_node(MyType val)//, int const& kids)
	{
		value = val;
		//children[kids];
		//for (c_node * node : children)
			//node = nullptr;

		left = right = nullptr;
	}

	~c_node()
	{
		delete left, right;
		left = right = nullptr;
	}

	/*c_node<MyType>& operator=(c_node<MyType> r_node)
	{
		value = r_node.value;
		left = r_node.left;
		right = r_node.right;
		return *this;
	}*/
};