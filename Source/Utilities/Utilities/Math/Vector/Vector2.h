#pragma once

#include <initializer_list>

#include "Interfaces/Serializable.h"

namespace ENGINE_NAMESPACE::Math
{
	template <typename T>
	class Vector2 final : public ISerializable
	{
	public:
		Vector2();
		Vector2(const T& aX, const T& aY);
		Vector2(const std::initializer_list<T> initList);
		~Vector2() = default;

	public:
		rapidjson::Value Save(rapidjson::Document::AllocatorType& allocator) const override;
		void Load(const rapidjson::Value& aValue) override;

	public:
		const Vector2 operator+(const Vector2& anotherVec) const;
		const Vector2& operator+=(const Vector2& anotherVec);

		const Vector2 operator-(const Vector2& anotherVec) const;
		const Vector2& operator-=(const Vector2& anotherVec);

		const Vector2 operator*(const Vector2& anotherVec) const;
		const Vector2& operator*=(const Vector2& anotherVec);

		Vector2 operator=(const Vector2& anotherVec);
		Vector2 operator==(const Vector2& anotherVec);

		friend Vector2 operator*(const Vector2& aVec, const T& aScalar)
		{
			return Vector2(aVec.x * aScalar, aVec.y * aScalar);
		}

		friend Vector2 operator*(const T& aScalar, const Vector2& aVec)
		{
			return Vector2(aVec.x * aScalar, aVec.y * aScalar);
		}

		friend Vector2 operator/(const Vector2& aVec, const T& aScalar)
		{
			return Vector2(aVec.x / aScalar, aVec.y / aScalar);
		}

		friend Vector2 operator/(const T& aScalar, const Vector2& aVec)
		{
			return Vector2(aScalar / aVec.x, aScalar / aVec.y);
		}

	public:
		T Dot(const Vector2& anotherVec) const;
		static T Dot(const Vector2& aVec0, const Vector2& aVec1);

		T Distance(const Vector2& anotherVec) const;
		static T Distance(const Vector2& aVec0, const Vector2& aVec1);

		T DistanceSqrd(const Vector2& anotherVec) const;
		static T DistanceSqrd(const Vector2& aVec0, const Vector2& aVec1);

		T Length() const;
		T LengthSqrd() const;

	public:
		Vector2<T> Normalized() const;
		void Normalize();

		Vector2<T> Perpendicular() const;
		static Vector2<T> Perpendicular(const Vector2& aVec);

		T AngleBetween(const Vector2& anotherVec) const;
		static T AngleBetween(const Vector2& aVec0, const Vector2& aVec1);

	public:
		union
		{
			struct { T x, y; };
			struct { T X, Y; };
			struct { T myX, myY; };

			T data[2];
			T myData[2];
		};
	};

	typedef Vector2<float> Vector2f;
	typedef Vector2<unsigned> Vector2ui;
	typedef Vector2<int> Vector2i;
	typedef Vector2<double> Vector2d;
}

#include "Vector2.inl"