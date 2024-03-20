#pragma once
#include "Section.h"

#define T 8

class sectionNodes {
	section sections[T];
	int taken = 0;
public:
	sectionNodes() {
		for (int i = 0; i < T; i++) {
			this->sections[i] = section();
		}
		this->taken = 0;
	};

	explicit sectionNodes(const section& sec) {
		this->sections[taken] = sec;
		taken++;
	};

	section* getSections() {
		return sections;
	};

	int getTaken() const {
		return this->taken;
	};

	void decrementTaken() {
		this->taken--;
	};

	void push_back(const section& sec) {
		this->sections[taken] = sec;
		this->taken++;
	};

	friend ostream& operator << (ostream& os, const sectionNodes& secN) {
		for (int i = 0; i < secN.taken; i++) {
			os << secN.sections[i];
		}
		return os;
	};

	~sectionNodes() {
		for (int i = 0; i < T; i++) {
			this->sections[i] = section();
		}
		this->taken = 0;
	};
};