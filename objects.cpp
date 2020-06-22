#include "objects.h"

Employee::Employee(int _salary, const std::string &_name, std::string &_surname,
        std::string &_middlename) {
        salary = _salary;
        surname = _surname;
        name = _name;
        middlename = _middlename;
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

std::string Department::get_name() const {
        return name;
}

const std::vector<Employee*> &Department::get_emp() const {
        return emp_vec;
}


Department::~Department() {
        for (auto &idx : emp_vec)
                delete idx;
}
