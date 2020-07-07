#include "objects.h"
#include "commands.h"
#include "xmlparser.h"


int main()
{
        std::string command, inp;
        std::vector<Department*> tree;
        std::cout << "Enter xml file name:\n";
        std::cin >> inp;
        read_xml(inp, tree);
        while (std::cin >> command) {
                if  (command == "add") {
                        std::string type;
                        std::cin >> type;
                        if (type == "department") {
                                std::string name;
                                std::cout << "Enter name:\n";
                                std::cin.ignore(1, '\n');
                                getline(std::cin, name);
                                cmdbuffer.push(new AddDepartmentCommand(name, tree));
                        } else if (type == "employee") {
                                std::string name, surname, middlename,
                                                dep_name, function;
                                int salary;
                                std::cout << "Enter department:\n";
                                std::cin.ignore(1, '\n');
                                std::getline(std::cin, dep_name);
                                std::cout << "Enter name:\n";
                                std::cin >> name;
                                std::cout << "Enter surname:\n";
                                std::cin >> surname;
                                std::cout << "Enter middlename:\n";
                                std::cin >> middlename;
                                std::cout << "Enter salary:\n";
                                std::cin >> salary;
                                std::cout << "Enter function:\n";
                                std::cin >> function;
                                cmdbuffer.push(new AddEmployeeCommand(dep_name, name,
                                                surname, middlename, function, salary, tree));
                        }
                } else if (command == "print") {
                        print_handler(tree);
                } else if (command == "quit") {
                        break;
                } else if (command == "undo") {
                        cmdbuffer.pop(tree);
                } else if (command == "redo") {
                        cmdbuffer.redo(tree);
                } else if (command == "delete") {
                        std::string type;
                        std::cin >> type;
                        if (type == "department") {
                                std::string name;
                                std::cout << "Enter name:\n";
                                std::cin.ignore(1, '\n');
                                getline(std::cin, name);
                                cmdbuffer.push(new DelDepartmentCommand(name, tree));
                        } else if (type == "employee") {
                                std::string name, surname, middlename, dep_name;
                                int salary;
                                std::cout << "Enter department:\n";
                                std::cin.ignore(1, '\n');
                                getline(std::cin, dep_name);
                                std::cout << "Enter name:\n";
                                std::cin >> name;
                                std::cout << "Enter surname:\n";
                                std::cin >> surname;
                                std::cout << "Enter middlename:\n";
                                std::cin >> middlename;
                                cmdbuffer.push(new DelEmployeeCommand(dep_name, name,
                                                surname, middlename, tree));
                        }
                } else if (command == "write") {
                        std::string wf;
                        std::cout << "Enter output filename: \n";
                        std::cin >> wf;
                        writexml(wf, tree);
                } else {
                        std::cout << "unknown command\n";
                }
        }

        for (auto idx : tree)
                delete idx;
        tree.clear();

}
