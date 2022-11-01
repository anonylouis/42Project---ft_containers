# 42Project---ft_containers

Possible implementation of some containers from the standard library C++ :
- [vector](https://github.com/anonylouis/42Project---ft_containers/blob/main/includes/vector.hpp)
- [stack](https://github.com/anonylouis/42Project---ft_containers/blob/main/includes/stack.hpp)
- [map](https://github.com/anonylouis/42Project---ft_containers/blob/main/includes/map.hpp)[^1]
- [set](https://github.com/anonylouis/42Project---ft_containers/blob/main/includes/set.hpp)[^1]

**All methods and functions available since C++98 are made !**[^2]

[*en.subject.pdf*](https://github.com/anonylouis/42Project---ft_containers/blob/main/en.subject.pdf) is the original subject of the project from 42Paris !

In the main/ directory you can find some tests to check how it works.

---
Some commands you can use with the Makefile :

>make + *Container Name*

Compile the main associated with the *Container Name* in two ways : with the original class and with my implementation. The results should be similar !

>make

equivalent to `make vector && make stack && make map`

>make bonus

equivalent to `make && make set`


[^1]: Map and Set store data in a Red-Black tree.
[^2]: You can find them on [cppreference](https://en.cppreference.com/w/cpp/container) or [cplusplus.com](https://cplusplus.com/reference/stl/)