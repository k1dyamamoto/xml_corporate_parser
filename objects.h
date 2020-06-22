#ifndef OBJECTS_H
#define OBJECTS_H

#include <vector>
#include <string>

class Element
{
public:
        void relocate(Element *node);
        void remove();
};

class Employee: Element
{
        int salary;
        std::string name, surname, middlename;
public:
        Employee(int _salary, const std::string &_name, std::string &_surname,
                std::string &_middlename);
        int get_salary() const;
        std::string get_name() const;
        std::string get_surname() const;
        std::string get_middlename() const;
};

class Department: Element
{
        std::string name;
        int emp_num;
        float avg_sal;
        std::vector<Employee*> emp_vec;
public:
        Department(const std::string &_name);
        void add_emp(Employee *emp);
        std::string get_name() const;
        const std::vector<Employee*> &get_emp() const;
        ~Department();
};

#endif
