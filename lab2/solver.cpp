#include "solver.h"
#include <cmath>

SimulationResult eulerMethod(std::function<double(double, double)> func, double T0, double T1, double gamma, double t_start, double t_end, double dt)
{
    SimulationResult result;
    double t = t_start;
    double T = T0;

    while (t <= t_end)
    {
        result.time.push_back(t);
        result.temperature.push_back(T);
        T += dt * func(t, T);
        t += dt;
    }
    return result;
}

SimulationResult heunMethod(std::function<double(double, double)> func, double T0, double T1, double gamma, double t_start, double t_end, double dt)
{
    SimulationResult result;
    double t = t_start;
    double T = T0;

    while (t <= t_end)
    {
        result.time.push_back(t);
        result.temperature.push_back(T);
        double k1 = func(t, T);
        double k2 = func(t + dt, T + dt * k1);
        T += dt * 0.5 * (k1 + k2);
        t += dt;
    }
    return result;
}
