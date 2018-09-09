#pragma once
#include <iostream>
#include "c_heap.h"

class c_max_heap : public c_heap
{
public:
	c_max_heap() = delete;

	explicit c_max_heap(int const& num) : c_heap(num) {}

	void add_item(int const& val) override
	{
		//if(size > 0 && size < 3)
		//{
			//root->left = new c_node<int>{ val };

			//std::cout << "root " << (root == nullptr) << std::endl;
			//std::cout << root->value << std::endl;

			//std::cout << "Results" << std::endl;
			//std::cout << (root->left == nullptr) << std::endl;
			//std::cout << (root->right == nullptr) << std::endl;

			//c_node<int> * test = new c_node<int>{ val };
			//std::cout << test->value << std::endl;
			//delete test;


			//if (root->left == nullptr)
				//root->left = new c_node<int>{ val };
			//else
				//root->right = new c_node<int>{ val };

			//std::cout << "Working here" << std::endl;

			//(root->left == nullptr ? root->left : root->right) = new c_node<int>{ val };
			//size++;
		//}
		//else
		//{
			//std::cout << "Shouldn't get here yet" << std::endl;
			//need to know amount currently in last generation and the amount that last generation can hold
			//int amount_last_level = size - amount_full_tree(amount_complete_levels(size));//amount in last level
			//where the new value is inserted should be at this ^ plus one in the last level
			int open_spot = amount_last_level(size);
			//std::cout << open_spot << std::endl;
			//int complete_levels = amount_complete_levels(size);//how many levels I need to navigate through
			//std::cout << amount_complete_levels(size) << " complete" << std::endl;

			//If last level is full, find the max of the next level, else, amount of the partially complete one
			//int max_of_last_level = amount_last_level(size) == 0 ? amount_in_level(amount_complete_levels(size)) : amount_in_level(amount_complete_levels(size) - 1);
			//SECOND PART OF THIS LINE ^^^ GIVES WRONG LEVEL TO GET THE MAX OF
			int max_of_last_level = amount_in_level(amount_complete_levels(size));

		//if (amount_last_level(size) == 0)
				//max_of_last_level = amount_in_level(amount_complete_levels(size));
			//else
				//max_of_last_level = amount_in_level(amount_complete_levels(size) - 1);

				

			//int max_of_last_level = amount_in_level(amount_full_tree(amount_complete_levels(size)) + 1);
			//std::cout << "Value " << val << std::endl;
			//std::cout << "max " << max_of_last_level << std::endl;
			//now I know where the open spot is, I need to navigate to it
			//how will I tell which ways to turn?
			//I need to calculate the amount the last level would have if completed, to know how far left or right I need to go
			
			//do I need to know how many full levels there are?
			//or can I just keep going down the tree until there's an open left or right, checking left first?
			c_node<int> * current = root;
			int current_level = 0;
			int previous_calc = 0;
			while(true)
			{
				//std::cout << open_spot << " < " << previous_calc << " + " << max_of_last_level << " / " << amount_in_level(current_level + 1) << std::endl;
				//std::cout << "Looping forever?" << std::endl;

				if(open_spot < previous_calc + max_of_last_level / amount_in_level(current_level + 1))
				{
					if(current->left != nullptr)
					{
						current = current->left;
					}
					else
					{
						current->left = new c_node<int>{ val };
						size++;
						break;
					}
				}
				else
				{
					previous_calc += max_of_last_level / amount_in_level(current_level + 1);

					if(current->right != nullptr)
					{
						current = current->right;
					}
					else
					{
						current->right = new c_node<int>{ val };
						size++;
						break;
					}
				}
				++current_level;
				
				
				//root max/2
				//next max/4
			}
		//}

		
		//I think I do need to store a size. Many places seem to store the tree as an array too, but I'd like to avoid that in this class
		//I may make another class that purely uses arrays for max and min heaps
	}

	void add_items(std::vector<int> const& vals) override
	{
		
	}

	void remove_item() override//this would be the same except the > check in a min heap
	{
		c_node<int> * current = root;
		while(true)
		{
			if(current->left != nullptr && current->right != nullptr)//if node has two children, set current value to the largest of the two which becomes current
			{
				current->value = current->left->value > current->right->value ? current->left->value : current->right->value;
				current = current->left->value > current->right->value ? current->left : current->right;
			}
			else if(current->left == nullptr && current->right == nullptr)//a previous node has taken current's value and it's the end of the tree
			{
				delete current;
				--size;
				break;
			}
			else//if current has only one child, take that value and delete the child since heaps should only have one child in the last generation
			{
				current->value = current->left != nullptr ? current->left->value : current->right->value;
				//current = current->left != nullptr ? current->left : current->right;
				delete (current->left != nullptr ? current->left : current->right);
				--size;
				break;
			}
		}
	}

	

	/*void remove_item() override
	{
		if (root->left == nullptr && root->right == nullptr)
			delete root;
		else
		{
			//for the first one
			//compare the two siblings and take the largest of the two
		}
	}

	void fix_violations() const//not sure if I need this yet or not
	{
		c_node<int> * current = root;
		while (true)
		{
			if (current->value < current->left->value && current->left != nullptr)
			{
				if (current->right->value > current->left->value && current->value < current->right->value)
				{
					//swap current and right values
					int const temp = current->value;
					current->value = current->right->value;
					current->right->value = temp;
					current = current->right;
				}
				else
				{
					//swap current and left values
					int const temp = current->value;
					current->value = current->left->value;
					current->left->value = temp;
					current = current->left;
				}
			}
			else if (current->value < current->right->value && current->right != nullptr)
			{
				//swap current and right values
				int const temp = current->value;
				current->value = current->right->value;
				current->right->value = temp;
				current = current->right;
			}
			else
				break;
		}
	}*/
};
