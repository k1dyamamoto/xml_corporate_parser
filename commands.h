#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <string>
#include "objects.h"


void print_handler(const std::vector<Department*> &tree);

class Command
{
public:
        virtual void undo(std::vector<Department*> &tree) const { std::cout << "compiler wants this...\n"; }
        virtual void redo(std::vector<Department*> &tree) const { std::cout << "compiler wants this...\n"; }
};

class CommandHistory
{
        std::vector<Command*> hist;
        int cur = 0;
public:
        void push(Command *cmd);
        void pop(std::vector<Department*> &tree);
        void redo(std::vector<Department*> &tree);
};

extern CommandHistory cmdbuffer;

class AddDepartmentCommand : public Command
{
        std::string name;
public:
        AddDepartmentCommand(const std::string &_name, std::vector<Department*> &tree);
        void undo(std::vector<Department*> &tree) const override;
        void redo(std::vector<Department*> &tree) const override;
};

class AddEmployeeCommand : public Command
{
        std::string name;
        std::string surname;
        std::string middlename;
        std::string dep_name;
        std::string function;
        int salary;
public:
        AddEmployeeCommand(const std::string &_dep_name, const std::string &_name,
                        const std::string &_surname, const std::string &_middlename,
                        const std::string &_function, int salary,  std::vector<Department*> &tree);
        void undo(std::vector<Department*> &tree) const override;
        void redo(std::vector<Department*> &tree) const override;
};

class DelDepartmentCommand : public Command
{
        std::string name;
public:
        DelDepartmentCommand(const std::string &_name, std::vector<Department*> &tree);
        void undo(std::vector<Department*> &tree) const override;
        void redo(std::vector<Department*> &tree) const override;
};

class DelEmployeeCommand : public Command
{
        std::string name;
        std::string surname;
        std::string middlename;
        std::string dep_name;
        std::string function;
        int salary;
public:
        DelEmployeeCommand(const std::string &_dep_name, const std::string &_name,
                        const std::string &_surname, const std::string &_middlename,
                        std::vector<Department*> &tree);
        void undo(std::vector<Department*> &tree) const override;
        void redo(std::vector<Department*> &tree) const override;
};


#endif
