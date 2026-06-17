#pragma once
#include <nlohmann/json.hpp>
#include <vector>

namespace WeatherUI{
    void print_weather(const nlohmann::json& response);

    void display_option(const std::vector<nlohmann::json>& option);
}
