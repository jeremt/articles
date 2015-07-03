#pragma once

#include <tuple>
#include <cstddef>
#include <memory>

namespace detail { // private implementation code

    template<size_t TCount>
    struct CallerHelper {
        template<typename TFunction, typename TFirst, typename ...TRest>
        auto operator()(TFunction &&fn, TFirst &&first, TRest &&...rest) const -> void {
            CallerHelper<TCount - 1>()(
                    std::forward<TFunction>(fn),
                    std::forward<TFirst>(first),
                    std::get<TCount - 1>(std::forward<TFirst>(first)),
                    std::forward<TRest>(rest)...);
        }
    };

    template<>
    struct CallerHelper<0> {
        template<typename TFunction, typename TFirst, typename ...TRest>
        auto operator()(TFunction &&fn, TFirst &&, TRest &&...rest) const -> void {
            fn(std::forward<TRest>(rest)...);
        }
    };

}

/**
 * This class allows to store a function and its parameters to call it later (like in `std::thread` for instance.
 */
template<typename TFunction, typename ...TArgs>
class Callable final {
public:
    Callable(TFunction &&fn, TArgs &&...args) :
            _fn(std::forward<TFunction>(fn)),
            _args(std::forward<TArgs>(args)...) {
    }

    Callable(Callable const &other) = default;
    Callable(Callable &&other) = default;
    ~Callable() = default;

public:
    auto operator=(Callable const &other) -> Callable & = default;
    auto operator=(Callable &&other) -> Callable & = default;
    auto operator()() -> void {
        detail::CallerHelper<sizeof...(TArgs)>()(_fn, _args);
    }

private:
    TFunction _fn;
    std::tuple<TArgs...> _args;
};

/**
 * This helper allows to infer the type of the callable parameters. So the callable can be created directly like so:
 *
 * ```
 * auto c = make_callable([] (int a, bool b) { ... }, 10, true);
 * ```
 */
template<typename TFunction, typename ...TArgs>
auto make_callable(TFunction &&fn, TArgs &&...args) -> Callable<TFunction, TArgs...> {
    return Callable<TFunction, TArgs...>(std::forward<TFunction>(fn), std::forward<TArgs>(args)...);
}