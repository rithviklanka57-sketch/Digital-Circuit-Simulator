// ===== PERSON 3 =====
// Output.h - reads a SimulationResult and presents it.
//   Output     : pretty table on the console
//   CSVOutput  : subclass that dumps the readings to a CSV file (open in Excel)
#pragma once
#include "SimulationResult.h"
#include <iostream>
#include <string>

class Output {
public:
    explicit Output(std::ostream& os = std::cout) : os_(os) {}
    virtual ~Output() = default;
    virtual void write(const SimulationResult& result);   // console table
protected:
    std::ostream& os_;
};

class CSVOutput : public Output {
public:
    explicit CSVOutput(std::string path) : path_(std::move(path)) {}
    void write(const SimulationResult& result) override;  // writes the file
    const std::string& path() const { return path_; }
private:
    std::string path_;
};
