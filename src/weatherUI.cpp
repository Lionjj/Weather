#include "weatherUI.hpp"
#include <iostream>
#include <string>

using json = nlohmann::json;
using namespace std;

namespace WeatherUI{

    void print_weather(const json& response)
    {
        if(response.empty())
        {
        cerr << "Response is empty!" << endl;
        return;  
        } 

        if(response.contains("cod") && response["cod"] >= 400)
        {
            cerr << "error: respons code: " << response["cod"] << '.' << endl; 
            return;
        }

        float temp = response["main"]["temp"];
        float feels_like = response["main"]["feels_like"];
        int humidity = response["main"]["humidity"];

        string description = response["weather"][0]["description"];
        
        string city = response["name"];
        string country = response["sys"]["country"];

        cout << "\n ======================================================" << endl;
        cout << '\t' + city + '(' + country + ')' + " weather forecast: " + description << endl;
        cout << "\n ======================================================" << endl;
        cout << "\tTemperature: " << temp << "°C (Feels like: " << feels_like << " °C)" << endl;
        cout << "\tHumidity: " << humidity << endl;
        cout << "\n ======================================================" << endl;

    }

    void display_option(const vector<json>& option)
    {
        for (size_t i = 0; i < option.size(); ++i) 
        {
            string nazione = option[i]["country"];
            string nome = option[i]["name"];
            string regione = option[i].contains("state") ? option[i]["state"].get<string>() : "";
            cout << "  [" << i + 1 << "] " << nome << " (" << regione << ", " << nazione << ")\n";
        }
    }
}