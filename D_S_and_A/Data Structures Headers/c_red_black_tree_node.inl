#pragma once
#include "c_red_black_tree_node.h"

template <typename ValType>
c_red_black_tree_node<ValType>::c_red_black_tree_node(ValType const& val, bool const& r) : c_poly_node<ValType>(val, 2), red(r) {}