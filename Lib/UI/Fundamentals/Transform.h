#pragma once

#include <vector>
#include <Math/Matrix.h>
#include <Core/Intrusive.h>

namespace Presentation::UI {
    struct TransformBase : IntrusiveVTBase {
        virtual Math::Mat4D GetMatrix() const noexcept = 0;
        virtual Math::Mat4D GetReverse() const noexcept = 0;
        Math::Vec3D ApplyMatrix(const Math::Vec3D& in) const noexcept;
        Math::Vec3D ApplyReverse(const Math::Vec3D& in) const noexcept;
    protected:
        virtual void CacheFlush() noexcept;
    private:
        friend class Transforms;
        void SetParent(TransformBase& parent) noexcept;
        TransformBase* _Parent = nullptr;
    };

    class Transforms : public TransformBase {
    public:
        using HandleType = IntrusivePtr<TransformBase>;
        using ContainerType = std::vector<HandleType>;
        using IteratorType = ContainerType::iterator;
        using ConstIteratorType = ContainerType::const_iterator;
        Transforms() noexcept;
        auto begin() noexcept { return _Transforms.begin(); }
        auto end() noexcept { return _Transforms.end(); }
        auto begin() const noexcept { return _Transforms.begin(); }
        auto end() const noexcept { return _Transforms.end(); }
        auto& operator[](size_t idx) { return _Transforms[idx]; }
        auto& operator[](size_t idx) const { return _Transforms[idx]; }
        auto& at(size_t idx) { return _Transforms.at(idx); }
        auto& at(size_t idx) const { return _Transforms.at(idx); }
        IteratorType Remove(ConstIteratorType iter);
        IteratorType Remove(IteratorType iBegin, IteratorType iEnd);
        void Remove(size_t idx) { Remove(begin()+idx); }
        void Remove(size_t idx, size_t count) { Remove(begin()+idx, begin()+idx+count); }
        void Append(HandleType handle);
        auto Insert(ConstIteratorType iter, HandleType handle);
        auto Insert(size_t index, HandleType handle);
        Math::Mat4D GetMatrix() const noexcept override;
        Math::Mat4D GetReverse() const noexcept override;
    protected:
        void CacheFlush() noexcept override;
    private:
        Math::Mat4D _Matrix, _Reverse;
        std::vector<IntrusivePtr<TransformBase>> _Transforms;
    };

    class TranslateTransform : public TransformBase {
    public:
        explicit TranslateTransform(const Math::Vec3D& r) noexcept
                :_Translate(r) { }
        Math::Mat4D GetMatrix() const noexcept override;
        Math::Mat4D GetReverse() const noexcept override;
        auto& GetTranslate() const noexcept { return _Translate; }
        void SetTranslate(const Math::Vec3D& trans) noexcept {
            _Translate = trans;
            CacheFlush();
        }
    private:
        Math::Vec3D _Translate;
    };

    class RotateTransform : public TransformBase {
    public:
        RotateTransform(const Math::Vec3D& axis, double rad) noexcept;
        Math::Mat4D GetMatrix() const noexcept override;
        Math::Mat4D GetReverse() const noexcept override;
        void SetRotation(const Math::Vec3D& axis, double rad) noexcept;
    private:
        static Math::Mat4D ComputeRotationMatrix(const Math::Vec3D& axis, double rad) noexcept;
        Math::Mat4D _Matrix, _Reverse;
    };

    class ScaleTransform : public TransformBase {
    public:
        explicit ScaleTransform(const Math::Vec3D& scale) noexcept
                :_Scale(scale) { }
        Math::Mat4D GetMatrix() const noexcept override;
        Math::Mat4D GetReverse() const noexcept override;
        auto& GetScale() const noexcept { return _Scale; }
        void SetScale(const Math::Vec3D& trans) noexcept {
            _Scale = trans;
            CacheFlush();
        }
    private:
        Math::Vec3D _Scale;
    };
}
