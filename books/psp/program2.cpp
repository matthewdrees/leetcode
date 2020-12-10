// PSP program 2. Calculate lines of code (LOC) metrics.
//
// This is a toy program and not a real LOC calculator. (It doesn't really parse
// C++, can't handle namespaces, etc.)
//
// Input: cpp source file.
// Output: Lines of Code information.
//
// Usage:
//
//   $ ./program2 program2.cpp
//   Part Name   Number of items   Part LOC   Total LOC
//   ---------   ---------------   --------   ---------
//       class                 2         30
//    function                 4        192
//                                                  222
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>

// Part of a program, e.g. class, function, etc.
class ProgramPart
{
public:
    ProgramPart(std::string name_) : name(name_), num(0), loc(0) {}
    std::string name; // Name (e.g. "class", "function")
    int num = 0;      // Number of these parts found in program.
    int loc = 0;      // Total LOC found in these parts.
};

class ProgramLoc
{
public:
    ProgramLoc() : classes("class"), functions("function") {}

    // Track each type of part found in the program.
    ProgramPart classes;
    ProgramPart functions;

    int get_total_loc() const { return classes.loc + functions.loc; }
};

bool line_is_empty_or_brackets(const std::string &line)
{
    for (size_t i = 0; i < line.size(); ++i)
    {
        if (isspace(line[i]) || line[i] == '{' || line[i] == '}')
        {
            continue;
        }
        return false;
    }
    return true;
}

// Return true if line appears to be a comment or # include.
// Note, only handling c++ style comments, not /* */.
bool line_is_a_comment(const std::string &line)
{
    // skip whitespace.
    size_t i = 0;
    for (; i < line.size(); ++i)
    {
        if (line[i] != ' ')
        {
            break;
        }
    }
    return line.substr(i, 2) == "//";
}

int get_num_loc_on_line(const std::string &line)
{
    if (line_is_a_comment(line))
    {
        return 0;
    }
    // Line is #include<something>
    if (line.substr(0, 1) == "#")
    {
        return 0;
    }
    // empty line.
    if (line_is_empty_or_brackets(line))
    {
        return 0;
    }
    return 1;
}

bool looks_like_a_function(const std::string &line)
{
    return line.find('(') != std::string::npos;
}

std::optional<ProgramLoc> calculate_loc(std::string filename)
{
    ProgramLoc program_loc;
    enum class State
    {
        None,
        Class,
        Function,
    };
    State state = State::None;

    std::ifstream ifs(filename);
    if (!ifs.is_open())
    {
        std::cerr << "Error opening file " << filename << '\n';
        return {};
    }

    std::string line;
    while (std::getline(ifs, line))
    {
        const int num_loc_on_line = get_num_loc_on_line(line);
        switch (state)
        {
        case State::None:
            if (num_loc_on_line > 0)
            {
                if (line.substr(0, 6) == "class ")
                {
                    program_loc.classes.loc += num_loc_on_line;
                    state = State::Class;
                }
                else if (looks_like_a_function(line))
                {
                    program_loc.functions.loc += num_loc_on_line;
                    state = State::Function;
                }
                else
                {
                    std::cerr << "Found line of code outside class or function:\n"
                              << line << '\n';
                    return {};
                }
                break;
            case State::Class:
                if (line.substr(0, 2) == "};")
                {
                    state = State::None;
                }
                else
                {
                    program_loc.classes.loc += num_loc_on_line;
                }
                break;
            case State::Function:
                if (line.substr(0, 1) == "}")
                {
                    state = State::None;
                }
                else
                {
                    program_loc.functions.loc += num_loc_on_line;
                }
                break;
            }
        }
    }
    if (state != State::None)
    {
        std::cerr << "Ended program in wrong state: " << static_cast<int>(state) << '\n';
        return {};
    }
    return program_loc;
}

// dump formatted stats.
void dump_program_stats_line(const ProgramPart &program_part)
{
    if (program_part.loc > 0)
    {
        std::cout << std::setw(9) << program_part.name
                  << std::setw(17) << program_part.num
                  << std::setw(11) << program_part.loc
                  << '\n';
    }
}
void dump_program_stats(const ProgramLoc &program_loc)
{
    std::cout << "Part Name   Number of items   Part LOC   Total LOC\n";
    std::cout << "---------   ---------------   --------   ---------\n";
    dump_program_stats_line(program_loc.classes);
    dump_program_stats_line(program_loc.functions);
    std::cout << std::setw(9 + 17 + 11 + 12) << program_loc.get_total_loc() << '\n';
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage:\n"
                  << "./program2 file.cpp\n";
        return 1;
    }

    const auto program_loc = calculate_loc(argv[1]);
    if (!program_loc)
    {
        return 1;
    }

    dump_program_stats(*program_loc);
    return 0;
}
