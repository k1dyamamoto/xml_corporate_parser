#include "objects.h"

std::vector<Department*> tree;

Employee::Employee(int _salary, const std::string &_name, const std::string &_surname,
        const std::string &_middlename, const std::string &_function) {
        salary = _salary;
        surname = _surname;
        name = _name;
        middlename = _middlename;
        function = _function;
}

int Employee::get_salary() const {
        return salary;
}

std::string Employee::get_name() const {
        return name;
}

std::string Employee::get_middlename() const {
        return middlename;
}

std::string Employee::get_surname() const {
        return surname;
}

std::string Employee::get_function() const {
        return function;
}

Department::Department(const std::string &_name) {
        emp_num = 0;
        avg_sal = 0;
        name = _name;
}

void Department::add_emp(Employee * emp) {
        emp_vec.push_back(emp);
        emp_num++;
        avg_sal = (float)(avg_sal + emp->get_salary()) / emp_num;
}

void Department::del_emp(const std::string &_name,
                        const std::string &_surname,
                        const std:: string &_middlename) {

        for (int i = 0; i < emp_vec.size(); i++) {
                if (emp_vec[i]->get_name() == _name &&
                    emp_vec[i]->get_surname() == _surname &&
                    emp_vec[i]->get_middlename() == _middlename) {

                            emp_vec.erase(emp_vec.begin() + i);
                            return;
                }
        }
        std::cout << "Error\n";
}

Employee *Department::find_emp(const std::string &_name,
                        const std::string &_surname,
                        const std:: string &_middlename) const {

        for (int i = 0; i < emp_vec.size(); i++) {
                if (emp_vec[i]->get_name() == _name &&
                    emp_vec[i]->get_surname() == _surname &&
                    emp_vec[i]->get_middlename() == _middlename) {
                            return emp_vec[i];
                }
        }
}

int Department::get_num() const {
        return emp_num;
}

float Department::get_avg() const {
        return avg_sal;
}

std::string Department::get_name() const {
        return name;
}
const std::vector<Employee*> &Department::get_emp() const {
        return emp_vec;
}
