#pragma once

#include <functional>
#include <stdexcept>
#include <typeinfo>

namespace detail {

    template <typename TFunction>
    struct FunctionHelper : public FunctionHelper<decltype(&TFunction::operator())> {

    };

    template <typename TClass, typename TReturn, typename ...TArgs>
    struct FunctionHelper<TReturn(TClass::*)(TArgs...) const> {
        using Type = std::function<TReturn(TArgs...)>;
    };

    template <typename TFunction>
    auto make_function(TFunction &fn) -> typename FunctionHelper<TFunction>::Type {
        return static_cast<typename FunctionHelper<TFunction>::Type>(fn);
    }

}

/**
 * This class is a generic type to store fns. It's basically the same principe as boost::any design pattern
 * applied on fn functions. You can store the fn without specify any type information, and call it later. It
 * can be useful to store fn functions with different signatures into a map for example.
 */
class Function final {
public:

    Function() :
            _clone([](){ return std::make_pair(nullptr, nullptr); }),
            _delete([](Function *){}),
            _function(nullptr),
            _signature(nullptr) {
    }

    template<typename TFunction>
    Function(TFunction const &fn) {
        _clone = [&] () {
            auto function = new decltype(detail::make_function(fn))(detail::make_function(fn));
            return std::make_pair(static_cast<void *>(function), &typeid(function));
        };
        _delete = [&] (Function *self) {
            if (_function != nullptr) {
                delete static_cast<decltype(detail::make_function(fn)) *>(self->_function);
            }
        };
        auto cloned_function = _clone();
        _function  = cloned_function.first;
        _signature = cloned_function.second;
    }

    Function(Function const &other) :
            _clone(other._clone),
            _delete(other._delete) {
        auto cloned_function = _clone();
        _function  = cloned_function.first;
        _signature = cloned_function.second;
    }

    ~Function() {
        _delete(this);
    }

public:
    auto operator=(Function const &other) -> Function & {
        if (this != &other) {
            _clone = other._clone;
            _delete = other._delete;
            auto cloned_function = _clone();
            _function  = cloned_function.first;
            _signature = cloned_function.second;
        }
        return *this;
    }

    template<typename ...TArgs>
    auto operator()(TArgs &&...args) -> void {
        call(std::forward<TArgs>(args)...);
    }

public:
    template<typename TReturn = void, typename ...TArgs>
    auto call(TArgs &&...args) -> TReturn {
        if (_function == nullptr || _signature == nullptr)
            throw std::logic_error("Call of uninitialized function");
        auto function = static_cast<std::function<TReturn(TArgs...)>*>(_function);
        if (typeid(function) != *(_signature))
            throw std::logic_error("Signatures " + std::string(typeid(function).name()) +
                                           "and" + std::string(_signature->name()) + " mismatch");
        return (*function)(std::forward<TArgs>(args)...);
    }

private:
    std::function<std::pair<void *, std::type_info const *>()> _clone;
    std::function<void(Function *self)> _delete;
    void *_function;
    std::type_info const *_signature;
};