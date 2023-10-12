# Results for Assignment 01

## Improvement Iterations

Here's my table showing the improvements I did to make the application go faster.  The **Time** column in the table represents the _wall-clock time_ for a program run.

| Version | Time | Speedup | Memory (KB) | Changes |
| :-----: | ---- | :-----: | :------: | ------- |
| [01](01.cpp) | 634.27s | &mdash; | 4532 | Initial version - no changes |
| [02](02.cpp) | 116.74s | 5.43x | 4896 | Static threaded version |
| [03](03.cpp) | 46.34s | 13.68x | 4828 | Removed redundant vector copy |
| [04](04.cpp) | 56.99s | 11.13x | 4828 | Tried different iterator loop |
