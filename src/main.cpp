#include <iostream>
#include <algorithm>
#include <filesystem>
#include <locale>
#include <fstream>
#include <regex>
#include <functional>

#include "caesar_cipher.hpp"

template<typename ReturnType>
auto validate_input(const std::string &message, const std::regex &pattern, const std::function<ReturnType(const std::string &)> &converter) {
	std::string input;
	
	do {
		std::cout << message;
		std::getline(std::cin, input);
	} while (!std::regex_match(input, pattern));

	return converter(input);
}

int main() {
	const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
	
	const std::regex numbers_pattern("^[0-9]$|^[1-3][0-9]$|^48$");
	const std::regex letters_pattern("^[a-z]+$", std::regex::icase);

	const auto num_converter = [](const std::string &s) { return std::stoi(s); };
	const auto str_converter = [](const std::string &s) {return s; };

	auto caesar_key = validate_input<int32_t>("\ninput key for a Caesar Cipher (numbers only):\t", numbers_pattern, num_converter);
	
	namespace fs = std::filesystem;
	fs::path file_path = "example.txt";

	std::ifstream input_file(file_path);

	if (!input_file.is_open()) return -1;

	std::string line;
	while (std::getline(input_file, line)) {
		
		line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
		
		if (line.empty()) continue;
		
		std::cout << "\n\nmessage: " << line << '\n';

		if (!std::regex_match(line, letters_pattern)) {
			std::cout << "wrong format!\n";
			continue;
		}

		std::transform(line.begin(), line.end(), line.begin(), ::tolower);
		
		auto encoded = caesar_cipher::encode<std::string, char8_t>(line, caesar_key, alphabet);
		auto decoded = caesar_cipher::decode<std::string, char8_t>(encoded, caesar_key, alphabet);

		std::cout << "\nCaesar Cipher:\t" << encoded;
		std::cout << "\nDecoded:\t" << decoded;
	}

	input_file.close();

	return 0;
}
