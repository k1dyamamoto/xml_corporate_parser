#include "commands.h"

CommandHistory cmdbuffer;

AddDepartmentCommand::AddDepartmentCommand(const std::string &_name) {
        name = _name;
        tree.push_back(new Department(_name));
}

void AddDepartmentCommand::undo() const {
        for (int i = 0; i < tree.size(); i++)
                if (tree[i]->get_name() == name)
                        tree.erase(tree.begin() + i);
}

DelDepartmentCommand::DelDepartmentCommand(const std::string &_name) {
        name = _name;
        for (int i = 0; i < tree.size(); i++)
                if (tree[i]->get_name() == _name)
                        tree.erase(tree.begin() + i);
}

void DelDepartmentCommand::undo() const {
        tree.push_back(new Department(name));
}

AddEmployeeCommand::AddEmployeeCommand(const std::string &_dep_name, const std::string &_name,
                                        const std::string &_surname, const std::string &_middlename,
                                        const std::string &_function, int salary) {
        name = _name;
        surname = _surname;
        middlename = _middlename;
        dep_name = _dep_name;
        for (auto &idx : tree)
                if (idx->get_name() == dep_name) {
                        idx->add_emp(new Employee(salary, name, surname,
                                                middlename, _function));
                        return;
                }
        std::cout << "department not found\n";
}

void AddEmployeeCommand::undo() const {
        for (int i = 0; i < tree.size(); i++)
                if (tree[i]->get_name() == dep_name)
                        tree[i]->del_emp(name, surname, middlename);
}

DelEmployeeCommand::DelEmployeeCommand(const std::string &_dep_name, const std::string &_name,
                                        const std::string &_surname, const std::string &_middlename) {

        for (int i = 0; i < tree.size(); i++)
                if (tree[i]->get_name() == _dep_name) {
                        salary = tree[i]->find_emp(_name, _surname, _middlename)->get_salary();
                        function = tree[i]->find_emp(_name, _surname, _middlename)->get_function();
                        name = _name;
                        surname = _surname;
                        middlename = _middlename;
                        tree[i]->del_emp(_name, _surname, _middlename);
                        return;
                }
        std::cout << "employee not found\n";
}

void DelEmployeeCommand::undo() const {
        for (auto &idx : tree)
                if (idx->get_name() == dep_name) {
                        idx->add_emp(new Employee(salary, name, surname,
                                                middlename, function));
                        return;
                }
        std::cout << "department not found\n";
}

void CommandHistory::push(Command *cmd) {
        hist.push_back(cmd);
}

void CommandHistory::pop() {
        if (hist.size()) {
                hist[hist.size() - 1]->undo();
                delete hist[hist.size() - 1];
                hist.pop_back();
        } else {
                std::cout << "nothing to undo\n";
        }
}

void print_handler() {
        for (auto &dep : tree) {
                std::cout << dep->get_name() << std::endl;
                auto emps = dep->get_emp();
                for (auto &emp : emps)
                        std::cout << "| " << emp->get_surname() << " "
                                << emp->get_name() << " "
                                << emp->get_middlename() << std::endl;
        }
}
