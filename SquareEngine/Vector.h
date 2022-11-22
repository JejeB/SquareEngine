#pragma once
struct Vector
{
	float x;
	float y;

	Vector operator+(Vector v) {
		Vector r;
		r.x = v.x + x;
		r.y = v.y + y;
		return r;
	}
	Vector operator-(Vector v) {
		Vector r;
		r.x = x - v.x;
		r.y = y - v.y;
		return r;
	}
	Vector operator*(Vector v) {
		Vector r;
		r.x = x * v.x;
		r.y = y * v.y;
		return r;
	}
	Vector operator/(Vector v) {
		Vector r;
		r.x = x / v.x;
		r.y = y / v.y;
		return r;
	}
	Vector opp() {
		Vector r;
		r.x = -x;
		r.y = -y;
		return r;
	}
	Vector by(float f) {
		Vector r;
		r.x = x * f;
		r.y = y * f;
		return r;
	}
	Vector abs() {
		Vector r;
		r.x = x > 0 ? x : -x;
		r.y = y > 0 ? y : -y;
		return r;
	}
};

