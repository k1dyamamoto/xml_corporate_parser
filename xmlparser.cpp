#include "xmlparser.h"


std::string cut(std::string &s)
{
        int p1 = 1 + s.find('>');
        int p2 = s.find('<', p1);
        return s.substr(p1, p2 - p1);
}

bool contains(const std::string &str, const std::string &sub)
{
        return (str.find(sub) != std::string::npos);
}

void read_xml(const std::string &input_file, std::vector<Department*> &tree)
{
        std::ifstream xml(input_file);
        std::string curline;
        int cur_dept = -1;
        while (getline(xml, curline)) {
                if (contains(curline, "<department ")) {
                        int begin = curline.find('"');
                        std::string name = "";
                        while (curline[++begin] != '"')
                                name += curline[begin];
                        tree.push_back(new Department(name));
                        cur_dept++;
                } else if (contains(curline, "<employment>")) {
                        std::string emp_surname, emp_name,
                        emp_middlename, emp_function;
                        int emp_salary;

                        for (int i = 0; i < 5; ++i) {
                                getline(xml, curline);
                                if (contains(curline, "<name>")) {
                                        emp_name = cut(curline);
                                } else if (contains(curline, "<surname>")) {
                                        emp_surname = cut(curline);
                                } else if (contains(curline, "<middleName>")) {
                                        emp_middlename = cut(curline);
                                } else if (contains(curline, "<function>")) {
                                        emp_function = cut(curline);
                                } else if (contains(curline, "<salary>")) {
                                        emp_salary = std::stoi(cut(curline));
                                }
                        }
                        tree[cur_dept]->add_emp(new Employee(emp_salary, emp_name,
                                                        emp_surname, emp_middlename, emp_function));
                }
        }
}

void writexml(const std::string &output_file, const std::vector<Department*> &tree)
{
        std::ofstream xml(output_file);
        xml << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<departments>\n";
        for (auto &dep : tree) {
                xml << "   <department name=\"";
                xml << dep->get_name() << "\">\n";
                auto emps = dep->get_emp();
                xml << "      <employments>\n";
                for (auto &emp : emps) {
                        xml << "         <employment>\n"
                        << "            <surname>"
                        << emp->get_surname() << "</surname>\n"
                        << "            <name>"
                        << emp->get_name() << "</name>\n"
                        << "            <middleName>"
                        << emp->get_middlename() << "</middleName>\n"
                        << "            <function>"
                        << emp->get_function() << "</function>\n"
                        << "            <salary>"
                        << emp->get_salary() << "</salary>\n"
                        << "         </employment>\n";
                }
                xml << "     </employments>\n" << "   </department>\n";
        }
        xml << "</departments>";

}
