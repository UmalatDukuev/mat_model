#include <vector>

extern "C"
{
    std::vector<std::vector<double>> adams_bashforth_2nd(
        std::vector<double> (*f)(double, const std::vector<double> &),
        const std::vector<double> &y0, double t0, double t_end, double step)
    {
        std::vector<std::vector<double>> result;
        std::vector<double> y_prev = y0;
        std::vector<double> y = y0;
        double t = t0;
        result.push_back(y);
        std::vector<double> f_prev = f(t, y);
        for (std::size_t i = 0; i < y.size(); ++i)
        {
            y[i] = y[i] + step * f_prev[i];
        }
        t += step;

        while (t <= t_end)
        {
            result.push_back(y);
            std::vector<double> f_curr = f(t, y);
            for (std::size_t i = 0; i < y.size(); ++i)
            {
                y[i] = y[i] + step / 2 * (3 * f_curr[i] - f_prev[i]);
            }
            f_prev = f_curr;
            t += step;
        }

        return result;
    }

    std::vector<std::vector<double>> solve(
        std::vector<double> (*f)(double, const std::vector<double> &),
        const std::vector<double> &y0, double t0, double t_end, double step)
    {
        return adams_bashforth_2nd(f, y0, t0, t_end, step);
    }
}
