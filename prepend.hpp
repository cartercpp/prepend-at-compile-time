#pragma once

#include <type_traits>
#include <concepts>

template <auto...>
struct value_sequence;

template <auto FirstValue, auto... OtherValues>
	requires (std::same_as<decltype(FirstValue), decltype(OtherValues)> && ...)
struct value_sequence<FirstValue, OtherValues...>
{
	template <auto Value>
	using append = value_sequence<FirstValue, OtherValues..., Value>;

	template <auto Value>
	using prepend = value_sequence<Value, FirstValue, OtherValues...>;
};

template <>
struct value_sequence<>
{
	template <auto Value>
	using append = value_sequence<Value>;

	template <auto Value>
	using prepend = value_sequence<Value>;
};

template <typename, auto, auto...>
struct prepend_impl;

template <typename Accumulated, auto PrependValue, auto FirstValue, auto... OtherValues>
struct prepend_impl<Accumulated, PrependValue, FirstValue, OtherValues...>
{
	using type = typename prepend_impl<
		std::conditional_t<
			PrependValue == FirstValue,
			typename Accumulated::template prepend<FirstValue>,
			typename Accumulated::template append<FirstValue>
		>,
		PrependValue,
		OtherValues...
	>::type;
};

template <typename Accumulated, auto PrependValue>
struct prepend_impl<Accumulated, PrependValue>
{
	using type = Accumulated;
};

template <auto PrependValue, auto... Values>
using prepend_all = typename prepend_impl<
	value_sequence<>,
	PrependValue,
	Values...
>::type;
