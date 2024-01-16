#include <string.h>
#include <chrono>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

std::vector<std::string> tokenize(const std::string& s)
{
    std::vector<std::string> result;

    std::string::size_type from = 0;
    std::string::size_type colon = s.find(':');

    while (colon != std::string::npos)
    {
        result.push_back(s.substr(from, colon - from));
        from = colon + 1;
        colon = s.find(':', from);
    }

    result.push_back(s.substr(from));

    return result;
}

void replace(std::string& s, const char* from, const char* to)
{
    std::size_t pos = 0;

    while ((pos = s.find(from, pos)) != std::string::npos)
    {
        s.replace(pos, strlen(from), to);
        pos += strlen(to);
    }
}

std::string concatenate_tokens(const std::vector<std::string>& tokens)
{
    std::string result;

    for (const std::string& token : tokens)
        if (result.empty())
            result = token;
        else
            result += ":" + token;

    return result;
}

std::string service(std::string& in)
{
    std::istringstream iss(in);
    std::string result;
    std::uint64_t line_count = 0;
    std::string line;

    std::map<std::string, std::string> entries;
    
    while (std::getline(iss, line))
    {
        std::vector<std::string> tokens = tokenize(line);

        if (tokens[0] == "params") {
            replace(tokens[1], "${param}", "task7");
            replace(tokens[1], "${tag}", "performance");
            replace(tokens[1], "${id}", "TUM");
            replace
                (tokens[1], "${line_count}", std::to_string(line_count).c_str());

            result += concatenate_tokens(tokens) + '\n';
            ++line_count;
        }
        else if (tokens[0] == "set") {
            entries[tokens[1]] = tokens[2];
        }
        else if (tokens[0] == "value") {
            if (entries.find(tokens[1]) != entries.end())
                result += "value:" + entries[tokens[1]] + '\n';
            else
                result += "value:\n";

            ++line_count;
        }
        else
        {
            result += concatenate_tokens(tokens) + '\n';
            ++line_count;
        }
    }

    return result;
}

/**********************************/
/* IMPORTANT!!!                   */
/* DON'T MODIFY THE MAIN FUNCTION */
/**********************************/

int main()
{
    std::ifstream file( "records.txt" );

    if ( file )
    {
        std::ostringstream oss;
        oss << file.rdbuf();
        std::string str = oss.str();

        auto start = std::chrono::steady_clock::now();
        std::string result = service(str);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end - start;

        std::cout << diff.count() << std::endl;
        file.close();

        std::ofstream output("output");
        if(output.is_open())
        {
            output << result;
            output.close();
        }

        file.close();
    }
    return 0;
}
