# Results for Assignment 02di

## Improvement Iterations

Here's my table showing the improvements I did to make the application go faster.  The **Time** column in the table represents the _wall-clock time_ for a program run.

| Version | Time | Speedup | Memory (KB) | Changes |
| :-----: | ---- | :-----: | :------: | ------- |
| [01](01.cpp) | 634.27s | &mdash; | 4532 | Initial version - no changes |
| [02](02.cpp) | 116.74s | 5.43x | 4896 | Static threaded version |
| [03](03.cpp) | 46.34s | 13.68x | 4828 | Removed redundant vector copy |
| [04](04.cpp) | 56.99s | 11.13x | 4828 | Tried different iterator loop |
| [05](05.cpp) | 69.41s | 9.14x | 4824 | Dynamic retrieval of values |
| [06](06.cpp) | 77.55s | 8.18x | 4840 | Local array of records |
| [07](07.cpp) | 48.44s | 13.09x | 8076 | Dynamic load balancing (100) |
| [07](07.cpp) | 48.37s | 13.11x | 6240 | Dynamic load balancing (250) |
| [07](07.cpp) | 45.95s | 13.81x | 6240 | Dynamic load balancing (500) |
| [07](07.cpp) | 45.30s | 14.00x | 6240 | Dynamic load balancing (2500) |
| [07](07.cpp) | 45.22s | 14.02x | 6240 | Dynamic load balancing (3500) |
| [08](08.cpp) | 69.87s | 9.08x | 4868 | Updated data retrieval method |



