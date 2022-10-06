#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
typedef
tree < int, null_type ,less<int>,
rb_tree_tag,
tree_order_statistics_node_update > ordered_set;

/*
    Operations :
    find_by_order : returns an iterator to the k-th
    largest element (counting from zero).
    order_of_key :  returns the number of items in
    a set that are strictly smaller than our item.
    # to use as a multiset just insert a pair<int,int> with unique second element, change
    int to pair<int,int> in typedef part
*/

