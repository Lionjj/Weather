#pragma once

#include "config.hpp"
#include <nlohmann/json.hpp>
#include <vector>


namespace WeatherAPI
{
    nlohmann::json call_api_weather(const double lat, const double lon);

    std::vector<nlohmann::json> create_city_option(const std::string& input);

    nlohmann::json select_city_option(const std::vector<nlohmann::json> option);

    nlohmann::json search_city();
} // namespace WeatherAPI
