#pragma once
#include <string>


namespace Config
{
    inline constexpr const char* API_KEY = "0ef9ddfc862960e794be95bdc093587b";
    inline constexpr const char* WEATHER_PREFIX_URL = "https://api.openweathermap.org/data/2.5/weather?";
    inline constexpr const char* WEATHER_SUFFIX_URL = "&units=metric&lang=it";

    inline constexpr const char* GEO_PREFIX_URL = "http://api.openweathermap.org/geo/1.0/direct?q=";
    inline constexpr int GEO_LIMIT = 5;
} // namespace cofig
