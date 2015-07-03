#pragma once

#include "PropertyBase.h"

class CounterProperty final : public PropertyBase {
public:
    CounterProperty() = delete;
    CounterProperty(int start) :
        _count(start) {

    }

    CounterProperty(CounterProperty const &other) = default;
    CounterProperty(CounterProperty &&other) = default;
    ~CounterProperty() = default;

public:
    auto operator=(CounterProperty const &other) -> CounterProperty & = default;
    auto operator=(CounterProperty &&other) -> CounterProperty & = default;

public:
    virtual auto type_info() const -> std::type_info const & override final { return typeid(CounterProperty); }

public:
    auto value() -> int { return _count--; }

private:
    int _count;
};