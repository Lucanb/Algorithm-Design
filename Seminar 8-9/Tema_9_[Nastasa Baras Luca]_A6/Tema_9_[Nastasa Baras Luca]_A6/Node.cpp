#include "Node.h"
//Class Functions
Node::Node()
{
	end = false;
	fail_redirect = NULL;
	for (int i = 0; i < CHARSET; i++)
		child_nodes[i] = NULL;
	op = 0;
}