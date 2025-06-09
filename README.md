# libFpCmp

`libFpCmp` is a modern C++ header-only library offering robust, tolerance-based floating-point comparisons. It supports absolute, relative, or combined tolerance modes and works with `float`, `double`, and `long double`.

## Features

* **Tolerance Modes** (`ToleranceType` enum):

  * **Absolute**: Compare using only absolute tolerance (`atol`).
  * **Relative**: Compare using only relative tolerance (`rtol`).
  * **Combined**: Use both absolute and relative tolerances.

* **Equality Check**: `areEqual(a, b, precision, type)`

* **Zero Check**: `isZero(value, precision, type)`

* **Greater Than**: `greaterThan(a, b, precision, type)`

* **Greater Than or Equal**: `greaterThanOrEqual(a, b, precision, type)`

* **Less Than**: `lessThan(a, b, precision, type)`

* **Less Than or Equal**: `lessThanOrEqual(a, b, precision, type)`

All functions default to a combined tolerance of 4× machine epsilon when `precision` and `type` are omitted.

## Getting Started

### Installation

Simply copy the header into your project:

```c++
libfpcmp/
└── libs/
    └── FpCmp/
        └── include/
            └── FpCmp.hpp
```

Include it in your code:

```cpp
#include "FpCmp.hpp"
```

This library requires C++17 or later.

### Basic Usage

```cpp
#include "FpCmp.hpp"
#include <iostream>

int main() {
    double x = 0.1 + 0.2;
    double y = 0.3;

    // Default (combined) tolerance
    if (fpcomp::areEqual(x, y)) {
        std::cout << "x and y are approximately equal\n";
    }

    // Absolute-only zero check
    if (fpcomp::isZero(x - y, 1e-12, fpcomp::ToleranceType::Absolute)) {
        std::cout << "Difference is within 1e-12 absolute tolerance\n";
    }
}
```

### Examples

#### Double Precision

```cpp
double d1 = 1.0;
double d2 = 1.0 + 1e-12;

std::cout << std::boolalpha;
std::cout << "areEqual(d1, d2)? "
          << fpcomp::areEqual(d1, d2) << '\n';
std::cout << "greaterThan(d2, d1)? "
          << fpcomp::greaterThan(d2, d1) << '\n';
```

#### Custom Precision & Mode

```cpp
double a = 100.0, b = 100.5;

// 1% relative-only
bool rel = fpcomp::areEqual(a, b, 0.01, fpcomp::ToleranceType::Relative);

// 0.5 absolute-only
bool abs = fpcomp::areEqual(a, b, 0.5, fpcomp::ToleranceType::Absolute);
```

## Running Tests

This project includes Google Test–based unit tests in `tests/`:

```bash
mkdir build && cd build
cmake .. .
make
```

## Contributing

Contributions welcome! Please open issues or PRs. For significant changes, discuss via an issue first.

## License

MIT License. See [LICENSE](LICENSE) for details.
