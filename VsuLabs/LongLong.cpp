#include "LongLong.h"

namespace com
{
	void LongLong::print_bits(const void* buffer, int size)
	{
		unsigned char* p = (unsigned char*)buffer;
		//int size = sizeof(T);
		for (int i = 0; i < size; i++)
		{
			for (int j = 7; j >= 0; j--)
			{
				printf("%d", (p[size - 1 - i] >> j) & 1);
			}
			printf(" ");
		}
		//printf("\n%d <- 0\n", size - 1);
		printf("\n");
	}

	LongLong LongLong::abs(const LongLong& src)
	{
		LongLong res(src);

		if (res.get_sign() == -1)
		{
			if (res.minor == 0)
			{
				res.major = ~res.major + 1;
			}
			else
			{
				res.major = ~res.major;
				res.minor = ~res.minor + 1;
			}
		}
		// 1111 1111
		// 1000 0000

		return res;
	}

	LongLong LongLong::abs() const
	{
		return abs(*this);
	}

	halfint LongLong::get_high_bits(inttype value)
	{
		//0xff 0xff >> 8 -> 0x0 0xff
		return value >> sizeof(halfint) * 8;
	}

	halfint LongLong::get_low_bits(inttype value)
	{
		//0xff 0xff & 0x0 0xff -> 0x0 0xff
		return value & HALF_TYPE_MASK;
	}

	LongLong::LongLong()
		: major(0), minor(0)
	{}

	LongLong::LongLong(inttype number)
		: major(0), minor(number)
	{
		if (number < 0)
		{
			major = ~0;
		}
	}

	std::string LongLong::toString() const
	{
		std::stringstream ss;

		ss << std::hex << major << std::setfill('0') << std::setw(sizeof(inttype) * 2) << (minor);

		return ss.str();
	}

	std::string LongLong::toSignString() const
	{
		std::stringstream ss;

		sgn sign = get_sign();

		if (sign == MINUS)
		{
			ss << std::hex << '-' << ~major << std::setfill('0') << std::setw(sizeof(inttype) * 2) << (inttype)((~minor) + 1);
		}
		else
		{
			ss << std::hex << major << std::setfill('0') << std::setw(sizeof(inttype) * 2) << (minor);
		}

		return ss.str();
	}

	LongLong LongLong::operator+(const LongLong& right) const
	{
		LongLong temp;
		temp.minor = this->minor + right.minor;
		temp.major = this->major + right.major;

		if (temp.minor < std::max(this->minor, right.minor))
			temp.major++;

		if (temp.major < std::max(this->major, right.major))
			temp.overflow = true;

		return temp;
	}

	 LongLong LongLong::operator-(const LongLong& right) const
	{
		LongLong temp(right);
		return *this + (-temp);
	}

	 LongLong LongLong::operator*(const LongLong& right) const
	{
		LongLong res;

		const int int_fields_per_struct = 2;
		const int product_size = 2 * 2 * int_fields_per_struct;

		com::LongLong::sgn sign1 = this->get_sign();
		com::LongLong::sgn sign2 = right.get_sign();

		com::LongLong::sgn expected_res_sign = com::LongLong::sgn(sign1 * sign2);

		enum
		{
			LEFT, RIGHT
		};

		LongLong l = this->abs();
		LongLong r = right.abs();

		inttype bits[2][4] = {
			{
				LongLong::get_low_bits(l.minor) & HALF_TYPE_MASK,
				LongLong::get_high_bits(l.minor) & HALF_TYPE_MASK,
				LongLong::get_low_bits(l.major) & HALF_TYPE_MASK,
				LongLong::get_high_bits(l.major) & HALF_TYPE_MASK
			},
			{
				LongLong::get_low_bits(r.minor) & HALF_TYPE_MASK,
				LongLong::get_high_bits(r.minor) & HALF_TYPE_MASK,
				LongLong::get_low_bits(r.major) & HALF_TYPE_MASK,
				LongLong::get_high_bits(r.major) & HALF_TYPE_MASK
			},
		};

		inttype result[8] = { 0 };

		halfint carry = 0;

		for (int i = 0; i < 4; i++)
		{
			
			carry = 0;
			inttype l2 = bits[RIGHT][i];
			for (int j = 0; j < 4; j++)
			{
				inttype l1 = bits[LEFT][j];

				inttype prod = l1 * l2;

				result[j+i] += carry & HALF_TYPE_MASK;
				result[j+i] += prod & HALF_TYPE_MASK;

				carry = (prod >> sizeof(halfint) * 8) + (result[j + i] >> 8);
				result[j + i] &= HALF_TYPE_MASK;
			}
		}		

		res.minor = result[0] & HALF_TYPE_MASK | ((inttype)result[1] << 8);
		res.major = result[2] & HALF_TYPE_MASK | ((inttype)result[3] << 8);

		if (expected_res_sign == -1)
		{
			res = -res;
			//if (res.minor == 0)
			//{
			//	res.major = ~res.major + 1;
			//}
			//else
			//{
			//	res.major = ~res.major;
			//	res.minor = ~res.minor + 1;
			//}
		}

		return com::LongLong(this->toLL() * right.toLL());

		// случай переполнения, когда число меняет знак
		// 01000000 00000000 00000000 00000000
		// *
		// 00000000 00000000 00000000 00000010
		// -----------------------------------
		// 10000000 00000000 00000000 00000000
		com::LongLong::sgn res_sign = res.get_sign();

		if ((expected_res_sign != res_sign) || result[4] || result[5] || result[6] || result[7])
			res.overflow = true;

		return res;
	}

	LongLong LongLong::operator/(const LongLong& divisor) const
	{
		//LongLong res;

		//if (divisor > *this)
		//{
		//	return res;
		//}

		//while (*this > res * divisor)
		//	res = res + com::LongLong(1);

		//while (res * divisor > *this)
		//	res = res - com::LongLong(1);

		//return res;
		return this->toLL() / divisor.toLL();

	}

	bool LongLong::operator<(const LongLong& other) const
	{
		return !this->operator>=(other);
	}

	bool LongLong::operator>(const LongLong& other) const
	{
		if (this->major > other.major)
			return true;
		else if (this->major < other.major)
			return false;

		if (this->minor > other.minor)
			return true;
		
		return false;
	}

	bool LongLong::operator==(const LongLong& other) const
	{
		if (this->major == other.major && this->minor == other.minor)
			return true;

		return false;
	}

	bool LongLong::operator>=(const LongLong& other) const
	{
		return this->operator>(other) || this->operator==(other);
	}

	bool LongLong::operator<=(const LongLong& other) const
	{
		return this->operator<(other) || this->operator==(other);
	}

	LongLong& LongLong::operator-()
	{
		if (minor == 0)
		{
			major = ~major + 1;
		}
		else
		{
			major = ~major;
			minor = ~minor + 1;
		}

		return *this;
	}


	LongLong LongLong::operator%(const LongLong& r)
	{
		return LongLong();
	}

	long long LongLong::toLL() const
	{
		return std::stoll(this->toSignString(), nullptr, 16);
	}

}