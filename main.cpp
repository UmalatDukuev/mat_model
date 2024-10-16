#include <iostream>
#include <vector>
#include <dlfcn.h> // Для Linux
#include <fstream>
#include <functional>

typedef std::vector<std::vector<double>> (*NumericalMethod)(std::vector<double> (*f)(double, const std::vector<double> &),
                                                            const std::vector<double> &, double, double, double);

std::vector<double> f(double t, const std::vector<double> &y)
{
    double k1 = 0.577;
    double k2 = 0.422;
    return {-k1 * y[0], k1 * y[0] - k2 * y[1], k2 * y[1]};
}

void save_solution(const std::string &method, double t0, double step, const std::vector<std::vector<double>> &solution_rk4,
                   const std::vector<std::vector<double>> &solution_ab, std::ofstream &output_file)
{
    double t = t0;
    for (size_t i = 0; i < solution_rk4.size(); ++i)
    {
        const auto &y_rk4 = solution_rk4[i];
        const auto &y_ab = solution_ab[i];
        output_file << t << "," << y_rk4[0] << "," << y_rk4[1] << "," << y_rk4[2] << ","
                    << y_ab[0] << "," << y_ab[1] << "," << y_ab[2] << "\n";
        t += step;
    }
}

int main()
{
    void *handle_rk4 = dlopen("librk4.so", RTLD_LAZY);
    void *handle_ab = dlopen("libadams_bashforth.so", RTLD_LAZY);

    if (!handle_rk4 || !handle_ab)
    {
        std::cerr << "Error loading libraries!" << std::endl;
        if (handle_rk4)
            dlclose(handle_rk4);
        if (handle_ab)
            dlclose(handle_ab);
        return -1;
    }

    NumericalMethod rk4_method = (NumericalMethod)dlsym(handle_rk4, "solve");
    NumericalMethod ab_method = (NumericalMethod)dlsym(handle_ab, "solve");

    if (!rk4_method || !ab_method)
    {
        std::cerr << "Error loading methods!" << std::endl;
        dlclose(handle_rk4);
        dlclose(handle_ab);
        return -1;
    }

    std::vector<double> y0 = {1.0, 0.0, 0.0};
    double t0 = 0.0;
    double t_end = 10.0;
    double step = 0.1;

    std::vector<std::vector<double>> solution_rk4 = rk4_method(f, y0, t0, t_end, step);
    std::vector<std::vector<double>> solution_ab = ab_method(f, y0, t0, t_end, step);

    std::ofstream output_file("solution.csv");
    save_solution("both", t0, step, solution_rk4, solution_ab, output_file);
    output_file.close();

    dlclose(handle_rk4);
    dlclose(handle_ab);

    return 0;
}