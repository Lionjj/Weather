#include <iostream>
#include <string>
#include <curl/curl.h>

static const std::string API_KEY = "0ef9ddfc862960e794be95bdc093587b";
static const std::string PREFIX_URL = "https://api.openweathermap.org/data/2.5/weather?q=";
static const std::string SUFFIX_URL = "&appid=" + API_KEY + "&units=metric&lang=it";

bool call_api_meteo(std::string city) 
{
    if(city.empty())
    {
        std::cerr << "No city specified!" << std::endl;
        return false;
    }

    CURL *curl = curl_easy_init();
    
    if(!curl) return false;

    CURLcode result;
    
    std::string url = PREFIX_URL + city + SUFFIX_URL;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    result = curl_easy_perform(curl);

    if(result != CURLE_OK)
    {
        printf("error: %s\n", curl_easy_strerror(result));
        curl_easy_cleanup(curl);
        return false;
    }

    std::cout << result << std::endl;
    curl_easy_cleanup(curl);
    return true;
}

int main()
{
    // 1. Dipslay the possibility of the input of the user
    // 2. Get the input from the user
    // 3. Call the API based on the current request
    if (call_api_meteo("Milano")) std::cout << "ok" << std::endl;
    return 0;
    // 4. Display the result.
}