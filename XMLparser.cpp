#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "objects.h"

std::string cut(std::string &s)
{
        int p1 = 1 + s.find('>');
        int p2 = s.find('<', p1);
        return s.substr(p1, p2 - p1);
}

bool contains(const std::string &str, const std::string &sub)
{
        return (str.find(sub) != std::string::npos);
}

int main()
{
        std::ifstream xml("example.xml");
        std::string curline;
        std::vector<Department*> tree;
        int cur_dept = -1;
        while (getline(xml, curline)) {
                if (contains(curline, "<department ")) {
                        int begin = curline.find('"');
                        std::string name = "";
                        while (curline[++begin] != '"')
                                name += curline[begin];
                        tree.push_back(new Department(name));
                        cur_dept++;
                } else if (contains(curline, "<employment>")) {
                        std::string emp_surname, emp_name,
                        emp_middlename, emp_function;
                        int emp_salary;

                        for (int i = 0; i < 5; ++i) {
                                getline(xml, curline);
                                if (contains(curline, "<name>")) {
                                        emp_name = cut(curline);
                                } else if (contains(curline, "<surname>")) {
                                        emp_surname = cut(curline);
                                } else if (contains(curline, "<middleName>")) {
                                        emp_middlename = cut(curline);
                                } else if (contains(curline, "<function>")) {
                                        emp_function = cut(curline);
                                } else if (contains(curline, "<salary>")) {
                                        emp_salary = std::stoi(cut(curline));
                                }
                        }
                        tree[cur_dept]->add_emp(new Employee(emp_salary, emp_name,
                                                        emp_surname, emp_middlename));
                }
        }

        for (auto &dep : tree) {
                std::cout << dep->get_name() << std::endl;
                auto emps = dep->get_emp();
                for (auto &emp : emps)
                        std::cout << "| " << emp->get_surname() << " "
                                << emp->get_name() << " "
                                << emp->get_middlename() << std::endl;
        }
        /*      not yet son
        std::string command;
        std::vector<std::string> command_buffer;
        while (std::cin >> command) {
                if (command == "add") {
                        add_handler();
                }
        }*/

        for (auto &idx : tree)
                delete idx;
}
