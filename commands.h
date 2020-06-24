#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <string>
#include "objects.h"


void print_handler();

class Command
{
public:
        virtual void undo() const { std::cout << "compiler wants this...\n"; }
};

class CommandHistory
{
        std::vector<Command*> hist;
public:
        void push(Command *cmd);
        void pop();
};

extern CommandHistory cmdbuffer;

class AddDepartmentCommand : public Command
{
        std::string name;
public:
        AddDepartmentCommand(const std::string &_name);
        void undo() const override;
};

class AddEmployeeCommand : public Command
{
        std::string name;
        std::string surname;
        std::string middlename;
        std::string dep_name;
public:
        AddEmployeeCommand(const std::string &_dep_name, const std::string &_name,
                        const std::string &_surname, const std::string &_middlename,
                        const std::string &_function, int salary);
        void undo() const override;
};

class DelDepartmentCommand : public Command
{
        std::string name;
public:
        DelDepartmentCommand(const std::string &_name);
        void undo() const override;
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
                        const std::string &_surname, const std::string &_middlename);
        void undo() const override;
};


#endif
