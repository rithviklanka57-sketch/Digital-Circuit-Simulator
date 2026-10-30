// ===== PERSON 1 =====
// Wire.h - a single signal (0/1) that connects components.
#pragma once
#include <string>
#include <utility>

class Wire {
public:
    explicit Wire(std::string name = "", bool initial = false)
        : name_(std::move(name)), value_(initial) {}

    Wire(const Wire&) = delete;
    Wire& operator=(const Wire&) = delete;

    bool get() const { return value_; }
    void set(bool v) { value_ = v; }
    const std::string& name() const { return name_; }

private:
    std::string name_;
    bool value_;
};
