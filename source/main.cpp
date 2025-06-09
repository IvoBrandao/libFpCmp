#include "FpCmp.hpp"
#include <iostream>
#include <iomanip>

int main() {
    std::cout << std::boolalpha;

    // --- Example 1: Comparing doubles with the new areEqual() ---
    std::cout << "--- Double Precision Examples ---\n";
    double d1 = 1.0;
    double d2 = 1.0 + 1e-12;
    double d3 = 1.1;

    std::cout << "areEqual(d1, d2) [default comb. tol]? "
              << fpcomp::areEqual(d1, d2) << "\n";

    std::cout << "areEqual(d1, d3) [default]? "
              << fpcomp::areEqual(d1, d3) << "\n";

    std::cout << "greaterThan(d3, d1) [default]? "
              << fpcomp::greaterThan(d3, d1) << "\n";

    // Zero checks
    std::cout << "isZero(1e-13)? "
              << fpcomp::isZero(1e-13) << "\n";
    std::cout << "isZero(1e-3, 1e-2, ToleranceType::Absolute)? "
              << fpcomp::isZero(1e-3, 1e-2, fpcomp::ToleranceType::Absolute) << "\n\n";

    // --- Example 2: Comparing floats ---
    std::cout << "--- Single Precision (float) Examples ---\n";
    float f1 = 1.0f;
    float f2 = 1.0f + 1e-7f;
    float f3 = 1.0f + 1e-5f;

    std::cout << "areEqual(f1, f2)? "
              << fpcomp::areEqual(f1, f2) << "\n";

    std::cout << "greaterThanOrEqual(f3, f1)? "
              << fpcomp::greaterThanOrEqual(f3, f1) << "\n";

    std::cout << "greaterThanOrEqual(f1, f2)? "
              << fpcomp::greaterThanOrEqual(f1, f2) << "\n\n";

    // --- Example 3: Custom precision & type ---
    std::cout << "--- Custom-Precision & ToleranceType Example ---\n";
    double val1 = 100.0;
    double val2 = 100.5;

    std::cout << "areEqual(val1, val2) [default]? "
              << fpcomp::areEqual(val1, val2) << "\n";

    // 1% relative-only tolerance
    double tol = 0.01;
    std::cout << "areEqual(val1, val2, tol=0.01, Relative)? "
              << fpcomp::areEqual(val1, val2, tol, fpcomp::ToleranceType::Relative)
              << "\n";

    // 0.5 absolute-only tolerance
    tol = 0.5;
    std::cout << "areEqual(val1, val2, tol=0.5, Absolute)? "
              << fpcomp::areEqual(val1, val2, tol, fpcomp::ToleranceType::Absolute)
              << "\n";

    return 0;
}
