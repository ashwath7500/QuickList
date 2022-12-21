#include "quick_list.hpp"

int main() {
    list<int,fixed_alloc<int> > list = {1,2,3,4};
    list.push_back(2);
    list.push_back(3);
    return 0;
}