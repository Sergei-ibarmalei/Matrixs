#include "mat.hpp"
#include <chrono>


int main()
{
	//constexpr int v2Length{ 2 };
	//constexpr int v3Length{ 3 };

	//float v2_arr[v2Length] = { 1.0f, 0.0f };
	//float v3_arr[v3Length] = { -1.0f, 3.0f, 4.0f };
	//float v3_arr2[v3Length] = { -4.0f, 0.f, -1.f };

	//mv::Vector u{ v3Length, v3_arr };
	//mv::Vector v{ v3Length, v3_arr2 };
	////std::cout << "angle between u and v: " << angleBetween(u, v) << std::endl;
	//std::cout << u << std::endl;
	//std::cout << "u normailize: " << u.Norm() << std::endl;

	float m14[4] = { 1.f,
					2.f,
					3.f,
					4.f };

	float m23_[6] = { 5.f, -1.f, 6.f,
					 -3.f, 0.f, 7.f };

	M_ m(2, 3, m23_);
	std::cout << "m: " << std::endl;
	std::cout << m << std::endl;
	unsigned int ticks = 100'000;
	auto begin = std::chrono::steady_clock::now();
	for (unsigned int i = 0; i < ticks; i++)
	{
		auto tmpm = Transpose(m);
	}
	auto end = std::chrono::steady_clock::now();
	auto middle = std::chrono::duration_cast<std::chrono::nanoseconds>((end - begin) / ticks);
	std::cout << "100'000 times Transpose(): " <<
		middle.count() << " ns\n";
	//std::cout << Transpose(m) << std::endl;
	//M_ m2(2, 3, m23_);
	//std::cout << m << std::endl;
	//std::cout << m2 << std::endl;
	//std::cout << "m * m2 : " << std::endl;
	//std::cout << m * m2 << std::endl;
	//std::cout << "m2 * m : " << std::endl;
	//std::cout << m2 * m << std::endl;
	//std::cout << "m -m2 : \n" << m - m2 << std::endl;
	//if (m == m2) std::cout << "equals\n";
	//else std::cout << "not equals\n";
	//std::cout << m << std::endl;
	//std::cout << "Vector row of 3: " << m.GetRowV(3) << std::endl;
	//std::cout << "Vector col of 1: " << m.GetColV(1) << std::endl;

	return 0;
}