// Object.h
// rigid objects

#pragma once
#include <vector>
#include "Coord.h"
#include <ctime>
#include <cstdlib>


// rigid objects
class Object {
public:
	// change this enum to designate specific properties
	// currently, one interpretation is that PLAYER means movable blocks
	// while OBSTACLE has fallen to the ground and thus cannot move
	enum ObjectProperty { PLAYER, OBSTACLE };
	typedef unsigned char byte;

	Object(int x, int y, ObjectProperty prop) : center_(x, y),
		property_(prop) { }

	Object(const Coord<int> &center, ObjectProperty prop) :
		center_(center), property_(prop) { }

	virtual ~Object() { }

	Object(const Object &obj) : center_(obj.center_),
		property_(obj.property_), relative_positions_(obj.relative_positions_) {
	}

	void operator=(const Object &obj) {
		center_ = obj.center_;
		relative_positions_ = obj.relative_positions_;
		property_ = obj.property_;
	}

	// push contents by RELATIVE positions
	// it is the user's responsibility to ensure that no duplicate position is pushed
	void push(const Coord<int> &relative_position) {
		relative_positions_.push_back(relative_position);
	}

	// push contents by RELATIVE positions
	// it is the user's responsibility to ensure that no duplicate position is pushed
	void push(int delta_x, int delta_y) {
		push(Coord<int>(delta_x, delta_y));
	}

	// only keep the center, object property and the flat is_confined;
	void clear() {
		relative_positions_.clear();
	}

	// the following movements do not check whether the object exceeds the range of map
	void moveUp(int step = 1) {
		center_.y += step;
	}

	void moveDown(int step = 1) {
		center_.y -= step;
	}

	void moveLeft(int step = 1) {
		center_.x -= step;
	}

	void moveRight(int step = 1) {
		center_.x += step;
	}

	// using this->center_ as reference point
	void rotateLeft() {
		for (auto &r : relative_positions_) {
			auto tmp = r.x;
			r.x = -r.y;
			r.y = tmp;
		}
	}

	void rotateLeft(const Coord<int> &center) {
		for (auto &r : relative_positions_) {
			auto delta = r + this->center_ - center;
			auto tmp = delta.x;
			delta.x = -delta.y;
			delta.y = tmp;
			r = center + delta - this->center_;
		}
	}

	void rotateLeft(int x, int y) {
		rotateLeft(Coord<int>(x, y));
	}

	// using this->center_ as reference point
	void rotateRight() {
		for (auto &r : relative_positions_) {
			auto tmp = r.x;
			r.x = r.y;
			r.y = -tmp;
		}
	}

	void rotateRight(const Coord<int> &center) {
		for (auto &r : relative_positions_) {
			auto delta = r + this->center_ - center;
			auto tmp = delta.x;
			delta.x = delta.y;
			delta.y = -tmp;
			r = center + delta - this->center_;
		}
	}

	void rotateRight(int x, int y) {
		rotateRight(Coord<int>(x, y));
	}

	// using this->center_ as reference point
	void rotate180() {
		for (auto &r : relative_positions_) {
			r *= -1;
		}
	}

	void rotate180(const Coord<int> &center) {
		for (auto &r : relative_positions_) {
			auto delta = r + this->center_ - center;
			delta *= -1;
			r = center + delta - this->center_;
		}
	}

	void rotate180(int x, int y) {
		rotate180(Coord<int>(x, y));
	}

	// using this->center_ as reference point
	void flipLR() {
		for (auto &r : relative_positions_)
			r.x *= -1;
	}

	void flipLR(int x) {
		for (auto &r : relative_positions_)
			r.x = 2 * (x - center_.x) - r.x;
	}

	// using this->center_ as reference point
	void flipUD() {
		for (auto &r : relative_positions_)
			r.y *= -1;
	}

	void flipUD(int y) {
		for (auto &r : relative_positions_)
			r.y = 2 * (y - center_.y) - r.y;
	}

	Coord<int> get_center() const {
		return center_;
	}

	ObjectProperty get_object_property() const {
		return property_;
	}

	void set_object_property(ObjectProperty prop) {
		property_ = prop;
	}

	//bool get_is_confined() const {
	//	return is_confined_;
	//}

	// relative positions
	decltype(std::vector<Coord<int>>().begin()) begin() {
		return relative_positions_.begin();
	}

	// relative positions
	decltype(std::vector<Coord<int>>().rbegin()) rbegin() {
		return relative_positions_.rbegin();
	}

	// relative positions
	decltype(std::vector<Coord<int>>().end()) end() {
		return relative_positions_.end();
	}

	// relative positions
	decltype(std::vector<Coord<int>>().rend()) rend() {
		return relative_positions_.rend();
	}

private:
	Coord<int> center_;
	std::vector<Coord<int>> relative_positions_;
	enum ObjectProperty property_;	// player, obstacle, ...
									//bool is_confined_;				// whether confined in the map
};

class CCreator
{
	enum Shape { Z, S, L, J, O, T, I };
private:
	int Random(int base)
	{
		return std::rand() % base;
	}
public:
	Object operator ()(Coord<int> born)
	{
		Object oBlock(born, Object::PLAYER);
		oBlock.push(0, 0);
		int nSel = Random(7);
		switch (nSel)
		{
		case Z:
			oBlock.push(0, 1);
			oBlock.push(-1, 1);
			oBlock.push(1, 0);
			break;
		case S:
			oBlock.push(0, 1);
			oBlock.push(1, 1);
			oBlock.push(-1, 0);
			break;
		case L:
			oBlock.push(0, 1);
			oBlock.push(0, 2);
			oBlock.push(1, 0);
			break;
		case J:
			oBlock.push(0, 1);
			oBlock.push(0, 2);
			oBlock.push(-1, 0);
			break;
		case O:
			oBlock.push(0, 1);
			oBlock.push(1, 0);
			oBlock.push(1, 1);
			break;
		case T:
			oBlock.push(0, 1);
			oBlock.push(0, -1);
			oBlock.push(1, 0);
			break;
		case I:
			oBlock.push(0, 1);
			oBlock.push(0, 2);
			oBlock.push(0, -1);
			break;
		default:
			break;
		}
		return oBlock;
	}
};
