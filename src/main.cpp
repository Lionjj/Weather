#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using string = std::string;

static const string API_KEY = "0ef9ddfc862960e794be95bdc093587b";
static const string PREFIX_URL = "https://api.openweathermap.org/data/2.5/weather?q=";
static const string SUFFIX_URL = "&appid=" + API_KEY + "&units=metric&lang=it";

size_t write_call_back(void* contents, size_t size, size_t nmemb, std::string* userp)
{
    size_t total_size = size * nmemb;
    userp->append((char*)contents, total_size);
    return total_size;
}

void pritn_weather(const json& response)
{
    if(response.empty())
    {
      std::cerr << "Response is empty!" << std::endl;
      return;  
    } 

    if(response.contains("cod") && response["cod"] >= 400)
    {
        std::cerr << "error: respons code: " << response["cod"] << '.' << std::endl; 
    }

    float temp = response["main"]["temp"];
    float feels_like = response["main"]["feels_like"];
    int humidity = response["main"]["humidity"];

    string description = response["weather"][0]["description"];
    
    string city = response["name"];
    string country = response["sys"]["country"];

    std::cout << "\n ======================================================" << std::endl;
    std::cout << '\t' + city + '(' + country + ')' + " weather forecast: " + description << std::endl;
    std::cout << "\n ======================================================" << std::endl;
    std::cout << "\tTemperature: " << temp << "°C (Feels like: " << feels_like << " °C)" << std::endl;
    std::cout << "\tHumidity: " << humidity << std::endl;
    std::cout << "\n ======================================================" << std::endl;

}

json call_api_weather(string city) 
{
    json JSONResult = json::object();

    if(city.empty())
    {
        std::cerr << "No city specified!" << std::endl;
        return JSONResult;
    }

    CURL *curl = curl_easy_init();
    
    if(!curl) return JSONResult;

    CURLcode result;
    string response;
    
    string url = PREFIX_URL + city + SUFFIX_URL;
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

int main()
{
    // 1. Dipslay the possibility of the input of the user
    // 2. Get the input from the user
    // 3. Call the API based on the current request
    json server_response = call_api_weather("Milano");
    pritn_weather(server_response);
    // 4. Display the result.
    return 0;
}