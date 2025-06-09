#ifndef FPCOMP_HPP
#define FPCOMP_HPP

#include <algorithm>
#include <cmath>
#include <limits>
#include <type_traits>

namespace fpcomp {

/**
 * @brief Types of tolerance for comparison.
 */
enum class ToleranceType {
    Absolute,   // Use only absolute tolerance
    Relative,   // Use only relative tolerance
    Combined    // Use both absolute and relative tolerance
};

/**
 * @brief Compares two floating-point numbers for near equality.
 * @tparam T A floating-point type (float, double, long double).
 * @param a The first floating-point number.
 * @param b The second floating-point number.
 * @param rtol The relative tolerance. Defaults to 4 * epsilon.
 * @param atol The absolute tolerance. Defaults to 4 * epsilon.
 * @return True if the numbers are considered close, false otherwise.
 */
template <typename T,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool is_close(T a, T b,
              T rtol = std::numeric_limits<T>::epsilon() * 4,
              T atol = std::numeric_limits<T>::epsilon() * 4) {
    if (std::isnan(a) || std::isnan(b) || std::isinf(a) || std::isinf(b)) {
        return false;
    }
    return std::fabs(a - b) <= (atol + rtol * std::max(std::fabs(a), std::fabs(b)));
}

/**
 * @brief Checks if a floating-point number is approximately zero.
 * @tparam T A floating-point type.
 * @param v The value to check.
 * @param precision The tolerance value.
 * @param type The type of tolerance to use.
 * @return True if v is "zero" within the given tolerance.
 */
template <typename T,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool isZero(T v,
            T precision = std::numeric_limits<T>::epsilon() * 4,
            ToleranceType type = ToleranceType::Combined) {
    T rtol = T(0), atol = T(0);
    switch (type) {
    case ToleranceType::Absolute:
        atol = precision;
        break;
    case ToleranceType::Relative:
        rtol = precision;
        break;
    case ToleranceType::Combined:
        atol = precision;
        rtol = precision;
        break;
    }
    return is_close(v, T(0), rtol, atol);
}

/**
 * @brief Checks if two floating-point numbers are equal within a specified precision and type.
 * @tparam T A floating-point type.
 * @param a The first number.
 * @param b The second number.
 * @param precision The tolerance value.
 * @param type The type of tolerance to use.
 * @return True if a and b are equal within tolerance.
 */
template <typename T,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool areEqual(T a, T b,
              T precision = std::numeric_limits<T>::epsilon() * 4,
              ToleranceType type = ToleranceType::Combined) {
    T rtol = T(0), atol = T(0);
    switch (type) {
    case ToleranceType::Absolute:
        atol = precision;
        break;
    case ToleranceType::Relative:
        rtol = precision;
        break;
    case ToleranceType::Combined:
        atol = precision;
        rtol = precision;
        break;
    }
    return is_close(a, b, rtol, atol);
}

/**
 * @brief Checks if one floating-point number is strictly greater than another.
 */
template <typename T,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool is_greater(T a, T b,
                T rtol = std::numeric_limits<T>::epsilon() * 4,
                T atol = std::numeric_limits<T>::epsilon() * 4) {
    return a > b && !is_close(a, b, rtol, atol);
}

/**
 * @brief Checks if one floating-point number is strictly less than another.
 */
template <typename T,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool is_less(T a, T b,
             T rtol = std::numeric_limits<T>::epsilon() * 4,
             T atol = std::numeric_limits<T>::epsilon() * 4) {
    return a < b && !is_close(a, b, rtol, atol);
}

/**
 * @brief Checks if one floating-point number is greater than or equal to another.
 */
template <typename T,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool is_greater_equal(T a, T b,
                      T rtol = std::numeric_limits<T>::epsilon() * 4,
                      T atol = std::numeric_limits<T>::epsilon() * 4) {
    return a > b || is_close(a, b, rtol, atol);
}

/**
 * @brief Checks if one floating-point number is less than or equal to another.
 */
template <typename T,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool is_less_equal(T a, T b,
                   T rtol = std::numeric_limits<T>::epsilon() * 4,
                   T atol = std::numeric_limits<T>::epsilon() * 4) {
    return a < b || is_close(a, b, rtol, atol);
}

/**
 * @brief Greater-than comparison with precision and tolerance type.
 */
template <typename T,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool greaterThan(T a, T b,
                 T precision = std::numeric_limits<T>::epsilon() * 4,
                 ToleranceType type = ToleranceType::Combined) {
    T rtol = T(0), atol = T(0);
    switch (type) {
    case ToleranceType::Absolute:
        atol = precision;
        break;
    case ToleranceType::Relative:
        rtol = precision;
        break;
    case ToleranceType::Combined:
        atol = precision;
        rtol = precision;
        break;
    }
    return is_greater(a, b, rtol, atol);
}

/**
 * @brief Greater-than-or-equal comparison with precision and tolerance type.
 */
template <typename T,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool greaterThanOrEqual(T a, T b,
                        T precision = std::numeric_limits<T>::epsilon() * 4,
                        ToleranceType type = ToleranceType::Combined) {
    T rtol = T(0), atol = T(0);
    switch (type) {
    case ToleranceType::Absolute:
        atol = precision;
        break;
    case ToleranceType::Relative:
        rtol = precision;
        break;
    case ToleranceType::Combined:
        atol = precision;
        rtol = precision;
        break;
    }
    return is_greater_equal(a, b, rtol, atol);
}

/**
 * @brief Less-than comparison with precision and tolerance type.
 */
template <typename T,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool lessThan(T a, T b,
              T precision = std::numeric_limits<T>::epsilon() * 4,
              ToleranceType type = ToleranceType::Combined) {
    T rtol = T(0), atol = T(0);
    switch (type) {
    case ToleranceType::Absolute:
        atol = precision;
        break;
    case ToleranceType::Relative:
        rtol = precision;
        break;
    case ToleranceType::Combined:
        atol = precision;
        rtol = precision;
        break;
    }
    return is_less(a, b, rtol, atol);
}

/**
 * @brief Less-than-or-equal comparison with precision and tolerance type.
 */
template <typename T,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
bool lessThanOrEqual(T a, T b,
                     T precision = std::numeric_limits<T>::epsilon() * 4,
                     ToleranceType type = ToleranceType::Combined) {
    T rtol = T(0), atol = T(0);
    switch (type) {
    case ToleranceType::Absolute:
        atol = precision;
        break;
    case ToleranceType::Relative:
        rtol = precision;
        break;
    case ToleranceType::Combined:
        atol = precision;
        rtol = precision;
        break;
    }
    return is_less_equal(a, b, rtol, atol);
}

} // namespace fpcomp

#endif // FPCOMP_HPP
