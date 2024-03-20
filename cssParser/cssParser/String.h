#pragma once
#include <iostream>
#include <cstring>
#include <cctype>
#include "LinkedList.h"

#define _CRT_SECURE_NO_WARNINGS

class String {
	char* data;
	int size;
	bool eof = false;
	bool eof1 = false;
	bool eof2 = false;
public:
	String() {
		data = new char[1];
		size = 0;
		eof = false;

		data[0] = '\0';
	};

	String(const char* str) {
		data = nullptr;
		size = 0;

		if (str != nullptr) {
			int length = strlen(str);

			char* strData = new char[length + 1];

			for (size_t i = 0, j = 0; i < length; i++) {
				if (str[i] != '\n') {
					strData[j] = str[i];

					j++;
					size++;
				}
			}

			strData[size] = '\0';

			data = strData;
		}
		else { //default wartosci
			data = new char[1];
			data[0] = '\0';
		}
	};

	String& operator=(const String& other) {
		if (this != &other) {

			if (data != nullptr) {
				data = nullptr;
			}

			size = other.size;
			data = new char[size + 1];

			memcpy_s(data, size + 1, other.data, size + 1);
		}
		return *this;
	};

	String& operator+(const String& other) const {
		String result;

		result.size = size + other.size;
		result.data = new char[result.size + 1];

		strcpy(result.data, data);
		strcat(result.data, other.data);

		return result;
	};

	char& operator[](int index) const {
		return data[index];
	};

	bool operator==(const String& other) const {
		return (size == other.size) && (strcmp(data, other.data) == 0);
	};

	bool operator!=(const String& other) const {
		return !(*this == other);
	};

	void setEOF1(int a) {
		this->eof1 = a;
	};

	char* getStr() const {
		return data;
	}

	bool getEOF1() const {
		return this->eof1;
	};

	bool getEOF2() const {
		return this->eof2;
	};

	int sizeS() const {
		return size;
	};

	bool ifEOF() const {
		return this->eof;
	};

	String substr(int buffer, int length) {
		char* newString = new char[length + 1];

		memcpy(newString, &data[buffer], length);

		newString[length] = '\0';

		return String(newString);
	};

	void getLine() {
		char* input = new char[1024];
		int i = 0, count = 0;

		char c = 'p';

		while (!(cin.eof()) && c != 125 && i < 1023) {
			c = cin.get();

			if (cin.eof()) {
				this->eof = true;
				delete[] input;
				return;
			}

			if (c != 10 && c != 9) {
				input[i++] = c;
				size++;
			}

			if (input[i - 1] == '?') {
				count++;
				if (count == 4) {
					break;
				}
			}
			else count = 0;
		}
		input[i] = '\0';

		if (c == char(26)) exit;
		data = new char[strlen(input) + 1];

		strcpy(data, input);
		delete[] input;
	};

	void getCommand() {
		char* input = new char[1024];
		int i = 0;

		char c = 'p';

		while (!(cin.eof()) && c != '\n' && i < 1023) {
			c = cin.get();


			if (c != 10 && c != 9 && c != '\n') {
				input[i++] = c;
				size++;
			}

			if (cin.eof() && input[0] == '?') {
				this->eof = true;
				this->eof2 = true;
				delete[] input;
				return;
			}
			if (cin.eof()) {
				this->eof = true;
				delete[] input;
				return;
			}

		}
		input[i] = '\0';

		if (c == char(26)) exit;
		data = new char[strlen(input) + 1];

		strcpy(data, input);
		delete[] input;
	};

	void Sdelete() {
		if (data != nullptr) {
			delete[] data;

			size = 0;
			data = new char[1];
			data[0] = '\0';
		}
	};

	~String() {
		if (data != nullptr) {
			data = nullptr;
		}
	};
};
