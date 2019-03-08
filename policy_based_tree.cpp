// Red-black tree with custom node update policy using GNU pb_ds
// Docs: https://gcc.gnu.org/onlinedocs/libstdc++/ext/pb_ds/tree_based_containers.html
// Example: order statistic policy

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template<class Node_CItr, class Node_Itr, class Cmp_Fn, class _Alloc>
struct node_update {
    virtual Node_CItr node_begin() const = 0;
    virtual Node_CItr node_end() const = 0;

    using metadata_type = int;

    // Get the node invariant or identity if the node does not exist
    inline metadata_type at(Node_CItr it) {
        return it != node_end() ? it.get_metadata() : 0;
    }

    // If mapped type == null_type, **it gives the key
    // otherwise, *it gives a key-value pair
    int order_of_key(int x) { return order_of_key(x, node_begin()); }
    int order_of_key(int x, Node_CItr it) {
        if (it == node_end()) return 0;
        auto l_it = it.get_l_child(), r_it = it.get_r_child();
        if (Cmp_Fn()(x, **it)) // x < cur
            return order_of_key(x, l_it);
        if (Cmp_Fn()(**it, x)) // x > cur
            return 1 + at(l_it) + order_of_key(x, r_it);
        return at(l_it);
    }

    int find_by_order(int k) { return find_by_order(k, node_begin()); }
    int find_by_order(int k, Node_CItr it) {
        if (it == node_end()) return -INF;
        auto l_it = it.get_l_child(), r_it = it.get_r_child();
        metadata_type order = at(l_it);
        if (k == order)
            return **it;
        if (k < order)
            return find_by_order(k, l_it);
        return find_by_order(k-order-1, r_it);
    }

    // This method restores the invariant of the node and must be implemented
    // `it` is a node whose decendants have valid invariants, and whose invariant may be violated
    // Example invariant: size of subtree
    void operator()(Node_Itr it, Node_CItr) {
        auto l_it = it.get_l_child(), r_it = it.get_r_child();
        metadata_type l = at(l_it), r = at(r_it);
        const_cast<metadata_type&>(it.get_metadata()) =
            l + r + 1;
    }
};

using ordered_tree = tree<int, null_type, less<int>, rb_tree_tag, node_update>;
