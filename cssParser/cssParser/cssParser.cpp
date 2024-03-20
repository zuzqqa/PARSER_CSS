#include <iostream>
#include "String.h"
#include "Attributes.h"
#include "Selector.h"
#include "LinkedList.h"
#include "Section.h"
#include "Sections_node.h"
#include "Checker.h"

#define T 8

using namespace std;

void splitString(String& css, LinkedList<sectionNodes>& main_list) {
    int buffer = 0, p, length = 0, gl = 0;

    LinkedList<selector> selectors;
    LinkedList<attribute> attributes;

    if (css[0] == '{') {
        gl = 1;
    }
    else if (multipleSelectors(css) == true) {
        for (int i = 0; i < css.sizeS(); i++) {
            p = 0;

            if (css[i] == '{') {
                for (int j = i - 1; j > 0; j--) {
                    if (css[j] == ' ') {
                        i--;
                    }
                    else break;
                }

                length = i - buffer;

                for (auto& sel : selectors) {
                    if (sel.getSelector_name() == deleteWhitespacesSel(css.substr(buffer, length), length, buffer)) { p = 1; break; }
                }

                if (p == 0) selectors.AddLast(selector(deleteWhitespacesSel(css.substr(buffer, length), length, buffer).getStr()));

                buffer = i + 1;
                break;
            }
            else {
                if (css[i] == ',') {
                    length = i - buffer;

                    for (auto& sel : selectors) {
                        if (sel.getSelector_name() == deleteWhitespacesSel(css.substr(buffer, length - 1), length - 1, buffer)) { p = 1; break; }
                    }
                    if (p == 0) selectors.AddLast(selector(deleteWhitespacesSel(css.substr(buffer, length), length, buffer).getStr()));

                    if (css[i + 1] != ' ') buffer = i + 1;
                    else buffer = i + 2;
                }
            }
        }
    }
    else {
        buffer = 0;
        for (int i = 0; i < css.sizeS() - 1; i++) {
            if (css[i] == '{') {
                selectors.AddLast(selector(deleteWhitespacesSel(css.substr(buffer, i), i, buffer).getStr()));
                break;
            }
        }

    }

    String s1, s2;

    for (int i = 0; i < css.sizeS(); i++) {
        if (css[i] == '{') {
            for (int j = i; j < css.sizeS(); j++) {
                if (css[j] != ' ') {
                    buffer = j + 1;
                    break;
                }
            }
            break;
        }
    }

    for (int j = buffer; j < css.sizeS(); j++) {
        if (css[j] == ':') {
            p = 0;
            length = j - buffer;
            s2 = deleteWhitespacesSel(css.substr(buffer, length), length, buffer);

            if (css[j + 1] != ' ') buffer = j + 1;
            else buffer = j + 2;

            for (int k = buffer; k < css.sizeS(); k++) {
                if (css[k] == ';' || css[k] == '}') {
                    length = k - buffer;
                    s1 = deleteWhitespacesSel(css.substr(buffer, length), length, buffer);

                    for (auto& attr : attributes) { //powtarzajace sie atrybuty
                        if (attr.getProperty() == s2.getStr()) {
                            attr.setProperty(s2.getStr());
                            attr.setValue(s1.getStr());
                            p = 1;
                            break;
                        }
                    }

                    if (p == 0) attributes.AddLast(attribute(s2, s1));

                    j = k + 1;
                    buffer = k + 1;

                    break;
                }
            }
        }
    }

    section sections(selectors, attributes);
    if (gl == 1) sections.setGlobal(1);

    sectionNodes secN(sections);

    if (main_list.getLast() == nullptr) main_list.AddLast(secN);
    else {
        if (main_list.getLast()->data.getTaken() == 8) {
            main_list.AddLast(secN);
        }
        else {
            main_list.getLast()->data.push_back(sections);
        }
    };
};

void getCSS(String& css, LinkedList<sectionNodes>& main_list) {
    while (true) {
        css.Sdelete();
        css.getLine();

        if (css.ifEOF() == true) break;

        if (css == "????") break;

        splitString(css, main_list);
    }
};

void getCommands(String& css, LinkedList<sectionNodes>& main_list) {
    while (true) {
        css.Sdelete();
        css.getCommand();

        if (css == "****") {
            return;
        }
        else if (css == "?") {
            cout << "? == " << numOfSections(main_list) << endl;
        }
        else if (css.ifEOF() == true) {
            if (css.getEOF2() == true)
                cout << "? == " << numOfSections(main_list) << endl;
            css.setEOF1(1);
            return;
        }
        else {
            splitCommand(css, main_list);
        }
    }
};

int main() {
    LinkedList<sectionNodes> main_list;
    String css;

    while (true) {
        getCSS(css, main_list);

        getCommands(css, main_list);
        if (css.getEOF1() == 1) break;
    };

    return 0;
};