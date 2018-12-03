//
// Created by 刘予顺 on 2018/11/29.
//

#include "Memory.h"
#include "Alias.h"
#include <new>

namespace Presentation {
    struct ____ : Compactbale {
        int Compact() noexcept override {
            int ret = 0;
            _Lock.enter();
            auto current = _Next;
            while (current) {
                ret += current->Compact();
                current = current->_Next;
            }
            _Lock.leave();
            return ret;
        }

        void Register(Compactbale* pCompactbale) noexcept {
            _Lock.enter();
            _Tail->_Next = pCompactbale;
            pCompactbale->_Prev = _Tail;
            pCompactbale->_Next = nullptr;
            _Tail = pCompactbale;
            _Lock.leave();
        }

        void Unregister(Compactbale* pCompactbale) noexcept {
            _Lock.enter();
            if (pCompactbale->_Next) {
                pCompactbale->_Next->_Prev = pCompactbale->_Prev;
                pCompactbale->_Prev->_Next = pCompactbale->_Next;
            }
            else {
                _Tail = pCompactbale->_Prev;
            }
            _Lock.leave();
        }
    private:
        task::spin_lock _Lock {};
        Compactbale* _Tail = this;
    } Zero;

    int __Compact() noexcept { return Zero.Compact(); };

    Compactbale::Compactbale() noexcept { if (this != &Zero) Zero.Register(this); }

    Compactbale::~Compactbale() noexcept { if (this != &Zero) Zero.Unregister(this); }
}

namespace {
    struct _A_ {
        _A_() noexcept {
            std::set_new_handler([]()noexcept {
                if (!Presentation::__Compact())
                    std::set_new_handler(nullptr);
            });
        }
    } _AA_;
}
