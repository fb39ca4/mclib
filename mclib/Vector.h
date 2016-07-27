#ifndef VECTOR_H_
#define VECTOR_H_

#include <cstdint>
#include <cmath>
#include <limits>
#include <ostream>
#include <sstream>

template <typename VecType>
class Vector3 {
public:
    union {
        struct {
            VecType x, y, z;
        };
        struct {
            VecType pitch, yaw, roll;
        };
    };

    typedef VecType value_type;

    Vector3() : x(0), y(0), z(0) { }
    Vector3(VecType x, VecType y) : x(x), y(y), z(0) { }
    Vector3(VecType x, VecType y, VecType z) : x(x), y(y), z(z) { }

    Vector3& operator=(const Vector3& other) {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    bool operator==(const Vector3& rhs) const {
        double epsilon = 0.00001;
        return std::fabs((double)x - rhs.x) < epsilon && 
               std::fabs((double)y - rhs.y) < epsilon &&
               std::fabs((double)z - rhs.z) < epsilon;
    }

    bool operator!=(const Vector3& rhs) const {
        return !(*this == rhs);
    }

    Vector3 operator-() {
        return Vector3(-x, -y, -z);
    }

    inline Vector3& operator+=(VecType v) {
        x += v;
        y += v;
        z += v;
        return *this;
    }

    inline Vector3& operator-=(VecType v) {
        x -= v;
        y -= v;
        z -= v;
        return *this;
    }

    inline Vector3& operator+=(const Vector3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    inline Vector3& operator-=(const Vector3& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    inline Vector3& operator*=(VecType v) {
        x *= v;
        y *= v;
        z *= v;
        return *this;
    }

    inline Vector3& operator/=(VecType v) {
        x /= v;
        y /= v;
        z /= v;
        return *this;
    }

    inline Vector3 operator+(const Vector3& v) {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    inline Vector3 operator-(const Vector3& v) {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    inline Vector3 operator/(const Vector3& v) {
        return Vector3(x / v.x, y / v.y, z / v.z);
    }

    inline Vector3 operator+(VecType v) {
        return Vector3(x + v, y + v, z + v);
    }

    inline Vector3 operator-(VecType v) {
        return Vector3(x - v, y - v, z - v);
    }

    inline Vector3 operator*(VecType v) {
        return Vector3(x * v, y * v, z * v);
    }

    inline Vector3 operator/(VecType v) {
        return Vector3(x / v, y / v, z / v);
    }

    inline double operator*(const Vector3& rhs) {
        return Dot(rhs);
    }

    inline double Length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    inline double LengthSq() const {
        return x * x + y * y + z * z;
    }

    inline void Normalize() {
        double length = Length();
        if (length > std::numeric_limits<VecType>::epsilon() * 2) {
            x /= length;
            y /= length;
            z /= length;
        }
    }

    inline double Dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    inline Vector3 Cross(const Vector3& v2) const {
        return Vector3(y*v2.z - z*v2.y,
                        z*v2.x - x*v2.z,
                        x*v2.y - y*v2.x);
    }

    inline double Distance(const Vector3& other) const {
        return Vector3(*this - other).Length();
    }
};

template <typename T>
inline double DotProduct(const Vector3<T>& v1, const Vector3<T>& v2) {
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

template <typename T>
inline Vector3<T> CrossProduct(const Vector3<T>& v1, const Vector3<T>& v2) {
    return Vector3<T>(v1.y*v2.z - v1.z*v2.y,
                   v1.z*v2.x - v1.x*v2.z,
                   v1.x*v2.y - v1.y*v2.x);
}

template <typename T>
inline Vector3<T> Vector3Normalize(const Vector3<T>& v1) {
    Vector3<T> copy = v1;
    copy.Normalize();
    return copy;
}

template <typename T>
inline bool operator<(const Vector3<T>& lhs, const Vector3<T>& rhs) {
    if (lhs.z < rhs.z) {
        return true;
    } else if (lhs.z > rhs.z) {
        return false;
    }

    if (lhs.y < rhs.y) {
        return true;
    } else if (lhs.y > rhs.y) {
        return false;
    }
    if (lhs.x < rhs.x) {
        return true;
    }
    return false;
}

// Todo: rotation matrix
template <typename T>
inline Vector3<T> Vector3RotateAboutY(Vector3<T> vec, double rads) {
    double cosA = std::cos(rads);
    double sinA = std::sin(rads);
    return Vector3<T>(cosA * vec.x - sinA * vec.z, vec.y, sinA * vec.x + cosA * vec.z);
}

template <typename T>
inline std::ostream& operator<<(std::ostream& out, const Vector3<T>& v) {
    return out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

template <typename T>
inline std::wostream& operator<<(std::wostream& out, const Vector3<T>& v) {
    return out << L"(" << v.x << L", " << v.y << L", " << v.z << L")";
}

template <typename T>
std::string to_string(const Vector3<T>& v) {
    std::stringstream ss;
    ss << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return ss.str();
}

template <typename T>
inline Vector3<T> operator+(const Vector3<T>& v1, const Vector3<T>& v2) {
    return Vector3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

template <typename T>
inline Vector3<T> operator-(const Vector3<T>& v1, const Vector3<T>& v2) {
    return Vector3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

typedef Vector3<int64_t> Vector3i;
typedef Vector3<int16_t> Vector3s;
typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;

inline Vector3d& operator+=(Vector3d& v1, const Vector3f& v2) {
    v1.x += v2.x;
    v1.y += v2.y;
    v1.z += v2.z;
    return v1;
}

inline Vector3d& operator-=(Vector3d& v1, const Vector3f& v2) {
    v1.x -= v2.x;
    v1.y -= v2.y;
    v1.z -= v2.z;
    return v1;
}

inline Vector3d ToVector3d(const Vector3f& v) {
    return Vector3d(v.x, v.y, v.z);
}

inline Vector3d ToVector3d(const Vector3i& v) {
    return Vector3d((double)v.x, (double)v.y, (double)v.z);
}

inline Vector3d ToVector3d(const Vector3s& v) {
    return Vector3d((double)v.x, (double)v.y, (double)v.z);
}

inline Vector3i ToVector3i(const Vector3d& d) {
    return Vector3i((Vector3i::value_type)std::floor(d.x), (Vector3i::value_type)std::floor(d.y), (Vector3i::value_type)std::floor(d.z));
}

#endif
