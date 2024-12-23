#ifndef ALP_DOUBLE_COLUMNS_HPP
#define ALP_DOUBLE_COLUMNS_HPP

#include "column.hpp"

namespace alp_bench {

inline std::array<Column, 31> alp_dataset = {{

    {1, "Air-Pressure", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "neon_air_pressure.bin", 14, 9, 3, 16},
    {2, "Arade/4", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "arade4.bin", 14, 10, 8, 24},
    {3, "Basel-Temp", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "basel_temp_f.bin", 14, 7, 47, 28},
    {4, "Basel-Wind", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "basel_wind_f.bin", 14, 7, 9, 29},
    {5, "Bird-Mig", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "bird_migration_f.bin", 14, 9, 2, 17},
    {6, "Btc-Price", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "bitcoin_f.bin", 14, 10, 10, 25},
    {7, "Blockchain", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "bitcoin_transactions_f.bin", 14, 10, 11, 30},
    {8, "City-Temp", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "city_temperature_f.bin", 14, 13, 0, 11},
    {9, "CMS/1", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "cms1.bin", 14, 5, 10, 41},
    {10, "CMS/9", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "cms9.bin", 16, 16, 2, 10},
    {11, "CMS/25", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "cms25.bin", 14, 4, 6, 42},
    {12, "Dew-Temp", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "neon_dew_point_temp.bin", 14, 11, 6, 13},
    {13, "Bio-Temp", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "neon_bio_temp_c.bin", 14, 12, 0, 10},
    {14, "Food-prices", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "food_prices.bin", 16, 12, 46, 20},
    {15, "Gov/10", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "gov10.bin", 3, 1, 72, 27},
    {16, "Gov/26", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "gov26.bin", 18, 18, 0, 0},
    {17, "Gov/30", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "gov30.bin", 18, 18, 4, 0},
    {18, "Gov/31", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "gov31.bin", 18, 18, 1, 0},
    {19, "Gov/40", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "gov40.bin", 18, 18, 3, 0},
    {20, "Medicare/1", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "medicare1.bin", 14, 5, 37, 38},
    {21, "Medicare/9", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "medicare9.bin", 16, 16, 3, 10},
    {22, "PM10-dust", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "neon_pm10_dust.bin", 14, 11, 0, 8},
    {23, "NYC/29", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "nyc29.bin", 14, 1, 5, 42},
    {24, "POI-lat", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "poi_lat.bin", 16, 0, 157, 55, true},
    {25, "POI-lon", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "poi_lon.bin", 16, 0, 199, 56, true},
    {26, "SD-bench", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "ssd_hdd_benchmarks_f.bin", 14, 13, 0, 17},
    {27, "Stocks-DE", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "stocks_de.bin", 14, 11, 5, 10},
    {28, "Stocks-UK", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "stocks_uk.bin", 14, 13, 0, 9},
    {29, "Stocks-USA", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "stocks_usa_c.bin", 14, 12, 0, 7},
    {30, "Wind-dir", "", PATHS.ALP_DATASET_BINARY_DIR_PATH + "neon_wind_dir.bin", 14, 12, 0, 16},
    {31, "issue_8", PATHS.ALP_ISSUE_CSV_PATH + "active_power.csv", "", 0, 0, 0, 0, true},

}};
} // namespace alp_bench
#endif