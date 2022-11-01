#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP
# include <cstddef>

namespace ft
{
	template<class T, T v>
	struct integral_constant
	{
		typedef T value_type;
		typedef integral_constant<T,v> type;

		static const T value = v;
	
		operator T()
		{
			return v;
		}
	};

	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;

	template<typename> struct is_integral: false_type {};

	template<> struct is_integral<bool>: true_type {};
	template<> struct is_integral<char>: true_type {};
	template<> struct is_integral<wchar_t>: true_type {};
	template<> struct is_integral<signed char>: true_type {};
	template<> struct is_integral<short int>: true_type {};
	template<> struct is_integral<int>: true_type {};
	template<> struct is_integral<long int>: true_type {};
	template<> struct is_integral<long long int>: true_type {};
	template<> struct is_integral<unsigned char>: true_type {};
	template<> struct is_integral<unsigned short int>: true_type {};
	template<> struct is_integral<unsigned int>: true_type {};
	template<> struct is_integral<unsigned long int>: true_type {};
	template<> struct is_integral<unsigned long long int>: true_type {};

	template<> struct is_integral<const bool>: true_type {};
	template<> struct is_integral<const char>: true_type {};
	template<> struct is_integral<const wchar_t>: true_type {};
	template<> struct is_integral<const signed char>: true_type {};
	template<> struct is_integral<const short int>: true_type {};
	template<> struct is_integral<const int>: true_type {};
	template<> struct is_integral<const long int>: true_type {};
	template<> struct is_integral<const long long int>: true_type {};
	template<> struct is_integral<const unsigned char>: true_type {};
	template<> struct is_integral<const unsigned short int>: true_type {};
	template<> struct is_integral<const unsigned int>: true_type {};
	template<> struct is_integral<const unsigned long int>: true_type {};
	template<> struct is_integral<const unsigned long long int>: true_type {};

	template<> struct is_integral<volatile bool>: true_type {};
	template<> struct is_integral<volatile char>: true_type {};
	template<> struct is_integral<volatile wchar_t>: true_type {};
	template<> struct is_integral<volatile signed char>: true_type {};
	template<> struct is_integral<volatile short int>: true_type {};
	template<> struct is_integral<volatile int>: true_type {};
	template<> struct is_integral<volatile long int>: true_type {};
	template<> struct is_integral<volatile long long int>: true_type {};
	template<> struct is_integral<volatile unsigned char>: true_type {};
	template<> struct is_integral<volatile unsigned short int>: true_type {};
	template<> struct is_integral<volatile unsigned int>: true_type {};
	template<> struct is_integral<volatile unsigned long int>: true_type {};
	template<> struct is_integral<volatile unsigned long long int>: true_type {};

}

#endif