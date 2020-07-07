#ifndef OBJECTS_H
#define OBJECTS_H

#include <vector>
#include <string>
#include <iostream>


class Employee
{
        int salary;
        std::string name, surname, middlename, function;
public:
        Employee(int _salary, const std::string &_name, const std::string &_surname,
                const std::string &_middlename, const std::string &_function);
        int get_salary() const;
        std::string get_name() const;
        std::string get_surname() const;
        std::string get_middlename() const;
        std::string get_function() const;

};

class Department
{
        std::string name;
        int emp_num;
        float avg_sal;
        std::vector<Employee*> emp_vec;
public:
        Department(const std::string &_name);
        void add_emp(Employee *emp);
        int get_num() const;
        float get_avg() const;
        void del_emp(const std::string &name,
                const std::string &surname, const std:: string &middlename);
        Employee *find_emp(const std::string &_name,
                                        const std::string &_surname,
                                        const std:: string &_middlename) const;
        std::string get_name() const;
        const std::vector<Employee*> &get_emp() const;
};


#endif
