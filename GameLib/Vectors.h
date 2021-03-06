/***************************************************************************************
 * Original Author:		Gabriele Giuseppini
 * Created:				2018-01-21
 * Copyright:			Gabriele Giuseppini  (https://github.com/GabrieleGiuseppini)
 ***************************************************************************************/
#pragma once

#include <cmath>
#include <cstddef>
#include <string>

struct vec2f
{
public:
	
    float x, y;

    static constexpr const vec2f zero() 
    { 
        return vec2f(); 
    }

	inline vec2f operator+(vec2f const & other) const
	{
		return vec2f(
			x + other.x, 
			y + other.y);
	}

	inline vec2f operator-(vec2f const & other) const
	{
		return vec2f(
			x - other.x, 
			y - other.y);
	}

    inline vec2f operator-() const
    {
        return vec2f(
            -x,
            -y);
    }

	inline vec2f operator*(float other) const
	{
		return vec2f(
			x * other,
			y * other);
	}

	inline vec2f operator/(float other) const
	{
		return vec2f(
			x / other,
			y / other);
	}

	inline vec2f & operator+=(vec2f const & other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	inline vec2f & operator-=(vec2f const & other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	inline vec2f & operator*=(float other)
	{
		x *= other;
		y *= other;
		return *this;
	}

	inline vec2f& operator/=(float other)
	{
		x /= other;
		y /= other;
		return *this;
	}

	inline bool operator==(vec2f const & other) const
	{
		return x == other.x && y == other.y;
	}

    inline bool operator!=(vec2f const & other) const
    {
        return !(*this == other);
    }

	// (lexicographic comparison only)
	inline bool operator<(vec2f const & other) const
	{
		return x < other.x || (x == other.x && y < other.y);
	}

	inline float dot(vec2f const & other) const
	{
		return x * other.x + y * other.y;
	}

    inline float cross(vec2f const & other) const
    {
        return x * other.y - y * other.x;
    }

	inline float length() const
	{
        return sqrtf(x * x + y * y);
	}

    inline float squareLength() const
    {
        return x * x + y * y;
    }

	inline vec2f normalise() const
	{
        float const squareLength = x * x + y * y;
        if (squareLength > 0)
        {
            return (*this) / sqrtf(squareLength);
        }
        else
        {
            return vec2f(0.0f, 0.0f);
        }
	}

    inline vec2f normalise(float length) const
    {
        if (length > 0)
        {
            return (*this) / length;
        }
        else
        {
            return vec2f(0.0f, 0.0f);
        }
    }

    inline float angle(vec2f const & other) const
    {
        return -atan2f(
            x * other.y - y * other.x,
            x * other.x + y * other.y);
    }

    std::string toString() const;

    inline constexpr vec2f()
        : x(0.0f)
        , y(0.0f)
    {
    }

	inline constexpr vec2f(
		float _x,
		float _y)
		: x(_x)
		, y(_y)
	{
	}
};

static_assert(offsetof(vec2f, x) == 0);
static_assert(offsetof(vec2f, y) == sizeof(float));
static_assert(sizeof(vec2f) == 2 * sizeof(float));



struct vec3f
{
public:
	
    float x, y, z;

    static constexpr const vec3f zero() { return vec3f(); }

	inline vec3f operator+(vec3f const & other) const
	{
		return vec3f(
			x + other.x,
			y + other.y,
			z + other.z);
	}

    inline vec3f operator-(vec3f const & other) const
	{
		return vec3f(
			x - other.x,
			y - other.y,
			z - other.z);
	}

    inline vec3f operator-() const
    {
        return vec3f(
            -x,
            -y,
            -z);
    }

	inline vec3f operator*(float other) const
	{
		return vec3f(
			x * other,
			y * other,
			z * other);
	}

	inline vec3f operator/(float other) const
	{
		return vec3f(
			x / other,
			y / other,
			z / other);
	}

	inline vec3f & operator+=(vec3f const & other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	inline vec3f & operator-=(vec3f const & other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	inline vec3f & operator*=(float other)
	{
		x *= other;
		y *= other;
		z *= other;
		return *this;
	}

	inline vec3f & operator/=(float other)
	{
		x /= other;
		y /= other;
		z /= other;
		return *this;
	}

	inline bool operator==(vec3f const & other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

    inline bool operator!=(vec3f const & other) const
    {
        return !(*this == other);
    }

	// (lexicographic comparison only)
	inline bool operator<(vec3f const & other) const
	{
		return x < other.x || (x == other.x && (y < other.y || (y == other.y && z < other.z)));
	}
    
	float dot(vec3f const & other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}
    
	float length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

    float squareLength() const
    {
        return x * x + y * y + z * z;
    }

	vec3f normalise() const
	{
        float const squareLength = x * x + y * y + z * z;
        if (squareLength > 0)
        {
            return (*this) / sqrtf(squareLength);
        }
        else
        {
            return vec3f(0.0f, 0.0f, 0.0f);
        }
	}

    std::string toString() const;

    inline constexpr vec3f()
        : x(0.0f)
        , y(0.0f)
        , z(0.0f)
    {
    }

	inline constexpr vec3f(
		float _x,
		float _y,
		float _z)
		: x(_x)
		, y(_y)
		, z(_z)
	{
	}
};

static_assert(offsetof(vec3f, x) == 0);
static_assert(offsetof(vec3f, y) == sizeof(float));
static_assert(offsetof(vec3f, z) == 2 * sizeof(float));
static_assert(sizeof(vec3f) == 3 * sizeof(float));



struct vec4f
{
public:

    float x, y, z, w;

    static constexpr const vec4f zero() { return vec4f(); }

    inline vec4f operator+(vec4f const & other) const
    {
        return vec4f(
            x + other.x,
            y + other.y,
            z + other.z,
            w + other.w);
    }

    inline vec4f operator-(vec4f const & other) const
    {
        return vec4f(
            x - other.x,
            y - other.y,
            z - other.z,
            w - other.w);
    }

    inline vec4f operator-() const
    {
        return vec4f(
            -x,
            -y,
            -z,
            -w);
    }

    inline vec4f operator*(float other) const
    {
        return vec4f(
            x * other,
            y * other,
            z * other,
            w * other);
    }

    inline vec4f operator/(float other) const
    {
        return vec4f(
            x / other,
            y / other,
            z / other,
            w / other);
    }

    inline vec4f & operator+=(vec4f const & other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    inline vec4f & operator-=(vec4f const & other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    inline vec4f & operator*=(float other)
    {
        x *= other;
        y *= other;
        z *= other;
        w *= other;
        return *this;
    }

    inline vec4f & operator/=(float other)
    {
        x /= other;
        y /= other;
        z /= other;
        w /= other;
        return *this;
    }

    inline bool operator==(vec4f const & other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    inline bool operator!=(vec4f const & other) const
    {
        return !(*this == other);
    }
    
    std::string toString() const;

    inline constexpr vec4f()
        : x(0.0f)
        , y(0.0f)
        , z(0.0f)
        , w(0.0f)
    {
    }

    inline constexpr vec4f(
        float _x,
        float _y,
        float _z,
        float _w)
        : x(_x)
        , y(_y)
        , z(_z)
        , w(_w)
    {
    }
};

static_assert(offsetof(vec4f, x) == 0);
static_assert(offsetof(vec4f, y) == sizeof(float));
static_assert(offsetof(vec4f, z) == 2 * sizeof(float));
static_assert(offsetof(vec4f, w) == 3 * sizeof(float));
static_assert(sizeof(vec4f) == 4 * sizeof(float));
