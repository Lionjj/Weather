# 🌦️ Weather CLI Application (C++)

Welcome to the **Weather CLI App**, a command-line utility written in **C++** that allows you to fetch real-time weather forecasts for any city worldwide using the **OpenWeatherMap** APIs.

The project is fully modular, decoupling network logic (handled via `libcurl`), data parsing (powered by the `nlohmann/json` library), and the terminal-based User Interface.

---

## 🛠️ Architecture & Logical Flow

The application robustly resolves city name ambiguity (e.g., searching for a city that exists in multiple countries) by implementing a two-factor flow: **Geocoding + Geographic Coordinates**.

1. **User Input**: The user enters a city name or its initials.
2. **Geocoding (`Config::GEO_PREFIX_URL`)**: The app queries the geocoding endpoint to fetch up to a maximum of 5 matching options (`GEO_LIMIT`).
3. **Selection Menu**: An interactive menu displays the found locations, showing their State and Country code.
4. **Weather Query (`Config::WEATHER_PREFIX_URL`)**: Once the user selects an option, the app extracts the exact `lat` (latitude) and `lon` (longitude) from the JSON object and performs the final weather API call, guaranteeing absolute precision and preventing `404` errors.

---

## ⚙️ Configuration (`config.hpp`) & API Key

This application requires an API key from OpenWeatherMap to fetch weather data. To protect sensitive credentials, the application reads the API key from your system's environment variables rather than hardcoding it into the source code.

### 1. Get your API Key
1. Go to [OpenWeatherMap](https://openweathermap.org/) and create a free account.
2. Navigate to your dashboard and generate a new **API Key** (under the "My API Keys" tab).

### 2. Set the Environment Variable
Before running the application, you must set the environment variable named `API_KEY`.

```cpp
#pragma once
#include <string>

namespace Config
{
    inline constexpr const char* API_KEY = "";
    inline constexpr const char* WEATHER_PREFIX_URL = "[https://api.openweathermap.org/data/2.5/weather](https://api.openweathermap.org/data/2.5/weather)?";
    inline constexpr const char* WEATHER_SUFFIX_URL = "&units=metric&lang=it";

    inline constexpr const char* GEO_PREFIX_URL = "[http://api.openweathermap.org/geo/1.0/direct?q=](http://api.openweathermap.org/geo/1.0/direct?q=)";
    inline constexpr int GEO_LIMIT = 5;
} // namespace Config
```

---

## 🚀 Requirements & Dependencies

To compile and run this project, your environment must have a modern C++ compiler supporting C++20 or higher, along with the following development libraries:

### libcurl

The client-side URL transfer library used to handle HTTP GET requests safely.

#### Ubuntu/Debian:

```bash
sudo apt-get update
sudo apt-get install libcurl4-openssl-dev
```

#### macOS(via Homebrew):

```bash
brew install curl
```

#### Windows:

It is recommended to use vcpkg (vcpkg install curl) or manually download and link the static/dynamic curl binaries.

### nlohmann/json

An intuitive, header-only JSON library for C++. Ensure that nlohmann/json.hpp is properly path-mapped or placed in your project's include folder.

#### Ubuntu/Debian:

```bash
sudo apt-get update
sudo apt-get install nlohmann-json3-dev
```

#### macOS(via Homebrew):

```bash
brew install nlohmann-json
```

---

## 🏗️ Compilation from Terminal

The project configuration targets C++20 and strictly manages dependencies via CMakeLists.txt. It includes specific paths to search within Homebrew directories if running on Apple macOS.
To build the executable, run the following commands from the root folder of the project

```bash
# 1. Create and enter the build directory
mkdir build && cd build

# 2. Configure the project using CMake
cmake ..

# 3. Compile the executable
cmake --build .
```

To execute the compiled application binary:

```bash
./Weather
```

---

## 🐛 Core Bug Fixes & Stability

In recent refactoring sessions (git log --oneline), two critical stability issues were successfully resolved:

1. Geographic Mismatch (Fixed): Replaced the old string-based weather API request with a coordinate-based system (lat/lon). This prevents OpenWeatherMap from returning incorrect namesake cities (e.g., New in Liberia instead of New in Kentucky).
2. Polluted Input Buffer (\n) (Fixed): Resolved unpredictable UI behaviors caused by trailing newline characters left in the input stream. Integrating cin.ignore(numeric_limits<streamsize>::max(), '\n') directly after numeric reads now ensures total stability for subsequent std::getline prompts.

More bug can be found during the usage, if this occurse let me know!
