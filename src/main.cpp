#include "weatherAPI.hpp"
#include "weatherUI.hpp"
#include <iostream>
#include <string>


bool user_want_to_procede()
{
    char ch;
    
    std::cout << "Do you want to search the weather for a new city? [y\\n]: " << std::endl;
    std::cin >> ch;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return ch == 'y' ? true : false;
}

int main() {

    do
    {
        nlohmann::json respone = WeatherAPI::search_city();
        if(respone.empty()) continue;

        double lat = respone["lat"];
        double lon = respone["lon"];

        nlohmann::json weather_data = WeatherAPI::call_api_weather(lat, lon);
        WeatherUI::print_weather(weather_data);
    } 
    while(user_want_to_procede());
    
    return 0;
}