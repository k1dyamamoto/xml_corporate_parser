#include "commands.h"

CommandHistory cmdbuffer;

AddDepartmentCommand::AddDepartmentCommand(const std::string &_name, std::vector<Department*> &tree) {
        name = _name;
        tree.push_back(new Department(_name));
}

void AddDepartmentCommand::undo(std::vector<Department*> &tree) const {
        for (int i = 0; i < tree.size(); i++)
                if (tree[i]->get_name() == name)
                        tree.erase(tree.begin() + i);
}

void AddDepartmentCommand::redo(std::vector<Department*> &tree) const {
        tree.push_back(new Department(name));
}

DelDepartmentCommand::DelDepartmentCommand(const std::string &_name, std::vector<Department*> &tree) {
        name = _name;
        for (int i = 0; i < tree.size(); i++)
                if (tree[i]->get_name() == _name)
                        tree.erase(tree.begin() + i);
}

void DelDepartmentCommand::undo(std::vector<Department*> &tree) const {
        tree.push_back(new Department(name));
}

void DelDepartmentCommand::redo(std::vector<Department*> &tree) const {
        for (int i = 0; i < tree.size(); i++)
                if (tree[i]->get_name() == name)
                        tree.erase(tree.begin() + i);
}

AddEmployeeCommand::AddEmployeeCommand(const std::string &_dep_name, const std::string &_name,
                                        const std::string &_surname, const std::string &_middlename,
                                        const std::string &_function, int _salary, std::vector<Department*> &tree) {
        name = _name;
        surname = _surname;
        middlename = _middlename;
        dep_name = _dep_name;
        function = _function;
        salary = _salary;
        for (auto &idx : tree)
                if (idx->get_name() == dep_name) {
                        idx->add_emp(new Employee(salary, name, surname,
                                                middlename, _function));
                        return;
                }
        std::cout << "department not found\n";
}

void AddEmployeeCommand::undo(std::vector<Department*> &tree) const {
        for (int i = 0; i < tree.size(); i++)
                if (tree[i]->get_name() == dep_name)
                        tree[i]->del_emp(name, surname, middlename);
}


void AddEmployeeCommand::redo(std::vector<Department*> &tree) const {
        for (auto &idx : tree)
                if (idx->get_name() == dep_name) {
                        idx->add_emp(new Employee(salary, name, surname,
                                                middlename, function));
                        return;
                }
        std::cout << "department not found\n";
}


DelEmployeeCommand::DelEmployeeCommand(const std::string &_dep_name, const std::string &_name,
                                        const std::string &_surname, const std::string &_middlename,
                                        std::vector<Department*> &tree) {

        for (int i = 0; i < tree.size(); i++)
                if (tree[i]->get_name() == _dep_name) {
                        dep_name = _dep_name;
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

void DelEmployeeCommand::undo(std::vector<Department*> &tree) const {
        for (auto &idx : tree)
                if (idx->get_name() == dep_name) {
                        idx->add_emp(new Employee(salary, name, surname,
                                                middlename, function));
                        return;
                }
        std::cout << "department not found\n";
}

void DelEmployeeCommand::redo(std::vector<Department*> &tree) const {
        for (int i = 0; i < tree.size(); i++)
                if (tree[i]->get_name() == dep_name) {
                        tree[i]->del_emp(name, surname, middlename);
                        return;
                }
        std::cout << "employee not found\n";
}

void CommandHistory::push(Command *cmd) {
        hist.push_back(cmd);
        cur = hist.size();
}

void CommandHistory::pop(std::vector<Department*> &tree) {
        if (cur) {
                hist[--cur]->undo(tree);
        } else {
                std::cout << "nothing to undo\n";
        }
}

void CommandHistory::redo(std::vector<Department*> &tree) {
        if (cur < hist.size()) {
                hist[cur++]->redo(tree);
        } else {
                std::cout << "nothing to redo\n";
        }
}

void print_handler(const std::vector<Department*> &tree) {
        for (auto &dep : tree) {
                std::cout << dep->get_name() << std::endl;
                auto emps = dep->get_emp();
                for (auto &emp : emps)
                        std::cout << "| " << emp->get_surname() << " "
                                << emp->get_name() << " "
                                << emp->get_middlename() << std::endl;
        }
}
