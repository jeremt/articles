//
// Copyright (c) 2015 DudeTeam. All rights reserved.
//

#pragma once

namespace detail {
    constexpr bool _static_cmp(char const *one, char const *two) {
        return (*one && *two) ? (*one == *two && _static_cmp(one + 1, two + 1)) : (!*one && !*two);
    }
}

#define FIELD(field_type, field_name, getter, setter) \
    public: \
        field_type const &field_name() { \
            static_assert(!detail::_static_cmp(#getter, "false"), "Field "#field_name" has no getter"); \
            return _##field_name; \
        } \
        void field_name(field_type const &value) { \
            static_assert(!detail::_static_cmp(#setter, "false"), "Field "#field_name" has no setter"); \
            _##field_name = value; \
        } \
    private: \
        field_type _##field_name;