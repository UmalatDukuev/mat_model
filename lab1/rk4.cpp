#include <vector>

std::vector<double> operator+(const std::vector<double> &vec1, const std::vector<double> &vec2)
{
    std::vector<double> result(vec1.size());
    for (std::size_t i = 0; i < vec1.size(); ++i)
    {
        result[i] = vec1[i] + vec2[i];
    }
    return result;
}

std::vector<double> operator*(double scalar, const std::vector<double> &vec)
{
    std::vector<double> result(vec.size());
    for (std::size_t i = 0; i < vec.size(); ++i)
    {
        result[i] = scalar * vec[i];
    }
    return result;
}

extern "C"
{
    std::vector<std::vector<double>> solve(
        std::vector<double> (*f)(double, const std::vector<double> &),
        const std::vector<double> &y0, double t0, double t_end, double step)
    {

        std::vector<std::vector<double>> result;
        std::vector<double> y = y0;
        double t = t0;

        while (t <= t_end)
        {
            result.push_back(y);
            std::vector<double> k1 = f(t, y);
            std::vector<double> k2 = f(t + step / 2, y + step / 2 * k1);
            std::vector<double> k3 = f(t + step / 2, y + step / 2 * k2);
            std::vector<double> k4 = f(t + step, y + step * k3);

            for (std::size_t i = 0; i < y.size(); ++i)
            {
                y[i] = y[i] + (step / 6) * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]);
            }
            t += step;
        }

        return result;
    }
}
