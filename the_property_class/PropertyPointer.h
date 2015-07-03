#pragma once

#include <memory>
#include <utility>
#include <typeinfo>
#include <type_traits>
#include <stdexcept>
#include "PropertyBase.h"

class PropertyPointer final {
public:
    PropertyPointer() = default;
    PropertyPointer(std::shared_ptr<PropertyBase> const &value) :
            _value(value) {

    }
    PropertyPointer(PropertyPointer const &) = default;
    ~PropertyPointer() = default;

public:
    auto operator=(PropertyPointer const &other) -> PropertyPointer & = default;
    operator bool() { return !!_value; }

public:
    auto type_info() const -> std::type_info const & { return _value->type_info(); };

public:
    template <typename TProperty> auto ptr() const -> TProperty *;
    template <typename TProperty> auto value() const -> decltype(std::declval<TProperty>().value());
    template <typename TProperty, typename TValue> auto value(TValue &&value) -> void;

private:
    std::shared_ptr<PropertyBase> _value;
};

template <typename TProperty>
auto PropertyPointer::ptr() const -> TProperty * {
    if (typeid(TProperty).hash_code() != _value->type_info().hash_code()) {
        throw std::bad_typeid();
    }
    return std::dynamic_pointer_cast<TProperty>(_value).get();
}

template <typename TProperty>
auto PropertyPointer::value() const -> decltype(std::declval<TProperty>().value()) {
    return ptr<TProperty>()->value();
}

template <typename TProperty, typename TValue>
auto PropertyPointer::value(TValue &&value) -> void {
    ptr<TProperty>()->value(std::forward(value));
}

template <typename TProperty, typename ...TArgs>
auto make_property(TArgs && ...args) -> PropertyPointer {
    return PropertyPointer(std::make_shared<TProperty>(std::forward<TArgs>(args)...));
}
