/* not yet son

#include <string>

void add_handler()
{
        std::string type;
        std::cin >> type;
        if (type == "department") {
                std::string name;
                std::cin >> name;
                tree.push_back(new Department(name));
        }

        if (type == "employee") {
                std::string surname, name, middlename, dep_name;
                int salary, dep_idx;
                std::cin >> dep_name >> surname >> name >> middlename >> salary;
                for (int i = 0; i < tree.size(); i++)
                        if (tree[i]->get_name() == dep_name)
                                dep_idx = i;

                tree[dep_idx]->add_emp(new Employee(emp_salary, emp_name,
                                                emp_surname, emp_middlename));
        }
} */
