#include <iostream>
#include "solver.h"
#include "utils.h"

double heatTransferEquation(double T, double T1, double gamma)
{
    return -gamma * (T - T1);
}

int main()
{
    double T0 = 0.0;
    double T1 = 20.0;
    double gamma = 0.5;
    double t_start = 0.0, t_end = 20.0, dt = 1.0;

    auto eulerResult = eulerMethod(
        [&](double t, double T)
        { return heatTransferEquation(T, T1, gamma); },
        T0, T1, gamma, t_start, t_end, dt);

    auto heunResult = heunMethod(
        [&](double t, double T)
        { return heatTransferEquation(T, T1, gamma); },
        T0, T1, gamma, t_start, t_end, dt);

    saveToCSV("euler_results.csv", eulerResult.time, eulerResult.temperature);
    saveToCSV("heun_results.csv", heunResult.time, heunResult.temperature);

    std::cout << "Simulation completed. Results saved to CSV files.\n";
    return 0;
}
