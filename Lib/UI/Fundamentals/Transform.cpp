#include "Transform.h"

namespace Presentation::UI {
    Math::Vec3D TransformBase::ApplyMatrix(const Math::Vec3D& in) const noexcept {
        const auto val = Math::Vec4D(in.X, in.Y, in.Z, 1.0)*GetMatrix();
        return Math::Vec3D(val.X, val.Y, val.Z);
    }

    Math::Vec3D TransformBase::ApplyReverse(const Math::Vec3D& in) const noexcept {
        const auto val = Math::Vec4D(in.X, in.Y, in.Z, 1.0)*GetReverse();
        return Math::Vec3D(val.X, val.Y, val.Z);
    }

    void TransformBase::SetParent(TransformBase& parent) noexcept { _Parent = std::addressof(parent); }

    void TransformBase::CacheFlush() noexcept {
        if (_Parent)
            _Parent->CacheFlush();
    }

    Transforms::Transforms() noexcept
            :_Matrix(Math::Mat4D::Identity()), _Reverse(Math::Mat4D::Identity()) { }

    Math::Mat4D Transforms::GetMatrix() const noexcept { return _Matrix; }

    Math::Mat4D Transforms::GetReverse() const noexcept { return _Reverse; }

    Transforms::IteratorType Transforms::Remove(ConstIteratorType iter) {
        const auto ret =  _Transforms.erase(iter);
        CacheFlush();
        return ret;
    }

    Transforms::IteratorType Transforms::Remove(IteratorType iBegin, IteratorType iEnd) {
        const auto ret = _Transforms.erase(iBegin, iEnd);
        CacheFlush();
        return ret;
    }

    void Transforms::Append(HandleType handle) {
        _Matrix *= handle->GetMatrix();
        _Reverse = handle->GetReverse() * _Reverse;
        _Transforms.push_back(std::move(handle));
        TransformBase::CacheFlush();
    }

    auto Transforms::Insert(ConstIteratorType iter, HandleType handle) {
        handle->SetParent(*this);
        const auto ret = _Transforms.insert(iter, std::move(handle));
        CacheFlush();
        return ret;
    }

    auto Transforms::Insert(size_t index, HandleType handle) {
        handle->SetParent(*this);
        const auto ret = _Transforms.insert(begin()+index, std::move(handle));
        CacheFlush();
        return ret;
    }

    void Transforms::CacheFlush() noexcept {
        _Matrix = Math::Mat4D::Identity();
        for (const auto& transforms : _Transforms)
            _Matrix *= transforms->GetMatrix();
        _Reverse = Math::Mat4D::Identity();
        for (auto iter = _Transforms.crbegin(); iter!=_Transforms.crend(); ++iter)
            _Reverse *= (*iter)->GetReverse();
        TransformBase::CacheFlush();
    }

    Math::Mat4D TranslateTransform::GetMatrix() const noexcept {
        return Math::Mat4D(
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                _Translate.X, _Translate.Y, _Translate.Z, 1.0
        );
    }

    Math::Mat4D TranslateTransform::GetReverse() const noexcept {
        return Math::Mat4D(
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                -_Translate.X, -_Translate.Y, -_Translate.Z, 1.0
        );
    }

    RotateTransform::RotateTransform(const Math::Vec3D& axis, double rad) noexcept
            :_Matrix(ComputeRotationMatrix(axis, rad)), _Reverse(ComputeRotationMatrix(axis, -rad)) { }

    Math::Mat4D RotateTransform::GetMatrix() const noexcept { return _Matrix; }

    Math::Mat4D RotateTransform::GetReverse() const noexcept { return _Reverse; }

    void RotateTransform::SetRotation(const Math::Vec3D& axis, double rad) noexcept {
        _Matrix = ComputeRotationMatrix(axis, rad);
        _Reverse = ComputeRotationMatrix(axis, -rad);
        CacheFlush();
    }

    Math::Mat4D RotateTransform::ComputeRotationMatrix(const Math::Vec3D& axis, double rad) noexcept {
        const double _cos = cos(rad), _1_cos = 1.0-_cos, _sin = sin(rad),
                _x2 = axis.X*axis.X, _y2 = axis.Y*axis.Y, _z2 = axis.Z*axis.Z,
                _xy = axis.X*axis.Y, _yz = axis.Y*axis.Z, _xz = axis.X*axis.Z;
        return Math::Mat4D(
                _cos+_1_cos*_x2, _1_cos*_xy+_sin*axis.Z, _1_cos*_xz-_sin*axis.Y, 0.0,
                _1_cos*_xy-_sin*axis.Z, _cos+_1_cos*_y2, _1_cos*_yz+_sin*axis.X, 0.0,
                _1_cos*_xz+_sin*axis.Y, _1_cos*_yz-_sin*axis.X, _cos+_1_cos*_z2, 0.0,
                0.0, 0.0, 0.0, 1.0
        );
    }

    Math::Mat4D ScaleTransform::GetMatrix() const noexcept {
        return Math::Mat4D(
                _Scale.X, 0.0, 0.0, 0.0,
                0.0, _Scale.Y, 0.0, 0.0,
                0.0, 0.0, _Scale.Z, 0.0,
                0.0, 0.0, 0.0, 1.0
        );
    }

    Math::Mat4D ScaleTransform::GetReverse() const noexcept {
        return Math::Mat4D(
                1.0/_Scale.X, 0.0, 0.0, 0.0,
                0.0, 1.0/_Scale.Y, 0.0, 0.0,
                0.0, 0.0, 1.0/_Scale.Z, 0.0,
                0.0, 0.0, 0.0, 1.0
        );
    }

    void TransformHolder::Content(TransformBase& child) noexcept { child.SetParent(*this); }
}
