#ifndef WEATHER_ANALYSIS_H
#define WEATHER_ANALYSIS_H

#define MAX_TEMPERATURES 1000

typedef struct {
    double temperatures[MAX_TEMPERATURES];
    int count;
} WeatherData;

typedef struct {
    double mode;
    double median;
    double standard_deviation;
} WeatherAnalysis;

int load_weather_data(WeatherData* data, const char* filename);
WeatherAnalysis analyze_weather_data(const WeatherData* data);
int write_weather_analysis(const WeatherAnalysis* analysis, const char* output_filename);

#endif