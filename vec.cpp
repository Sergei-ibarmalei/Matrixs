#include "vec.h"

static const float eps{ 0.001f };

static constexpr auto  x_ = 0;
static constexpr auto  y_ = 1;
static constexpr auto  z_ = 2;


mv::Vector::Vector(unsigned int d)
{
	assert(d >= 2 && d < 4);

	dimension = d;
	vecArr = new float[dimension] {};
}

mv::Vector::Vector(unsigned int d, float* arr)
{
	assert(d >= 1 && d < 4);
	dimension = d;
	vecArr = new float[dimension];
	for (unsigned int i = 0; i < dimension; i++)
	{
		vecArr[i] = arr[i];
 	}
}

mv::Vector::Vector(const Vector& other)
{
	dimension = other.dimension;
	vecArr = new float[dimension];
	for (unsigned int i = 0; i < dimension; i++)
	{
		this->vecArr[i] = other.vecArr[i];
	}
}

mv::Vector& mv::Vector::operator=(const Vector& other)
{
	assert(this->dimension == other.dimension);

	if (this == &other) return *this;
	delete[] vecArr;
	vecArr = new float[static_cast<size_t>(this->dimension)];
	for (unsigned int i = 0; i < this->dimension; i++)
	{
		this->vecArr[i] = other.vecArr[i];
	}
	return *this;
}

bool mv::operator==(const Vector& one, const Vector& two)
{
	assert(one.dimension == two.dimension);
	for (unsigned int i = 0; i < one.dimension; i++)
	{
		if ((abs(one.vecArr[i] - two.vecArr[i]) < eps)) 
			return false;
	}
	return true;
}



namespace mv
{
	std::ostream& operator<<(std::ostream& os, const Vector& v)
	{
		os << "[";
		for (unsigned int i = 0; i < v.dimension; i++)
		{
			os << v.vecArr[i] << ", ";
		}
		os << "\b\b]";
		return os;
	}
}

mv::Vector& mv::Vector::operator*(const int scalar)
{
	for (unsigned int i = 0; i < this->dimension; i++)
	{
		vecArr[i] *= static_cast<float>(scalar);
	}
	return *this;
}


mv::Vector& mv::Vector::operator+(const mv::Vector& other)
{
	assert(this->dimension == other.dimension);
	for (unsigned int i = 0; i < this->dimension; i++)
	{
		this->vecArr[i] += other.vecArr[i];
	}
	return *this;
}

mv::Vector& mv::Vector::operator-(const Vector& other)
{
	assert(this->dimension == other.dimension);

	for (unsigned int i = 0; i < this->dimension; i++)
	{
		this->vecArr[i] -= other.vecArr[i];
	}
	return *this;
}



bool mv::Vector::operator==(const Vector& other)
{
	assert(this->dimension == other.dimension);
	return (this->vecArr[x_] == other.vecArr[x_] &&
		this->vecArr[y_] == other.vecArr[y_] &&
		this->vecArr[z_] == other.vecArr[z_]);
}


mv::Vector mv::crosspr(const Vector& one, const Vector& two)
{
	mv::Vector tempV(3);

	tempV.vecArr[x_] = one.vecArr[y_] * two.vecArr[z_] -
		one.vecArr[z_] * two.vecArr[y_];
	tempV.vecArr[y_] = one.vecArr[z_] * two.vecArr[x_] - 
		one.vecArr[x_] * two.vecArr[z_];
	tempV.vecArr[z_] = one.vecArr[x_] * two.vecArr[y_] - 
		one.vecArr[y_] * two.vecArr[x_];

	return tempV;
}

float mv::angleBetween(const Vector& one, const Vector& two)
{
	return (acosf(dotpr(one, two) / (one.magnitude() * 
		two.magnitude()))) * 180.f / 3.141592f;
}

float mv::dotpr(const Vector& one, const Vector& two)  
{
	assert(one.dimension == two.dimension);

	float td{ 0.f };

	for (unsigned int i = 0; i < one.dimension; i++)
	{
		td += (one.vecArr[i] * two.vecArr[i]);
	}
	return td;
}

float mv::Vector::magnitude() const 
{
	float sum{ 0.f };
	for (unsigned int i = 0; i < this->dimension; i++)
	{
		sum += (this->vecArr[i] * this->vecArr[i]);
	}
	return sqrtf(sum);
}

float mv::Magnitude(const Vector& v)  
{
	return v.magnitude();
}

mv::Vector mv::Vector::Norm()
{
	unsigned int dim = this->dimension;
	float magn = magnitude();
	float* tmpVA = new float[dim] {};
	for (unsigned int  i = 0; i < dim; i++)
	{
		tmpVA[i] = this->vecArr[i] / magn;
	}
	Vector tmpV{ dim, tmpVA };
	delete[] tmpVA;
	return tmpV;
}






