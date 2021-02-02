// Generate statistics for PSP planning.
#include "statistics.hpp"

#include <cctype>
#include <fstream>
#include <iostream>
#include <optional>
#include <vector>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

std::optional<std::vector<statistics::Point>> get_points_from_file(std::string filename)
{
    std::vector<statistics::Point> points;
    std::ifstream ifs(filename);
    while (ifs.good())
    {
        statistics::Point p;
        ifs >> p.x;
        while (ifs.peek() == ',' || ifs.peek() == ' ')
        {
            ifs.ignore();
        }
        ifs >> p.y;
        while (ifs.peek() == ',' || std::isspace(ifs.peek()))
        {
            ifs.ignore();
        }
        points.push_back(std::move(p));
    }
    if (ifs.eof())
    {
        return points;
    }
    return {};
}

// Calculate and display PSP stats.
void calculate_and_display_stats(std::vector<statistics::Point> points, std::optional<double> x_estimate)
{
    const double correl = statistics::correlation(points);
    const double sig = statistics::significance(points);
    const auto si = statistics::linear_regression(points);

    std::cout << "PSP Stats\n"
              << "---------\n"
              << "correlation coefficient (> 0.7 is good): " << correl << "\n"
              << "significance (< 0.05 is good): " << sig << "\n"
              << "linear regression, slope: " << si.slope << ", y-intercept: " << si.y_intercept << "\n";

    if (x_estimate)
    {
        const auto y_estimate = statistics::get_projection(si, *x_estimate);
        const auto range = statistics::prediction_range(points, *x_estimate, 70.0);

        std::cout << "y(" << *x_estimate << "): " << y_estimate << "\n"
                  << "range: " << range << "\n"
                  << "UPI (70%): " << y_estimate + range << "\n"
                  << "LPI (70%): " << y_estimate - range << "\n";
    }
}

const char *help = R"help(
    Show PSP (Personal Software Process, Humphrey) stats for planning a
    project, based on historical data.

    Usage:
        ./psp_stats [OPTIONS] data_filename

    Options:

        -h, --help
            help string

        -x, --x-estimate
            floating point value of x estimate for calculating a y-value
            prediction, with prediction range values.

        data_filename
            csv file with 2 columns of x,y double floating point data values.
)help";

int main(int argc, char *argv[])
{
    std::optional<double> x_estimate;
    std::string filename;
    try
    {
        po::options_description desc("Options");
        desc.add_options()("help,h", "produce help message")("x-estimate,x", po::value<double>(), "x estimate for calculating y-value prediction")("input-file", po::value<std::string>(), "input file");

        po::positional_options_description p;
        p.add("input-file", -1);

        po::variables_map vm;

        po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
        po::notify(vm);

        if (vm.count("help"))
        {
            std::cout << help << '\n';
            return 0;
        }
        if (vm.count("x-estimate"))
        {
            x_estimate = vm["x-estimate"].as<double>();
        }
        if (vm.count("input-file"))
        {
            filename = vm["input-file"].as<std::string>();
        }
    }
    catch (const po::error &ex)
    {
        std::cerr << ex.what() << '\n';
        return 1;
    }

    const auto points = get_points_from_file(filename);
    if (!points)
    {
        std::cerr << "Couldn't get points from file " << filename << "\n";
        return 1;
    }

    if (points->size() < 3)
    {
        std::cerr << "Must provide at least 3 data points, found " << points->size() << "\n";
        return 1;
    }

    calculate_and_display_stats(*points, x_estimate);

    return 0;
}
