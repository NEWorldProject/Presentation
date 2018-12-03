#pragma once

#include <stdexcept>

namespace Presentation::UI {
    class SubSysFailure : public std::runtime_error {
    public:
        using runtime_error::runtime_error;
    };
}
