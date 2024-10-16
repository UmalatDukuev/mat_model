#include <iostream>
#include <vector>
#include <dlfcn.h> // Для Linux
#include <fstream>
#include <functional>

typedef std::vector<std::vector<double>> (*NumericalMethod)(
    std::vector<double> (*f)(double, const std::vector<double> &),
    const std::vector<double> &, double, double, double);

std::vector<double> f(double t, const std::vector<double> &y)
{
    double k1 = 0.577;
    double k2 = 0.422;
    return {-k1 * y[0], k1 * y[0] - k2 * y[1], k2 * y[1]};
}

int main()
{
    std::string method;
    std::cout << "Enter method (rk4/adams_bashforth): ";
    std::cin >> method;

    void *handle;
    if (method == "rk4")
    {
        handle = dlopen("librk4.so", RTLD_LAZY);
    }
    else if (method == "adams_bashforth")
    {
        handle = dlopen("libadams_bashforth.so", RTLD_LAZY);
    }
    else
    {
        std::cerr << "Unknown method!" << std::endl;
        return -1;
    }

    if (!handle)
    {
        std::cerr << "Error loading library: " << dlerror() << std::endl;
        return -1;
    }

    srand(time(0));
    double k1 = 0.577;
    double k2 = 0.422 + (static_cast<double>(rand()) / RAND_MAX) * (1.0 - 0.422);

    NumericalMethod numerical_method = (NumericalMethod)dlsym(handle, "solve");
    if (!numerical_method)
    {
        std::cerr << "Error loading method!" << std::endl;
        dlclose(handle);
        return -1;
    }

    std::vector<double> y0 = {1.0, 0.0, 0.0};
    double t0 = 0.0;
    double t_end = 10.0;
    double step = 0.1;

    std::vector<std::vector<double>> solution = numerical_method(f, y0, t0, t_end, step);

    std::ofstream output_file("solution.csv");
    double t = t0;
    for (const auto &y : solution)
    {
        output_file << t << "," << y[0] << "," << y[1] << "," << y[2] << "\n";
        t += step;
    }
    output_file.close();

    dlclose(handle);
    return 0;
}
