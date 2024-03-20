#pragma once
#include <iostream>
#include "String.h"

class attribute {
	String property;
	String value;
public:
	attribute() = default;

	attribute(const String& str, const String& val) : property(str), value(val) {};

	explicit attribute(const String& property)
		:property(property){};

	String getProperty() {
		return this->property;
	};

	String getValue() const{
		return value;
	};

	void setProperty(const char* str) {
		this->property = str;
	};

	void setValue(const char* str) {
		this->value = str;
	};

	friend ostream& operator << (ostream& os, const attribute& atr) {
		os << "Property: " << atr.property.getStr() << " Value: " << atr.value.getStr();
		return os;
	};
};