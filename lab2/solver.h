#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <functional>

struct SimulationResult
{
    std::vector<double> time;
    std::vector<double> temperature;
};

SimulationResult eulerMethod(std::function<double(double, double)> func, double T0, double T1, double gamma, double t_start, double t_end, double dt);

SimulationResult heunMethod(std::function<double(double, double)> func, double T0, double T1, double gamma, double t_start, double t_end, double dt);

#endif
