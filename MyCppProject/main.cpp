#include <iostream>
#include <string>
#include <map>
#include <sstream>

void parseAndOutputParams(const std::string& input, std::map<std::string, std::string>& params) {
    // Clear previous parameters
    params.clear();
    
    // Parse input for --input0X=value format
    std::istringstream iss(input);
    std::string token;
    
    while (iss >> token) {
        if (token.substr(0, 2) == "--") {
            size_t equalPos = token.find('=');
            if (equalPos != std::string::npos) {
                std::string key = token.substr(2, equalPos - 2);
                std::string value = token.substr(equalPos + 1);
                params[key] = value;
            }
        }
    }
    
    // Output parameters in alphabetical order with spaces between them
    bool first = true;
    for (const auto& pair : params) {
        if (!first) {
            std::cout << " ";
        }
        std::cout << pair.second;
        first = false;
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    std::map<std::string, std::string> params;
    
    // Parse initial command-line arguments in format: --input0X=value
    std::string cmdLineArgs;
    for (int i = 1; i < argc; i++) {
        cmdLineArgs += argv[i];
        if (i < argc - 1) cmdLineArgs += " ";
    }
    
    if (!cmdLineArgs.empty()) {
        parseAndOutputParams(cmdLineArgs, params);
    }
    
    // Interactive loop - keep running until Ctrl+C
    std::string input;
    std::cout << "Echo CLI - Enter params (--input01=value --input02=value...) or text (Ctrl+C to exit):" << std::endl;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        
        // Check if input contains parameters
        if (input.find("--input") != std::string::npos) {
            parseAndOutputParams(input, params);
        } else {
            // Just echo the text
            std::cout << input << std::endl;
        }
    }
    
    return 0;
}