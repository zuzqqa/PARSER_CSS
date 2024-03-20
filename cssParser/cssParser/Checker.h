#pragma once
#include <iostream>
#include "LinkedList.h"
#include "Sections_node.h"
#include<stdio.h>
#include <stdlib.h>

using namespace std;

String deleteWhitespacesSel(String css, int length, int buffer) {
	buffer = 0; int l = 0;

	for (int z = buffer; z < length; z++) {
		if (css[z] != ' ' && css[z] > ' ') {
			break;
		}
		else buffer++;
	}

	for (l = css.sizeS() - 1; l > 0; l--) { //front
		if (css[l] != ' ' && css[l] > ' ') {
			break;
		}
		else length--;
	}

	length = l - buffer + 1;
	return css.substr(buffer, length);
};

bool multipleSelectors(String& css) {
	int i = 0;

	while (css[i] != '{') {
		if (css[i] == ',') return true;
		i++;
	}
	return false;
};

int numOfSections(LinkedList<sectionNodes>& main_list) {
	int sum = 0;
	for (auto& nodes : main_list) {
		for (int i = 0; i < T; i++) {
			if (nodes.getSections()[i].getEmpty() == false) sum++;
		}
	}
	return sum;
};

bool isDigit(String a) {
	if (a[0] >= 48 && a[0] <= 57) return true;
	return false;
};

void numOfSelID(const String& a2, const String& a3, LinkedList<sectionNodes>& main_list, int index) {
	int k = 0, j = 0;

	LinkedList<selector> selectors;

	if (index > numOfSections(main_list)) return;

	for (auto& nodes : main_list) {
		for (j = 0; j < T; j++) {
			if (nodes.getSections()[j].getEmpty() == true) {}
			else {
				if (k == index - 1) {
					if (nodes.getSections()[j].getGlobal() == true) {
						cout << index << "," << a2.getStr() << "," << a3.getStr() << " == 0" << endl;
						return;
					}
					selectors = nodes.getSections()[j].getSelectors();
					cout << index << "," << a2.getStr() << "," << a3.getStr() << " == " <<
						nodes.getSections()[j].getSelectors().getListLen() << endl;
					return;
				}
				k++;
			}
		}
	}
};

void numOfAttrID(const String& a2, const String& a3, LinkedList<sectionNodes>& main_list, int index) {
	int k = 0, j = 0;

	LinkedList<attribute> attributes;

	if (index > numOfSections(main_list)) return;

	for (auto& nodes : main_list) {
		for (j = 0; j < T; j++) {

			if (nodes.getSections()[j].getEmpty() == 1) {}
			else {

				if (k == index - 1) {

					attributes = nodes.getSections()[j].getAttributes();

					cout << index << "," << a2.getStr() << "," << a3.getStr() << " == " <<
						nodes.getSections()[j].getAttributes().getListLen() << endl;

					return;
				}
				k++;
			}
		}
	}
};

void selOnID(const String& a3, LinkedList<sectionNodes>& main_list, int i, int j) {
	int a = 0, k = 0, l = 0;

	LinkedList<selector>selectors;

	if (i > numOfSections(main_list)) return;

	for (auto& nodes : main_list) {
		for (a = 0; a < T; a++) {

			if (nodes.getSections()[a].getEmpty() == true) {}
			else {
				if (k == i - 1) {

					selectors = nodes.getSections()[a].getSelectors();

					if (j > selectors.getListLen() || (nodes.getSections()[a].getGlobal() == 1)) return;

					for (auto& sel : selectors) {

						if (l == j - 1) {
							cout << i << "," << a3.getStr() << "," << j << " == " << sel.getSelector_name().getStr() << endl;
							return;
						}
						l++;
					}
				}
				k++;
			}
		}
	}
};

void attrName(const String& a2, const String& a3, LinkedList<sectionNodes>& main_list, int index) { //1, A, padding, wypisz dla i-tej sekcji wartoœæ atrybutu o nazwie n, jeœli nie ma takiego pomiñ;
	int k = 0, j = 0;
	LinkedList<attribute>attributes;


	for (auto& nodes : main_list) {
		for (j = 0; j < T; j++) {
			if (nodes.getSections()[j].getEmpty() == true) {}
			else {

				if (k == index - 1) {

					attributes = nodes.getSections()[j].getAttributes();

					for (auto& attr : attributes) {

						if (attr.getProperty().sizeS() == a3.sizeS()) {
							if (attr.getProperty() == a3) {
								cout << index << "," << a2.getStr() << "," << a3.getStr() << " == " << attr.getValue().getStr() << endl;
								return;
							}
						}
					}
				}
				k++;
			}
		}
	}
};

void attrCount(const String& a1, LinkedList<sectionNodes>& main_list) {
	int sum = 0;

	for (auto& nodes : main_list) {

		LinkedList<attribute> attributes;

		for (int i = 0; i < T; i++) {

			if (nodes.getSections()[i].getEmpty() == false) {
				attributes = nodes.getSections()[i].getAttributes();

				for (auto& attr : attributes) {

					if (attr.getProperty() == a1) {
						sum++;
						break;
					}
				}
			}
		}
	}
	cout << a1.getStr() << ",A," << "?" << " == " << sum << endl;
};

void selCount(const String& a1, LinkedList<sectionNodes>& main_list) {
	int sum = 0;

	for (auto& nodes : main_list) {
		LinkedList<selector> selectors;

		for (int i = 0; i < T; i++) {
			selectors = nodes.getSections()[i].getSelectors();

			for (auto& sel : selectors) {
				if (sel.getSelector_name() == a1) {
					sum++;
					break;
				}
			}
		}
	}
	cout << a1.getStr() << ",S," << "?" << " == " << sum << endl;
};

void attrVal(const String& a1, const String& a2, LinkedList<sectionNodes>& main_list) {
	int exist = 0;
	String k;

	LinkedList<selector> selectors;
	LinkedList<attribute> attributes;

	for (auto& nodes : main_list) {
		for (int i = 0; i < T; i++) {

			selectors = nodes.getSections()[i].getSelectors();
			attributes = nodes.getSections()[i].getAttributes();

			for (auto& sel : selectors) {
				if (sel.getSelector_name() == a1) {
					for (auto& at : attributes) {
						if (at.getProperty() == a2) {
							exist = 1;
							k = at.getValue();
						}
					}
				}
			}

		}
	}

	if (exist == 0) { return; }


	cout << a1.getStr() << ",E," << a2.getStr() << " == " << k.getStr() << endl;
};

void deleteFunc(int i, LinkedList<sectionNodes>& main_list) {
	int j = 0, k = 0, o = 0;

	LinkedList<selector> selectors;

	if (i - 1 > numOfSections(main_list)) return;

	for (auto& nodes : main_list) {
		for (j = 0; j < T; j++) {

			if (nodes.getSections()[j].getEmpty() == true) {}
			else {
				if (k == i - 1) {
					selectors = nodes.getSections()[j].getSelectors();
					nodes.getSections()[j].clear();

					cout << i << ",D,* == deleted" << endl;
					return;
				}
				k++;
			}
		}
	}
};

void deleteAttr(int i, const String& a3, LinkedList<sectionNodes>& main_list) {
	int j = 0, k = 0, u = 0, next = 0, del = 0;

	LinkedList<attribute> attributes;

	if (i - 1 > numOfSections(main_list)) return;

	for (auto& nodes : main_list) {
		for (j = 0; j < T; j++) {

			if (nodes.getSections()[j].getEmpty() == true) {}
			else {
				if (k == i - 1) {
					next = 0;
					attributes = nodes.getSections()[j].getAttributes();

					for (auto& attr : attributes) {
						if (attr.getProperty() == a3) {

							if (nodes.getSections()[j].getAttributes().getListLen() - 1 == 0) {
								nodes.getSections()[j].clear();
							}
							else nodes.getSections()[j].getAttributes().RemoveNode(u);

							del = 1;
							break;
						}
						u++;
					}
					break;
				}
				k++;
			}
		}
	}

	if (del == 1) cout << i << ",D," << a3.getStr() << " == deleted" << endl;
};

void splitCommand(String command, LinkedList<sectionNodes>& main_list) {
	int a = 0, b = 0, length, buffer = 0; 
	String a1, a2, a3;

	if (command[0] == '?') {
		cout << "? == " << numOfSections(main_list) << endl;
		return;
	}

	for (int i = 0; i < command.sizeS(); i++) {
		if (command[i] == ',') {
			length = i - buffer;
			a1 = command.substr(0, length);
			buffer = i + 1;
			break;
		}
	}

	if (isDigit(a1)) {
		a = atoi(a1.getStr());
	}

	for (int i = buffer; i < command.sizeS(); i++) {
		if (command[i] == ',') {
			length = i - buffer;
			a2 = command.substr(buffer, length);
			buffer = i + 1;
			break;
		}
	}

	if (isDigit(command.substr(buffer, command.sizeS()))) {
		b = atoi(command.substr(buffer, command.sizeS()).getStr());
	}
	else {
		a3 = command.substr(buffer, command.sizeS());
	}


	if (isDigit(a1) && a3 == "?") {
		if (a2 == "S") numOfSelID(a2, a3, main_list, a);
		else if (a2 == "A") numOfAttrID(a2, a3, main_list, a);
	}
	else if (isDigit(a1) && a2 == "S" && isDigit(command.substr(buffer, command.sizeS()))) {
		selOnID(a2, main_list, a, b);
	}
	else if (isDigit(a1) && a2 == "A" && !isDigit(a3)) {
		attrName(a2, a3, main_list, a);
	}
	else if (!isDigit(a1) && a2 == "A" && a3 == "?") {
		attrCount(a1, main_list);
	}
	else if (!isDigit(a1) && a2 == "S" && a3 == "?") {
		selCount(a1, main_list);
	}
	else if (!isDigit(a1) && a2 == "E" && !isDigit(a3)) {
		attrVal(a1, a3, main_list);
	}
	else if (isDigit(a1) && a2 == "D" && a3 == "*") {
		deleteFunc(a, main_list);
	}
	else if (isDigit(a1) && a2 == "D" && !isDigit(a3)) {
		deleteAttr(a, a3, main_list);
	}
};