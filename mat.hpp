#pragma once

#include "vec.hpp"

using namespace mv;

enum class VectorKind  { VectorRow, VectorCol, };



class M_
{
protected:

	unsigned int row{ 0 };
	unsigned int col{ 0 };
	unsigned int rowLength{ 0 };
	unsigned int colHeight{ 0 };
	unsigned int mLength{ 0 };
	int : 4; // padding 4 bytes
	float* mArr{ nullptr };

	Vector makeV(VectorKind vk, unsigned int rowcol) const;

public:
	M_(unsigned int r, unsigned int c, float* ar);
	M_(unsigned int r, unsigned int c);
	M_(const M_& other);
	M_& operator=(const M_&) = delete;
	~M_();
	Vector GetRowV(unsigned int index) const;
	Vector GetColV(unsigned int index) const;
	


	

	friend std::ostream& operator<<(std::ostream& os, const M_& m);
	friend bool operator==(const M_& one, const M_& two);
	friend M_ operator+(const M_& one, const M_& two);
	friend M_ operator*(const M_& m, int scalar);
	friend M_ operator-(const M_& one, const M_& two);
	friend M_ operator*(const M_& one, const M_& two);
	friend M_ Transpose(const M_& m);


};

class M_i: public M_
{
	public:
	M_i(unsigned int r, unsigned int c);

};