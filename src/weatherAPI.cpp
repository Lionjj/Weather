#include "weatherAPI.hpp"
#include "weatherUI.hpp"
#include "config.hpp"
#include <nlohmann/json.hpp>
#include <vector>
#include <curl/curl.h>
#include <iostream>
#include <limits>

using namespace std;
using json = nlohmann::json;

namespace {
    size_t write_call_back(void* contents, size_t size, size_t nmemb, std::string* userp)
    {
        size_t total_size = size * nmemb;
        userp->append((char*)contents, total_size);
        return total_size;
    }

    void clear_bash()
    {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
}

namespace WeatherAPI{
    
    json call_api_weather(double lat, double lon) 
    {
        json JSONResult = json::object();

        CURL *curl = curl_easy_init();
        
        if(!curl) return JSONResult;

        CURLcode result;
        string response;
        
        string url = string(Config::WEATHER_PREFIX_URL)
                    + "lat=" + to_string(lat)
                    + "&lon=" + to_string(lon) 
                    + Config::WEATHER_SUFFIX_URL
                    + "&appid=" +  Config::API_KEY;
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_call_back);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        result = curl_easy_perform(curl);

        if(result != CURLE_OK)
        {
            printf("error: %s\n", curl_easy_strerror(result));
            curl_easy_cleanup(curl);
            return JSONResult;
        }

        JSONResult = json::parse(response);

        curl_easy_cleanup(curl);
        return JSONResult;
    }

    vector<json> create_city_option(const string& input)
    {
        vector<json> city_result;
        if(input.length() < 2) return city_result;

        CURL *curl = curl_easy_init();
        if(!curl) return city_result;

        char* escaped_input = curl_easy_escape(curl, input.c_str(), input.length());
        string safe_input(escaped_input);

        CURLcode result;
        string response;

        string url = string(Config::GEO_PREFIX_URL)
                    + safe_input
                    + "&limit=" + to_string(Config::GEO_LIMIT)
                    + "&appid=" + Config::API_KEY;
        

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_call_back);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3L);

        result = curl_easy_perform(curl);

        if(result != CURLE_OK)
        {
            printf("error: %s\n", curl_easy_strerror(result));
            curl_easy_cleanup(curl);
            return city_result;
        }

        try
        {
            json JSONRespons = json::parse(response);
            if(JSONRespons.is_array())
            {
                for(const auto& item : JSONRespons) city_result.push_back(item);
            }
        }
        catch(const exception& e)
        {
            cerr << e.what() << '\n';
        }

        curl_easy_cleanup(curl);
        return city_result;
    }

    json select_city_option(const vector<json> option)
    {
        if(option.empty())
        {
            cerr << "[Error]: Sothing went wrong, no option find!" << endl;
            return json::object();
        }

        int selected;

        cout << "Select option (Digit \'-1\' to insert a new city):" << endl;
        WeatherUI::display_option(option);

        cin >> selected;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(selected == -1) return json::object();

        int idx = selected - 1;

        if(idx >= option.size())
        {   
            cout << "Value not in range!" << endl;
            return json::object();
        }
        cout << idx << endl;
        return option.at(idx);
    }

    nlohmann::json search_city() 
    {
        std::vector<nlohmann::json> current_options;
        nlohmann::json json_result;

        while (json_result.empty()) {

            std::string current_input;

            clear_bash();
            std::cout << "Digit a city or it's initial:" << std::endl;
            std::getline(std::cin, current_input);

            if(current_input.length() < 2)
            {
                std::cerr << "String to short to search, put a new value!" << std::endl;
                continue;
            }

            current_options = WeatherAPI::create_city_option(current_input); 
            json_result = WeatherAPI::select_city_option(current_options);
            
        }
        
        clear_bash();
        return json_result;
    }
}