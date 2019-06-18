#include "pch.h"

/*
 * these are considered depth first search
 * in order traversal navigates all nodes in a normal bst in ascending order
 * left root right
 *
 * post order traversal
 * left right root
 *
 * preorder traversal
 * root left right
 *
 * level order traversal or breadth first search
 * left to right each level
 *
 * I'm kinda thinking that converting the tree into a 1D form to be traversed sounds easiest
 * but that's kinda incorrect
 * I should traverse the way that the structure is
 * THESE CANNOT RELY ON VALUES FOR NAVIGATION
 */

 /*
  * I should look into heap/tree merging
  */

/*
 * unique pointers can't be shared
 * shared pointers have a reference count and delete when it reaches 0
 * weak pointers don't increase the reference count of shared pointers
 * if any don't point to anything anymore, they return nullptr?
 *
 * smart pointers are apparently not thread safe I think, which worries me a little
 */

 /*
  * Copying a heap would be easiest and most accurate with a level order iterator for the new and old heaps
  */

int main(int argc, char* argv[])//char **argv
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}