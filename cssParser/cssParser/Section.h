#pragma once
#include "LinkedList.h"
#include "Selector.h"
#include "Attributes.h"

class section {
	LinkedList<selector> selectors;
	LinkedList<attribute> attributes;
	int global = 0;
	bool empty = true;

public:
	section() = default;

	section(const LinkedList<selector>& sel, const LinkedList<attribute>& attr)
		: selectors(sel), attributes(attr), empty(false) {}

	section(const LinkedList<attribute>& attr) :attributes(attr), empty(false) {}

	LinkedList<selector>& getSelectors() {
		return selectors;
	};

	LinkedList<attribute>& getAttributes() {
		return attributes;
	};

	int getGlobal() const {
		return global;
	};

	bool getEmpty() const {
		return empty;
	};

	void setGlobal(int a) {
		this->global = a;
	};

	friend ostream& operator << (ostream& os, const section& sec) {
		for (LinkedList<selector>::Iterator it = sec.selectors.begin(); it != sec.selectors.end(); ++it) {
			os << *it << " " << endl;
		}
		for (LinkedList<attribute>::Iterator it = sec.attributes.begin(); it != sec.attributes.end(); ++it) {
			os << *it << " " << endl;
		}
		return os;
	};

	void clear() {
		this->selectors.clearList();
		this->attributes.clearList();
		this->empty = true;
		this->global = 0;
	};
};