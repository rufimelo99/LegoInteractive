#include "quaternion.h"
#include "math.h"

using namespace Quaternions;
using namespace Vectors;

#define PI 3.14159265

const float epsilon = (float)1.0e-5;

quaternion::quaternion()
	: t(0.0), x(0.0), y(0.0), z(0.0)
{}

quaternion::quaternion(float theta, const vector4D& axis){
    vector3D axis3d(axis.x, axis.y, axis.z);
    axis3d /= axis.w;
    vector4D axisn(Vectors::vector4D::normalize(vector4D(axis3d, 1.0)));

	quaternion q;
	float a = theta * (float)PI / 180.0f;
	t = cos(a / 2.0f);
	float s = sin(a / 2.0f);
	x = axisn.x * s;
	y = axisn.y * s;
	z = axisn.z * s;
}

quaternion::quaternion(const quaternion& q)
	: t(q.t), x(q.x), y(q.y), z(q.z)
{}

quaternion quaternion::operator=(const quaternion& q){
	t = q.t;
	x = q.x;
	y = q.y;
	z = q.z;
	for(int i = 0; i < 16; i++){
		openglMatrixValues[i] = q.openglMatrixValues[i];
	}
	return *this;
}

void quaternion::toAngleAxis(const quaternion& q, float& theta, vector4D& axis){
    quaternion qn(normalize(q));
	theta = 2.0f * acos(qn.t) * (float)(PI / 180.0);
	float s = sqrt(1.0f - qn.t*qn.t);
	if(s < epsilon) {
		axis.x = 1.0f;
		axis.y = 0.0f;
		axis.z = 0.0f;
		axis.w = 1.0f;
	} else {
		float sinv = 1 / s;
		axis.x = qn.x * sinv;
		axis.y = qn.y * sinv;
		axis.z = qn.z * sinv;
		axis.w = 1.0f;
	}
}

float quaternion::quadrance(const quaternion& q){
    return q.t*q.t + q.x*q.x + q.y*q.y + q.z*q.z;
}

float quaternion::norm(const quaternion& q){
    return sqrt(quadrance(q));
}

quaternion quaternion::normalize(const quaternion& q){
    float s = 1 / norm(q);
	return multiply(q, s);
}

quaternion quaternion::conjugate(const quaternion& q){
    quaternion qconj(q.t, vector4D(-q.x, -q.y, -q.z, 1.0f));
	return qconj;
}

quaternion quaternion::inverse(const quaternion& q){
    return multiply(conjugate(q), 1.0f / quadrance(q));
}

quaternion quaternion::add(const quaternion& q0, const quaternion& q1)
{
	quaternion q;
	q.t = q0.t + q1.t;
	q.x = q0.x + q1.x;
	q.y = q0.y + q1.y;
	q.z = q0.z + q1.z;
	return q;
}

quaternion quaternion::multiply(const quaternion& q, const float s){
    quaternion sq;
	sq.t = s * q.t;
	sq.x = s * q.x;
	sq.y = s * q.y;
	sq.z = s * q.z;
	return sq;
}

quaternion quaternion::multiply(const quaternion& q0, const quaternion& q1){
    quaternion q;
	q.t = q0.t * q1.t - q0.x * q1.x - q0.y * q1.y - q0.z * q1.z;
	q.x = q0.t * q1.x + q0.x * q1.t + q0.y * q1.z - q0.z * q1.y;
	q.y = q0.t * q1.y + q0.y * q1.t + q0.z * q1.x - q0.x * q1.z;
	q.z = q0.t * q1.z + q0.z * q1.t + q0.x * q1.y - q0.y * q1.x;
	return q;
}

float* quaternion::toOpenGLMatrix(quaternion& q){
    quaternion qn = normalize(q);

	float xx = qn.x * qn.x;
	float xy = qn.x * qn.y;
	float xz = qn.x * qn.z;
	float xt = qn.x * qn.t;
	float yy = qn.y * qn.y;
	float yz = qn.y * qn.z;
	float yt = qn.y * qn.t;
	float zz = qn.z * qn.z;
	float zt = qn.z * qn.t;

	q.openglMatrixValues[0] = 1.0f - 2.0f * ( yy + zz );
	q.openglMatrixValues[1] = 2.0f * ( xy + zt );
	q.openglMatrixValues[2] = 2.0f * ( xz - yt );
	q.openglMatrixValues[3] = 0.0f;
	q.openglMatrixValues[4] = 2.0f * ( xy - zt );
	q.openglMatrixValues[5] = 1.0f - 2.0f * ( xx + zz );
	q.openglMatrixValues[6] = 2.0f * ( yz + xt );
	q.openglMatrixValues[7] = 0.0f;
	q.openglMatrixValues[8] = 2.0f * ( xz + yt );
	q.openglMatrixValues[9] = 2.0f * ( yz - xt );
	q.openglMatrixValues[10] = 1.0f - 2.0f * ( xx + yy );
	q.openglMatrixValues[11] = 0.0f;
	q.openglMatrixValues[12] = 0.0f;
	q.openglMatrixValues[13] = 0.0f;
	q.openglMatrixValues[14] = 0.0f;
	q.openglMatrixValues[15] = 1.0f;

	return q.openglMatrixValues;
}

matrix4D quaternion::toMatrix(const quaternion& q){
    quaternion qn = normalize(q);

    matrix4D qMatrix;
    
	float xx = qn.x * qn.x;
	float xy = qn.x * qn.y;
	float xz = qn.x * qn.z;
	float xt = qn.x * qn.t;
	float yy = qn.y * qn.y;
	float yz = qn.y * qn.z;
	float yt = qn.y * qn.t;
	float zz = qn.z * qn.z;
	float zt = qn.z * qn.t;

	qMatrix.values[0][0] = 1.0f - 2.0f * ( yy + zz );
	qMatrix.values[1][0] = 2.0f * ( xy + zt );
	qMatrix.values[2][0] = 2.0f * ( xz - yt );
	qMatrix.values[3][0] = 0.0f;

	qMatrix.values[0][1] = 2.0f * ( xy - zt );
	qMatrix.values[1][1] = 1.0f - 2.0f * ( xx + zz );
	qMatrix.values[2][1] = 2.0f * ( yz + xt );
	qMatrix.values[3][1] = 0.0f;

	qMatrix.values[0][2] = 2.0f * ( xz + yt );
	qMatrix.values[1][2] = 2.0f * ( yz - xt );
	qMatrix.values[2][2] = 1.0f - 2.0f * ( xx + yy );
	qMatrix.values[3][2] = 0.0f;

	qMatrix.values[0][3] = 0.0f;
	qMatrix.values[1][3] = 0.0f;
	qMatrix.values[2][3] = 0.0f;
	qMatrix.values[3][3] = 1.0f;

    return transpose(qMatrix);
}

quaternion quaternion::lerp(const quaternion& q0, const quaternion& q1, float k){
    float cos_angle = q0.x*q1.x + q0.y*q1.y + q0.z*q1.z + q0.t*q1.t;
	float k0 = 1.0f - k;
	float k1 = (cos_angle > 0) ? k : -k;
	quaternion qi = add(multiply(q0, k0), multiply(q1, k1));
	return normalize(qi);
}

quaternion quaternion::slerp(const quaternion& q0, const quaternion& q1, float k){
    float angle = acos(q0.x*q1.x + q0.y*q1.y + q0.z*q1.z + q0.t*q1.t);
	float k0 = sin((1-k)*angle) / sin(angle);
	float k1 = sin(k*angle) / sin(angle);
	quaternion qi = add(multiply(q0,k0), multiply(q1,k1));
	return normalize(qi);
}

bool quaternion::isEqual(const quaternion& q0, const quaternion& q1){
    return ( fabs(q0.t-q1.t) < epsilon && fabs(q0.x-q1.x) < epsilon &&
		     fabs(q0.y-q1.y) < epsilon && fabs(q0.z-q1.z) < epsilon );
}

quaternion quaternion::operator*(const quaternion& q){
	quaternion newQ;
	newQ.t = t * q.t - x * q.x - y * q.y - z * q.z;
	newQ.x = t * q.x + x * q.t + y * q.z - z * q.y;
	newQ.y = t * q.y + y * q.t + z * q.x - x * q.z;
	newQ.z = t * q.z + z * q.t + x * q.y - y * q.x;
	return newQ;
}
