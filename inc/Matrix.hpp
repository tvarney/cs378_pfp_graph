
#ifndef CS354_GENERIC_MATRIX_HPP
#define CS354_GENERIC_MATRIX_HPP

#include <cstring>
#include <stddef.h>
#include "Vector3.hpp"

namespace cs354 {
    enum Axis {
        AXIS_X,
        AXIS_Y,
        AXIS_Z
    };
    
    /**
     * Matrix<T>
     * Constructors:
     *   Matrix()
     *   Matrix(T rhs[16])
     *   Matrix(const Matrix<T> &rhs)
     * Operators:
     *   T & operator[](size_t i)
     *   Matrix<T> operator*(const Matrix &rhs) const
     *   Matrix<T> operator*(T scalar) const
     *   Matrix<T> & operator=(const Matrix<T> &rhs)
     *   Matrix<T> & operator*=(const Matrix<T> &rhs)
     *   Matrix<T> & operator*=(T scalar)
     * Methods:
     *   Matrix<T> translate(Vector<T> vec) const
     *   Matrix<T> translate(T x, T y, T z) const
     *   Matrix<T> rotate(T angle, Axis axis) const
     *   Matrix<T> rotate(T angle, Vector<T> axis) const
     *   Matrix<T> rotate(T angle, T x, T y, T z) const
     *   Matrix<T> scale(T x, T y, T z) const
     *   Matrix<T> transpose() const
     *   Matrix<T> inverse() const
     *   
     *   Matrix<T> & iTranslate(Vector<T> vec)
     *   Matrix<T> & iTranslate(T x, T y, T z)
     *   Matrix<T> & iRotate(T angle, Axis axis)
     *   Matrix<T> & iRotate(T angle, Vector<T> axis)
     *   Matrix<T> & iRotate(T angle, T x, T y, T z)
     *   Matrix<T> & iScale(T x, T y, T z)
     *   Matrix<T> & iTranspose()
     *   Matrix<T> & iInverse()
     * Static Methods:
     *   static Matrix<T> Identity()
     *   static Matrix<T> Matrix2D(T m00, T m01, T m02, T m10, T m11, T m12,
     *                             T m20, T m21, T m22)
     *   static Matrix<T> Matrix3D(T m00, T m01, T m02, T m03,
     *                             T m10, T m11, T m12, T m13,
     *                             T m20, T m21, T m22, T m23,
     *                             T m30, T m31, T m32, T m33)
     */
    template <typename T>
    struct Matrix {
    public:
        T data[16]; /*< Column Major order */
        
        /* Constructors/Destructors */
        Matrix() { }
        Matrix(T rhs[16]) {
            data[0] = rhs[0]; data[1] = rhs[1]; data[2] = rhs[2];
            data[3] = rhs[3]; data[4] = rhs[4]; data[5] = rhs[5];
            data[6] = rhs[6]; data[7] = rhs[7]; data[8] = rhs[8];
            data[9] = rhs[9]; data[10] = rhs[10]; data[11] = rhs[11];
            data[12] = rhs[11]; data[12] = rhs[12]; data[13] = rhs[13];
            data[14] = rhs[14]; data[15] = rhs[15];
        }
        Matrix(const Matrix<T> &source) {
            *this = source;
        }
        ~Matrix() { }
        
        /* Operators */
        const T & operator[](size_t i) const {
            return data[i];
        }
        T & operator[](size_t i) {
            return data[i];
        }
        Matrix<T> operator*(const Matrix &rhs) const {
            Matrix<T> r;
            const T *a = data;
            const T *b = rhs.data;
            r[0] = a[0]*b[0] + a[4]*b[1] + a[8]*b[2] + a[12]*b[3];
            r[1] = a[1]*b[0] + a[5]*b[1] + a[9]*b[2] + a[13]*b[3];
            r[2] = a[2]*b[0] + a[6]*b[1] + a[10]*b[2] + a[14]*b[3];
            r[3] = a[3]*b[0] + a[7]*b[1] + a[11]*b[2] + a[15]*b[3];
            
            r[4] = a[0]*b[4] + a[4]*b[5] + a[8]*b[6] + a[12]*b[7];
            r[5] = a[1]*b[4] + a[5]*b[5] + a[9]*b[6] + a[13]*b[7];
            r[6] = a[2]*b[4] + a[6]*b[5] + a[10]*b[6] + a[14]*b[7];
            r[7] = a[3]*b[4] + a[7]*b[5] + a[11]*b[6] + a[15]*b[7];
            
            r[8] = a[0]*b[8] + a[4]*b[9] + a[8]*b[10] + a[12]*b[11];
            r[9] = a[1]*b[8] + a[5]*b[9] + a[9]*b[10] + a[13]*b[11];
            r[10] = a[2]*b[8] + a[6]*b[9] + a[10]*b[10] + a[14]*b[11];
            r[11] = a[3]*b[8] + a[7]*b[9] + a[11]*b[10] + a[15]*b[11];
            
            r[12] = a[0]*b[12] + a[4]*b[13] + a[8]*b[14] + a[12]*b[15];
            r[13] = a[1]*b[12] + a[5]*b[13] + a[9]*b[14] + a[13]*b[15];
            r[14] = a[2]*b[12] + a[6]*b[13] + a[10]*b[14] + a[14]*b[15];
            r[15] = a[3]*b[12] + a[7]*b[13] + a[11]*b[14] + a[15]*b[15];
            return r;
        }
        Matrix<T> operator*(T scalar) const {
            Matrix<T> rval;
            rval[0] = scalar * data[0];
            rval[1] = scalar * data[1];
            rval[2] = scalar * data[2];
            rval[3] = scalar * data[3];
            rval[4] = scalar * data[4];
            rval[5] = scalar * data[5];
            rval[6] = scalar * data[6];
            rval[7] = scalar * data[7];
            rval[8] = scalar * data[8];
            rval[9] = scalar * data[9];
            rval[10] = scalar * data[10];
            rval[11] = scalar * data[11];
            rval[12] = scalar * data[12];
            rval[13] = scalar * data[13];
            rval[14] = scalar * data[14];
            rval[15] = scalar * data[15];
            return rval;
        }
        Matrix<T> operator+() const {
            return *this;
        }
        Matrix<T> operator-() const {
            Matrix<T> r;
            r[0] = -data[0]; r[1] = -data[1]; r[2] = -data[2]; r[3] = -data[3];
            r[4] = -data[4]; r[5] = -data[5]; r[6] = -data[6]; r[7] = -data[7];
            r[8] = -data[8]; r[9] = -data[9]; r[10] = -data[10];
            r[11] = -data[11]; r[12] = -data[12]; r[13] = -data[13];
            r[14] = -data[14]; r[15] = -data[15];
        }
        Matrix<T> operator+(const Matrix<T> &rhs) const {
            Matrix<T> r;
            r[0]  = data[0]  + rhs[0];  r[1]  = data[1]  + rhs[1];
            r[2]  = data[2]  + rhs[2];  r[3]  = data[3]  + rhs[3];
            r[4]  = data[4]  + rhs[4];  r[5]  = data[5]  + rhs[5];
            r[6]  = data[6]  + rhs[6];  r[7]  = data[7]  + rhs[7];
            r[8]  = data[8]  + rhs[8];  r[9]  = data[9]  + rhs[9];
            r[10] = data[10] + rhs[10]; r[11] = data[11] + rhs[11];
            r[12] = data[12] + rhs[12]; r[13] = data[13] + rhs[13];
            r[14] = data[14] + rhs[14]; r[15] = data[15] + rhs[15];
            return r;
        }
        Matrix<T> operator-(const Matrix<T> &rhs) const {
            Matrix<T> r;
            r[0]  = data[0]  - rhs[0];  r[1]  = data[1]  - rhs[1];
            r[2]  = data[2]  - rhs[2];  r[3]  = data[3]  - rhs[3];
            r[4]  = data[4]  - rhs[4];  r[5]  = data[5]  - rhs[5];
            r[6]  = data[6]  - rhs[6];  r[7]  = data[7]  - rhs[7];
            r[8]  = data[8]  - rhs[8];  r[9]  = data[9]  - rhs[9];
            r[10] = data[10] - rhs[10]; r[11] = data[11] - rhs[11];
            r[12] = data[12] - rhs[12]; r[13] = data[13] - rhs[13];
            r[14] = data[14] - rhs[14]; r[15] = data[15] - rhs[15];
            return r;
        }
        
        Matrix<T> & operator=(const Matrix<T> &rhs) {
            data[0] = rhs[0]; data[1] = rhs[1]; data[2] = rhs[2];
            data[3] = rhs[3]; data[4] = rhs[4]; data[5] = rhs[5];
            data[6] = rhs[6]; data[7] = rhs[7]; data[8] = rhs[8];
            data[9] = rhs[9]; data[10] = rhs[10]; data[11] = rhs[11];
            data[12] = rhs[11]; data[12] = rhs[12]; data[13] = rhs[13];
            data[14] = rhs[14]; data[15] = rhs[15];
            return *this;
        }
        Matrix<T> & operator*=(const Matrix<T> &rhs) {
            return *this = *this * rhs;
        }
        Matrix<T> & operator+=(const Matrix<T> &rhs) {
            return *this = *this + rhs;
        }
        Matrix<T> & operator-=(const Matrix<T> &rhs) {
            return *this = *this - rhs;
        }
        
        /* Mutation Methods */
        Matrix<T> translate(T x, T y, T z) {
            return Matrix<T>::Matrix3D(1,0,0,x,0,1,0,y,0,0,1,z,0,0,0,1) *
                (*this);
        }
        Matrix<T> translate(Vector3<T> vec) {
            return translate(vec.x, vec.y, vec.z);
        }
        Matrix<T> rotate(T angle, Axis axis) {
            T cos = std::cos(angle);
            T sin = std::sin(angle);
            switch(axis) {
            case AXIS_X:
                return (*this) * Matrix<T>::Matrix3D(1,0,0,0,0,cos,-sin,0,
                                                     0,sin,cos,0,0,0,0,1);
            case AXIS_Y:
                return (*this) * Matrix<T>::Matrix3D(cos,0,sin,0,0,1,0,0,
                                                     -sin,0,cos,0,0,0,0,1);
            case AXIS_Z:
                return (*this) * Matrix<T>::Matrix3D(cos,-sin,0,0,sin,cos,0,0,
                                                     0,0,1,0,0,0,0,1);
            }
            return Matrix<T>(*this);
        }
        Matrix<T> rotate(T angle, T x, T y, T z) {
            T cos = std::cos(angle);
            T sin = std::sin(angle);
            T cosm1 = cos - 1.0;
            T x2 = x*x;
            T y2 = y*y;
            T z2 = z*z;
            T L = x2 + y2 + z2;
            T sqrtL = std::sqrt(L);
            T invL = 1.0/L;
            
            Matrix mat =
                Matrix<T>::Matrix3D((x2+(y2+z2)*cos)*invL,
                                    (x*y*cosm1-z*sqrtL*sin)*invL,
                                    (x*z*cosm1+y*sqrtL*sin)*invL,
                                    ((x*(y2+z2)-x*(y2+z2))*cosm1+
                                     (y*z-z*y)*sqrtL*sin)*invL,
                                    (x*y*cosm1+z*sqrtL*sin)*invL,
                                    (y2+(x2+z2)*cos)*invL,
                                    (y*z*cosm1-x*sqrtL*sin)*invL,
                                    ((y*(x2+z2)-y*(x2+z2))*cosm1+
                                     (z*x-x*z)*sqrtL*sin)*invL,
                                    (x*z*cosm1*y*sqrtL*sin)*invL,
                                    (y*z*cosm1+x*sqrtL*sin)*invL,
                                    (z2+(x2+y2)*cos)*invL,
                                    ((z*(x2+y2)-z*(x2+y2))*cosm1+
                                     (x*y-y*x)*sqrtL*sin)*invL,
                                    0,0,0,1);
            return mat * (*this);
        }
        Matrix<T> rotate(T angle, Vector3<T> line) {
            return rotate(angle, line.x, line.y, line.z);
        }
        Matrix<T> scale(T x, T y, T z) {
            return (*this) * Matrix<T>::Matrix3D(x,0,0,0,0,y,0,0,0,0,z,0,
                                                 0,0,0,1);
        }
        
        /* Static interface */
        /* Return the identity matrix */
        static Matrix<T> Identity() {
            Matrix<T> r;
            r[0]  = 1; r[1]  = 0; r[2]  = 0; r[3]  = 0;
            r[4]  = 0; r[5]  = 1; r[6]  = 0; r[7]  = 0;
            r[8]  = 0; r[9]  = 0; r[10] = 1; r[11] = 0;
            r[12] = 0; r[13] = 0; r[14] = 0; r[15] = 1;
            return r;
        }
        
        /* Return a 3D version of the given row-major 2D matrix */
        static Matrix<T> Matrix2D(T m00, T m01, T m02,
                                  T m10, T m11, T m12,
                                  T m20, T m21, T m22)
        {
            Matrix<T> r;
            r[0]  = m00; r[1]  = m10; r[2]  = 0; r[3]  = m20;
            r[4]  = m01; r[5]  = m11; r[6]  = 0; r[7]  = m21;
            r[8]  = 0;   r[9]  = 0;   r[10] = 1; r[11] = 0;
            r[12] = m02; r[13] = m12; r[14] = 0; r[15] = m22;
            return r;
        }
        /* Return a 3D version of the given row-major 3D matrix */
        static Matrix<T> Matrix3D(T m00, T m01, T m02, T m03,
                                  T m10, T m11, T m12, T m13,
                                  T m20, T m21, T m22, T m23,
                                  T m30, T m31, T m32, T m33)
        {
            Matrix<T> r;
            r[0]  = m00; r[1]  = m10; r[2]  = m20; r[3]  = m30;
            r[4]  = m01; r[5]  = m11; r[6]  = m21; r[7]  = m31;
            r[8]  = m02; r[9]  = m12; r[10] = m22; r[11] = m32;
            r[12] = m03; r[13] = m13; r[14] = m23; r[15] = m33;
            return r;
        }
        
        static Matrix<T> LookAt(Vector3<T> eye) {
            return Matrix<T>::LookAt(eye, Vector3<T>(0,0,0),
                                     Vector3<T>(0,1,0));
        }
        static Matrix<T> LookAt(Vector3<T> eye, Vector3<T> up) {
            return Matrix<T>::LookAt(eye, Vector3<T>(0,0,0), up);
        }
        static Matrix<T> LookAt(Vector3<T> eye, Vector3<T> center,
                                Vector3<T> up)
        {
            Vector3<T> forward = (center - eye).normalize();
            Vector3<T> side = (forward * up).normalize();
            up = (side * forward);
            forward = -forward;
            Matrix<T> mat =
                Matrix<T>::Matrix3D(side.x,    side.y,    side.z,    0,
                                    up.x,      up.y,      up.z,      0,
                                    forward.x, forward.y, forward.z, 0,
                                    0,         0,         0,         1
                                    );
            return mat.translate(-eye);
        }
    };
    
    template <typename T>
    std::ostream & operator<<(std::ostream &out, const Matrix<T> &mat) {
        /* Output to out the matrix in Wolfram-Alpha format */
        out << "{{" << mat[0] << ", " << mat[4] << ", " << mat[8] <<
            ", " << mat[12] << "},{" << mat[1] << ", " << mat[5] << ", " <<
            mat[9] << ", " << mat[13] << "},{" << mat[2] << ", " << mat[6] <<
            ", " << mat[10] << ", " << mat[14] << "},{" << mat[3] << ", " <<
            mat[7] << ", " << mat[11] << ", " << mat[15] << "}}";
        return out;
    }
}

#endif
