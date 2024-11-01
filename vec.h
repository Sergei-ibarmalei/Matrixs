#pragma once

#include <iostream>
#include <iomanip>
#include <assert.h>
#include <cmath>


//class M_;

namespace mv
{
	
	

	class Vector
	{
	private:
		unsigned int dimension{ 0 };
		int : 4;
		float* vecArr{ nullptr };
		float magnitude() const;
	public:
		Vector(unsigned int d);
		Vector(unsigned int d, float* arr);
		Vector(const Vector& other);
		Vector& operator=(const Vector& other);

		Vector& operator*(const int scalar);
		Vector& operator+(const Vector&);
		Vector& operator-(const Vector&);
		Vector  Norm();
		bool operator==(const Vector&);

		const float* VArr() const { return vecArr; }
		const unsigned int VectorDimension() const { return dimension; }

		friend Vector  crosspr(const Vector& one, const Vector& two);
		friend float  dotpr(const Vector& one, const Vector& two);

		friend bool operator==(const Vector& one, const Vector& two);
		friend std::ostream& operator<<(std::ostream& os, const Vector& v);
		friend float angleBetween(const Vector& one, const Vector& two);
		friend float Magnitude(const Vector& v);
		//friend Vector Mult(const Vector& v, int scalar);
		

		
	};
}