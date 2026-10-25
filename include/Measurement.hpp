#ifndef MEASUREMENT_HPP
#define MEASUREMENT_HPP
#include <sstream>
#include <iomanip>
#include <variant>
#include <string>
#include <type_traits>

using Measurement = std::variant<float, int, bool>;

inline std::string measurementToString(const Measurement &value)
{
    return std::visit([](const auto &measuredValue) -> std::string
                      {
        using T = std::decay_t<decltype(measuredValue)>;

        if constexpr (std::is_same_v<T, bool>)
        {
            return measuredValue ? "1" : "0";
        }
        else if constexpr (std::is_floating_point_v<T>)
        {
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(2) << measuredValue;
            return oss.str();
        }
        else
        {
            return std::to_string(measuredValue);
        } }, value);
}

#endif
