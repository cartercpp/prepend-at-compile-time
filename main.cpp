#include <concepts>
#include "prepend.hpp"

int main()
{
	// prepend all 0s in this parameter pack:
	using values = prepend_all<
		0,
		0, 1, 0, 1, 0, 1
	>;

	static_assert(std::same_as<values, value_sequence<0, 0, 0, 1, 1, 1>>, "x");
}
