#include "mat.hpp"


M_::M_(unsigned int r, unsigned int c, float* ar)
{
	assert(r > 0 && c > 0);
	row = r;
	col = c;
	rowLength = col;
	colHeight = row;
	mLength = row * col;
	mArr = new float[mLength] {};
	for (unsigned int i = 0; i < mLength; i++)
	{
		mArr[i] = ar[i];
	}

}

M_::M_(const M_& other)
{
	this->row = other.row;
	this->col = other.col;
	this->rowLength = other.rowLength;
	this->colHeight = other.colHeight;
	this->mLength = other.mLength;
	this->mArr = new float[this->mLength]{};
	for (unsigned int i = 0; i < this->mLength; i++)
	{
		this->mArr[i] = other.mArr[i];
	}

}



M_::~M_()
{
	delete[] mArr;
	mArr = nullptr;
}



Vector M_::makeV(VectorKind vk, unsigned int rowcol) const
{
	switch (vk)
	{
		case  VectorKind::VectorRow:
		{
			unsigned int v_dim = this->rowLength;
			float* tmpVArr = new float[v_dim] {};
			for (unsigned int i = 0; i < v_dim; i++)
			{
				tmpVArr[i] = mArr[(rowcol) * rowLength + i];
			}
			Vector tmpV(v_dim, tmpVArr);
			delete[] tmpVArr; tmpVArr = nullptr;
			return tmpV;
			break;
		}
		case VectorKind::VectorCol:
		{
			unsigned int v_dim = this->colHeight;
			float* tmpVArr = new float[v_dim] {};
			for (unsigned int i = 0; i < v_dim; i++)
			{
				tmpVArr[i] = mArr[(rowLength * i) + rowcol];
			}
			Vector tmpV(v_dim, tmpVArr);
			delete[]tmpVArr; tmpVArr = nullptr;
			return tmpV;
			break;
		}
	}
}

Vector M_::GetRowV(unsigned int index) const
{
	return makeV(VectorKind::VectorRow, index);
}

Vector M_::GetColV(unsigned int index) const
{
	return makeV(VectorKind::VectorCol, index);
}




//===========FRIENDS================
std::ostream& operator<<(std::ostream& os, const M_& m)
{
	for (unsigned int r = 0; r < m.row; r++)
	{
		os << "| ";
		for (unsigned int c = 0; c < m.col; c++)
		{
			os << std::setw(3) << m.mArr[(r * m.rowLength) + c] << ' ';
		}
		os << "  |\n";
	}
	os << "\n";
	return os;
}

bool operator==(const M_& one, const M_& two)
{
	assert(one.row == two.row && one.col == two.col);
	for (unsigned int r = 0; r < one.row; r++)
	{
		for (unsigned int c = 0; c < one.col; c++)
		{
			if (one.mArr[r * one.rowLength + c] != 
				two.mArr[r * two.rowLength + c]) return false;
		}
	}
	return true;
}

M_ operator+(const M_& one, const M_& two)
{
	assert(one.row == two.row && one.col == two.col);

	unsigned int newRow = one.row;
	unsigned int newCol = one.col;
	unsigned int newRowLength = one.rowLength;
	unsigned int newColLength = one.colHeight;
	float* tmpmArr = new float[one.mLength]{};

	for (unsigned int r = 0; r < newRowLength; r++)
	{
		for (unsigned int c = 0; c < newColLength; c++)
		{
			tmpmArr[r * newRowLength + c] = 
				one.mArr[r * newRowLength + c] + 
				two.mArr[r * newRowLength + c];
		}
	}
	M_ tmpM{ newRow, newCol, tmpmArr };
	delete[] tmpmArr;
	tmpmArr = nullptr;
	return tmpM;
}

M_ operator*(const M_& m, int scalar)
{
	unsigned int newRow = m.row;
	unsigned int newCol = m.col;
	unsigned int  tmpmLength = m.mLength;
	float* tmpmArr = new float[tmpmLength] {};

	for (unsigned int i = 0; i < tmpmLength; i++)
	{
		tmpmArr[i] = m.mArr[i] * static_cast<float>(scalar);
	}

	M_ tmpM{ newRow, newCol, tmpmArr };
	delete[] tmpmArr;
	tmpmArr = nullptr;
	return tmpM;

}

M_ operator*(const M_& one, const M_& two)
{
	assert(one.col == two.row);

	unsigned int newRow = one.row;
	unsigned int newCol = two.col;
	unsigned int newRowLength = newCol;
	unsigned int tmpmLength = newRow * newCol;
	float* tmpmArr = new float[tmpmLength];

	for (unsigned int r = 0; r < newRow; r++)
	{
		Vector tmpVR = one.makeV(VectorKind::VectorRow, r);
		for (unsigned int c = 0; c < newCol; c++)
		{
			Vector tmpVC = 
				two.makeV(VectorKind::VectorCol, c);
			tmpmArr[r * newRowLength + c] = dotpr(tmpVR, tmpVC);
		}
	}
	M_ tmpM{ newRow, newCol, tmpmArr };
	delete[] tmpmArr;
	tmpmArr = nullptr;
	return tmpM;
}

M_ Transpose(const M_& m)
{

	unsigned int newRow = m.col;
	unsigned int newCol = m.row;
	unsigned int newRowLength = newCol;

	unsigned int newLength = newRow * newCol;
	float* tmpmArr = new float[newLength];

	for (unsigned int r = 0; r < newRow; r++)
	{
		Vector tmpVC = m.makeV(VectorKind::VectorCol, r);
		auto tmpArray = tmpVC.VArr();
		for (unsigned int c = 0; c < newCol; c++)
		{
			tmpmArr[r * newRowLength + c] = tmpArray[c];
		}
	}

	M_ tmp{ newRow, newCol, tmpmArr };
	delete[] tmpmArr; tmpmArr = nullptr;
	return tmp;

}


M_ operator-(const M_& one, const M_& two)
{
	return one + (two * (-1));
}


#undef sizet

