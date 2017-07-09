// Coord.h
// 2-D coordination

#pragma once

// 2-D coordination
template <typename T> class Coord {
public:
	Coord(): x(0), y(0) { }

	Coord(T x1, T y1): x(x1), y(y1) { }

	Coord(const Coord &p):x(p.x), y(p.y) {  }

	void operator=(const Coord &p) { x = p.x, y = p.y; }

	virtual ~Coord() { }

	Coord operator+(const Coord &p) const {
		return Coord<T>(x + p.x, y + p.y);
	}

	Coord operator+() const {
		return *this;
	}

	Coord operator-(const Coord &p) const {
		return Coord<T>(x - p.x, y - p.y);
	}

	Coord operator-() const {
		return Coord<T>(-x, -y);
	}

	void operator+=(const Coord &p) {
		x += p.x; y += p.y; 
	}

	void operator-=(const Coord &p) {
		x -= p.x; y -= p.y; 
	}

	bool operator==(const Coord &p) const {
		return x == p.x && y == p.y;
	}

	bool operator!=(const Coord &p) const {
		return !(*this == p);
	}
	
	Coord operator*(T k) const {
		return Coord<T>(k * x, k * y);
	}

	Coord operator/(T k) const {
		assert(k);
		return Coord<T>(x / k, y / k);
	}

	void operator*=(T k) {
		x *= k; y *= k;
	}

	void operator/=(T k) {
		assert(k);
		x /= k; y /= k;
	}

	// in [x_begin, x_end) * [y_begin, y_end)
	bool isInSquare(int x_end, int y_end, int x_begin = 0, int y_begin = 0) const {
		return x >= x_begin && x < x_end && y >= y_begin && y < y_end;
	}

	T x, y;
};

//[Min, Max)
struct Limits
{
	int nXMin;
	int nYMin;
	int nXMax;
	int nYMax;
};

