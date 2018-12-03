#pragma once

namespace Presentation {
    struct Compactbale {
        friend struct ____;
        virtual int Compact() noexcept = 0;
    protected:
        Compactbale() noexcept;
        ~Compactbale() noexcept;
    private:
        Compactbale* _Prev, *_Next;
    };
}
