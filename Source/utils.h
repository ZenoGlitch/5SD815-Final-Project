#pragma once

// narrow_cast(): a searchable way to do narrowing casts of values
template <class T, class U>


// clang-format on
constexpr T narrow_cast(U&& u) noexcept
{
    return static_cast<T>(std::forward<U>(u));
}