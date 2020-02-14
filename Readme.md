# ft_containers

This is the ft_containers project from the new cursus.

You have to reimplement the following C++ containers:
- [x] Vector ([std::vector])
- [x] List ([std::list])
- [x] Stack ([std::stack])
- [ ] Map ([std::map])
- [x] Queue ([std::queue])

STL is not allowed. That means you cannot you cannot use `<iterator>` or even `<utility>`.

Bonus:
- [ ] Set ([std::set])
- [ ] Deque ([std::deque])
- [ ] Multimap ([std::multimap])
- [ ] Multiset ([std::multiset])

This implementation comes with a large set of tests in the test directory.

[std::vector]: http://www.cplusplus.com/reference/vector/vector
[std::list]: http://www.cplusplus.com/reference/list/list
[std::stack]: http://www.cplusplus.com/reference/stack/stack
[std::map]: http://www.cplusplus.com/reference/map/map
[std::queue]: http://www.cplusplus.com/reference/queue/queue
[std::set]: http://www.cplusplus.com/reference/set/set
[std::deque]: http://www.cplusplus.com/reference/deque/deque
[std::multimap]: http://www.cplusplus.com/reference/map/multimap
[std::multiset]: http://www.cplusplus.com/reference/set/multiset

## docs

Here are some random useful / interesting links:
- [Which headers are STL](http://cs.stmarys.ca/~porter/csc/ref/stl/headers.html)
- [An introduction to C++ Traits](https://accu.org/index.php/journals/442)
- [What is meant by "Constant Amortized Time" when talking about time complexity of an algorithm?](https://stackoverflow.com/questions/200384/constant-amortized-time)
- [Map implementation - AVL tree algorithm visualization](https://www.cs.usfca.edu/~galles/visualization/AVLtree.html)
- [Map implementation - AVL tree data structure](https://www.codesdope.com/course/data-structures-avl-trees/)
- [Map implementation - Red-Black trees (not implemented here)](http://pages.cs.wisc.edu/~paton/readings/Red-Black-Trees/)

## todo

- Vector: tests for const iter
- List: operations (splice, ...)
- List: max_size
- List: coplien form for ListNode
- Queue and Stack: constructors and operator= private
