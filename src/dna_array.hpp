#ifndef DNA_ARRAY_HPP
#define DNA_ARRAY_HPP

/*
 * Copyright (c) 2016 David Seifert
 * 	
 * This file is part of ngshmmalign
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <algorithm>
#include <array>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

extern const int col_width;

template <typename T, std::size_t N>
class dna_array
{
private:
	typedef std::array<T, N> array_type;
	array_type m_array;

public:
	typedef typename array_type::size_type size_type;
	typedef typename array_type::value_type value_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;

	// rule-of-5 ctors
	dna_array() = default;
	dna_array(const dna_array& other) = default;
	dna_array(dna_array&& other) = default;
	dna_array& operator=(const dna_array& other) = default;
	dna_array& operator=(dna_array&& other) = default;

	// conversion ctor
	template <typename V, std::size_t M>
	friend class dna_array;

	template <typename V>
	dna_array(const dna_array<V, N>& v) noexcept
	{
		std::transform(
			v.m_array.begin(),
			v.m_array.end(),
			this->m_array.begin(),
			[](const V& i)
			{
				return static_cast<T>(i);
			});
	}
	template <typename V, std::size_t M>
	dna_array(dna_array<V, M>& v) noexcept : dna_array(static_cast<const dna_array<V, M>&>(v)) {}

	// aggregate initialization
	template <typename... U>
	dna_array(U&&... u) noexcept : m_array{ { std::forward<U>(u)... } } {}

	// normal indexing
	inline const_reference operator[](size_type) const noexcept;
	inline reference operator[](size_type) noexcept;

	// DNA base indexing
	inline const_reference operator[](char) const noexcept;
	inline reference operator[](char) noexcept;

	// output
	friend std::ostream& operator<<(std::ostream& output, const dna_array& dna_array_) noexcept
	{
		return output
			<< std::left << std::setw(3) << "A:" << std::right << std::setw(col_width) << dna_array_['A'] << '\t'
			<< std::left << std::setw(3) << "C:" << std::right << std::setw(col_width) << dna_array_['C'] << '\t'
			<< std::left << std::setw(3) << "G:" << std::right << std::setw(col_width) << dna_array_['G'] << '\t'
			<< std::left << std::setw(3) << "T:" << std::right << std::setw(col_width) << dna_array_['T'] << '\t'
			<< std::left << std::setw(3) << "N:" << std::right << std::setw(col_width) << dna_array_['N']
			<< '\n';
	}
};

// normal indexing
template <typename T, std::size_t N>
inline typename dna_array<T, N>::const_reference dna_array<T, N>::operator[](size_type pos) const noexcept
{
#ifndef NDEBUG
	assert((0 <= pos) && (pos < 4));
#endif
	return m_array[pos];
}

template <typename T, std::size_t N>
inline typename dna_array<T, N>::reference dna_array<T, N>::operator[](size_type pos) noexcept
{
	return const_cast<reference>(static_cast<const dna_array<T, N>&>(*this)[pos]);
}

// DNA base indexing
template <typename T, std::size_t N>
inline typename dna_array<T, N>::const_reference dna_array<T, N>::operator[](char base) const noexcept
{
	static_assert((N == 2) || (N == 5), "N has to be either 2 or 5! Exiting...\n");
	switch (N)
	{
		case 2:
			switch (base)
			{
				case 'A':
				case 'C':
				case 'G':
				case 'T':
					return m_array[static_cast<size_type>(0)];
				case 'N': // ambiguous base
					return m_array[static_cast<size_type>(1)];
				default:
					throw std::invalid_argument(std::string(1, base) + std::string(" is an unknown base! Exiting...\n"));
			}
			break;

		case 5:
			switch (base)
			{
				case 'A':
					return m_array[static_cast<size_type>(0)];
				case 'C':
					return m_array[static_cast<size_type>(1)];
				case 'G':
					return m_array[static_cast<size_type>(2)];
				case 'T':
					return m_array[static_cast<size_type>(3)];
				case 'N': // ambiguous base
					return m_array[static_cast<size_type>(4)];
				default:
					throw std::invalid_argument(std::string(1, base) + std::string(" is an unknown base! Exiting...\n"));
			}
			break;
	}
}

template <typename T, std::size_t N>
inline typename dna_array<T, N>::reference dna_array<T, N>::operator[](char base) noexcept
{
	return const_cast<reference>(static_cast<const dna_array<T, N>&>(*this)[base]);
}

#endif /* DNA_ARRAY_HPP */