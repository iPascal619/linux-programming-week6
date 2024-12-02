#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "weather_analysis.h"

int load_weather_data(WeatherData* data, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return -1;
    }

    data->count = 0;
    while (data->count < MAX_TEMPERATURES && 
           fscanf(file, "%lf", &data->temperatures[data->count]) == 1) {
        data->count++;
    }

    fclose(file);
    return data->count;
}

double calculate_mode(const WeatherData* data) {
    int max_count = 0;
    double mode = 0;
    
    for (int i = 0; i < data->count; i++) {
        int current_count = 1;
        for (int j = 0; j < data->count; j++) {
            if (i != j && fabs(data->temperatures[i] - data->temperatures[j]) < 0.001) {
                current_count++;
            }
        }
        if (current_count > max_count) {
            max_count = current_count;
            mode = data->temperatures[i];
        }
    }
    
    return mode;
}

double calculate_median(WeatherData* data) {
    // Sort temperatures
    for (int i = 0; i < data->count - 1; i++) {
        for (int j = 0; j < data->count - i - 1; j++) {
            if (data->temperatures[j] > data->temperatures[j+1]) {
                double temp = data->temperatures[j];
                data->temperatures[j] = data->temperatures[j+1];
                data->temperatures[j+1] = temp;
            }
        }
    }

    int mid = data->count / 2;
    return data->count % 2 == 0 ? 
        (data->temperatures[mid-1] + data->temperatures[mid]) / 2 : 
        data->temperatures[mid];
}

double calculate_standard_deviation(const WeatherData* data) {
    double mean = 0;
    for (int i = 0; i < data->count; i++) {
        mean += data->temperatures[i];
    }
    mean /= data->count;

    double variance = 0;
    for (int i = 0; i < data->count; i++) {
        variance += pow(data->temperatures[i] - mean, 2);
    }
    variance /= data->count;

    return sqrt(variance);
}

WeatherAnalysis analyze_weather_data(const WeatherData* data) {
    WeatherAnalysis analysis;
    
    // Create a copy for median calculation (which requires sorting)
    WeatherData temp_data = *data;
    
    analysis.mode = calculate_mode(data);
    analysis.median = calculate_median(&temp_data);
    analysis.standard_deviation = calculate_standard_deviation(data);

    return analysis;
}

int write_weather_analysis(const WeatherAnalysis* analysis, const char* output_filename) {
    FILE* file = fopen(output_filename, "w");
    if (!file) {
        fprintf(stderr, "Error: Cannot write to file %s\n", output_filename);
        return -1;
    }

    fprintf(file, "Weather Data Analysis:\n");
    fprintf(file, "Mode: %.2f\n", analysis->mode);
    fprintf(file, "Median: %.2f\n", analysis->median);
    fprintf(file, "Standard Deviation: %.2f\n", analysis->standard_deviation);

    fclose(file);
    return 0;
}