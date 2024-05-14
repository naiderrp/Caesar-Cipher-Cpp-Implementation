#pragma once

#include <string>

template<typename ContainerType, typename ValueType>
concept HasFindMethod = requires(ContainerType a, ValueType b)
{
	{ a.find(b) } -> std::same_as<size_t>;
};

struct caesar_cipher {

	template<typename StrType, typename ValueType> requires HasFindMethod<StrType, ValueType>
	[[ nodiscard ]]
	static constexpr auto encode(const StrType& original_message, uint32_t key, const StrType& alphabet) {
		StrType result;
		auto alphabet_size = alphabet.size();

		for (const auto& letter : original_message) {

			auto index = alphabet.find(letter);
			auto encoded_index = (index + key) % alphabet_size;
			auto encoded_letter = alphabet[encoded_index];

			result.push_back(encoded_letter);
		}

		return result;
	}

	template<typename StrType, typename ValueType> requires HasFindMethod<StrType, ValueType>
	[[ nodiscard ]]
	static constexpr auto decode(const StrType& encoded_message, uint32_t key, const StrType& alphabet) {
		StrType result;
		auto alphabet_size = alphabet.size();

		for (const auto& letter : encoded_message) {

			auto index = alphabet.find(letter);
			auto decoded_index = (index - key + alphabet_size) % alphabet_size;
			auto decoded_letter = alphabet[decoded_index];

			result.push_back(decoded_letter);
		}

		return result;
	}
};
