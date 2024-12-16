#include "utils.h"
#include <fstream>

void saveToCSV(const std::string &filename, const std::vector<double> &time, const std::vector<double> &temperature)
{
    std::ofstream file(filename);
    file << "Time,Temperature\n";
    for (size_t i = 0; i < time.size(); ++i)
    {
        file << time[i] << "," << temperature[i] << "\n";
    }
    file.close();
}
