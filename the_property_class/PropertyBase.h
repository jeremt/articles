#pragma once

#include <typeinfo>

class PropertyBase {
public:
    virtual ~PropertyBase() = default;

public:
    virtual auto type_info() const -> std::type_info const & = 0;

protected:
    PropertyBase() = default;
    PropertyBase(PropertyBase const &) = default;

protected:
    auto operator=(PropertyBase const &other) -> PropertyBase & = default;
};