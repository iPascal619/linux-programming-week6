#include <assert.h>
#include "weather_analysis.h"

void test_weather_analysis() {
    WeatherData data;
    int loaded = load_weather_data(&data, "data/weather_data.csv");
    assert(loaded > 0);

    WeatherAnalysis analysis = analyze_weather_data(&data);
    
    // Add appropriate assertions based on expected results
    assert(analysis.mode > 0);
    assert(analysis.median > 0);
    assert(analysis.standard_deviation >= 0);
}

int main() {
    test_weather_analysis();
    printf("Weather analysis tests passed!\n");
    return 0;
}