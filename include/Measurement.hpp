#ifndef MEASUREMENT_HPP
#define MEASUREMENT_HPP
#include <sstream>
#include <iomanip>
#include <variant>
#include <string>
#include <type_traits>

// Une mesure peut être flottante (température/humidité), entière (son)
// ou booléenne (lumière).
using Measurement = std::variant<float, int, bool>;

// Convertit une mesure vers le format texte utilisé dans la console et les CSV.
inline std::string measurementToString(const Measurement &value)
{
    return std::visit([](const auto &measuredValue) -> std::string
                      {
        using T = std::decay_t<decltype(measuredValue)>;

        // Les booléens sont écrits sous la forme 0/1 pour les journaux CSV.
        if constexpr (std::is_same_v<T, bool>)
        {
            return measuredValue ? "1" : "0";
        }
        // Les flottants sont uniformisés avec deux chiffres après la virgule.
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
