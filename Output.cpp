// ===== PERSON 3 =====
#include "Output.h"
#include <fstream>
#include <iomanip>
#include <stdexcept>

void Output::write(const SimulationResult& r) {
    const auto& cols = r.columns();
    os_ << std::setw(6) << "time";
    for (const auto& c : cols) os_ << ' ' << std::setw(std::max<std::size_t>(5, c.size())) << c;
    os_ << '\n';
    for (const auto& row : r.rows()) {
        os_ << std::setw(6) << row.time;
        for (std::size_t i = 0; i < row.values.size(); ++i)
            os_ << ' ' << std::setw(std::max<std::size_t>(5, cols[i].size())) << row.values[i];
        os_ << '\n';
    }
}

void CSVOutput::write(const SimulationResult& r) {
    std::ofstream f(path_);
    if (!f) throw std::runtime_error("cannot open " + path_ + " for writing");
    f << "time";
    for (const auto& c : r.columns()) f << ',' << c;
    f << '\n';
    for (const auto& row : r.rows()) {
        f << row.time;
        for (long v : row.values) f << ',' << v;
        f << '\n';
    }
}
