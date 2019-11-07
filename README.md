## DualPivotQuicksort for C++

This repository contains a C++ port of the the sorting algorithm BlockQuicksort of the Java OpenJDK [1, 2], firstly proposed by Vladimir Yaroslavskiy. The C++ version moves elements whenever possible and accepts an optional comparator. The interface supports a subset of ```std::sort```:
```
dual_pivot_quicksort::sort(Iterator begin, Iterator end, [Comparator comp])
```
and is easy to use
```
std::vector<double> v(200);
// Generate your data.
dual_pivot_quicksort::sort(v.begin(), v.end(), [st::less<>{}]);
assert(std::is_sorted(v.begin(), v.end()));
```

### Benchmark

You can compare DualPivotQuicksort with std::sort by typing the following lines into your terminal:
```
DualPivotQuicksort> mkdir build
DualPivotQuicksort> cd build
DualPivotQuicksort> cmake -DCMAKE_BUILD_TYPE=Release ..
DualPivotQuicksort> make benchmark
DualPivotQuicksort> ./benchmark
```

### Usage
If you want to use BlockQuickSort in our cmake project in executable *a*, include BlockQuicksort via ```#include <block_quick_sort.hpp>``` and add the following lines to you cmake file:
```
add_subdirectory(path-to-this-repository)
target_link_libraries(a dualpivotquicksort)
```

[1] https://openjdk.java.net/
[2] http://hg.openjdk.java.net/jdk/jdk/raw-file/tip/src/java.base/share/classes/java/util/DualPivotQuicksort.java