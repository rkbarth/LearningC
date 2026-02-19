#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <cstdlib>
#include <readline/readline.h>
#include <readline/history.h>

struct Book {
    int id;
    std::string title;
    std::string author;
    std::string isbn;
    std::string summary;
    std::string deweyDecimal;
    bool available;
};

class Library {
private:
    std::map<int, Book> books;
    int nextId = 1;

public:
    bool isbnExists(const std::string& isbn) const {
        for (const auto& pair : books) {
            if (pair.second.isbn == isbn) {
                return true;
            }
        }
        return false;
    }
    
    bool addBook(const std::string& title, const std::string& author, const std::string& isbn, 
                 const std::string& summary, const std::string& deweyDecimal) {
        if (isbnExists(isbn)) {
            std::cout << "Error: A book with ISBN " << isbn << " already exists. Use --update to modify it." << std::endl;
            return false;
        }
        
        Book newBook;
        newBook.id = nextId++;
        newBook.title = title;
        newBook.author = author;
        newBook.isbn = isbn;
        newBook.summary = summary;
        newBook.deweyDecimal = deweyDecimal;
        newBook.available = true;
        
        books[newBook.id] = newBook;
        std::cout << "Book added successfully with ID: " << newBook.id << std::endl;
        return true;
    }
    
    void listBooks() {
        if (books.empty()) {
            std::cout << "No books in the library." << std::endl;
            return;
        }
        
        std::cout << "\n=== Library Books ===" << std::endl;
        for (const auto& pair : books) {
            const Book& book = pair.second;
            std::cout << "ID: " << book.id << " | Title: " << book.title 
                      << " | Author: " << book.author << " | ISBN: " << book.isbn
                      << " | Dewey: " << book.deweyDecimal
                      << " | Available: " << (book.available ? "Yes" : "No") << std::endl;
        }
        std::cout << std::endl;
    }
    
    void readBook(int id) {
        if (books.find(id) == books.end()) {
            std::cout << "Book with ID " << id << " not found." << std::endl;
            return;
        }
        
        const Book& book = books[id];
        std::cout << "\n=== Book Details ===" << std::endl;
        std::cout << "ID: " << book.id << std::endl;
        std::cout << "Title: " << book.title << std::endl;
        std::cout << "Author: " << book.author << std::endl;
        std::cout << "ISBN: " << book.isbn << std::endl;
        std::cout << "Summary: " << book.summary << std::endl;
        std::cout << "Dewey Decimal: " << book.deweyDecimal << std::endl;
        std::cout << "Available: " << (book.available ? "Yes" : "No") << std::endl;
        std::cout << std::endl;
    }
    
    void updateBook(int id, const std::string& title, const std::string& author, const std::string& isbn,
                     const std::string& summary, const std::string& deweyDecimal) {
        if (books.find(id) == books.end()) {
            std::cout << "Book with ID " << id << " not found." << std::endl;
            return;
        }
        
        if (!title.empty()) books[id].title = title;
        if (!author.empty()) books[id].author = author;
        if (!isbn.empty()) books[id].isbn = isbn;
        if (!summary.empty()) books[id].summary = summary;
        if (!deweyDecimal.empty()) books[id].deweyDecimal = deweyDecimal;
        
        std::cout << "Book updated successfully." << std::endl;
    }
    
    void deleteBook(int id) {
        if (books.find(id) == books.end()) {
            std::cout << "Book with ID " << id << " not found." << std::endl;
            return;
        }
        
        books.erase(id);
        std::cout << "Book deleted successfully." << std::endl;
    }
};

// Forward declaration
void printHelp();

void parseAndExecute(const std::string& input, Library& library) {
    std::map<std::string, std::string> params;
    std::string command;
    
    // Parse command-line arguments
    std::istringstream iss(input);
    std::string token;
    
    while (iss >> token) {
        if (token.length() >= 2 && token[0] == '-' && token[1] == '-') {
            size_t equalPos = token.find('=');
            if (equalPos != std::string::npos) {
                // This is a parameter like --title=value
                std::string key = token.substr(2, equalPos - 2);
                std::string value = token.substr(equalPos + 1);
                params[key] = value;
            } else {
                // This is a flag like --list
                command = token.substr(2);
            }
        }
    }
    
    // Execute command
    if (command == "list") {
        library.listBooks();
    } else if (command == "add") {
        std::string title = params["title"];
        std::string author = params["author"];
        std::string isbn = params["isbn"];
        std::string summary = params["summary"];
        std::string deweyDecimal = params["dewey"];
        
        if (title.empty() || author.empty() || isbn.empty()) {
            std::cout << "Error: --add requires --title, --author, and --isbn parameters." << std::endl;
        } else {
            library.addBook(title, author, isbn, summary, deweyDecimal);
        }
    } else if (command == "read") {
        if (params.find("id") == params.end()) {
            std::cout << "Error: --read requires --id parameter." << std::endl;
            return;
        }
        int id = std::stoi(params["id"]);
        library.readBook(id);
    } else if (command == "update") {
        if (params.find("id") == params.end()) {
            std::cout << "Error: --update requires --id parameter." << std::endl;
            return;
        }
        int id = std::stoi(params["id"]);
        library.updateBook(id, params["title"], params["author"], params["isbn"], params["summary"], params["dewey"]);
    } else if (command == "delete") {
        if (params.find("id") == params.end()) {
            std::cout << "Error: --delete requires --id parameter." << std::endl;
            return;
        }
        int id = std::stoi(params["id"]);
        library.deleteBook(id);
    } else if (!command.empty()) {
        std::cout << "Unknown command: " << command << std::endl;
        printHelp();
    }
}

void printHelp() {
    std::cout << "\n=== Library System Commands ===" << std::endl;
    std::cout << "--list                                                List all books" << std::endl;
    std::cout << "--add --title=<t> --author=<a> --isbn=<i> [--summary=<s>] [--dewey=<d>]    Add a new book" << std::endl;
    std::cout << "--read --id=<id>                                      Read a book by ID" << std::endl;
    std::cout << "--update --id=<id> [--title] [--author] [--isbn] [--summary] [--dewey]    Update a book" << std::endl;
    std::cout << "--delete --id=<id>                                    Delete a book" << std::endl;
    std::cout << "--help                                                Show this help message" << std::endl;
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    Library library;
    
    // Add sample books
    library.addBook("C++ Primer", "Stanley B. Lippman", "978-0321714113", 
                    "A comprehensive guide to C++ programming language", "005.133");
    library.addBook("Effective C++", "Scott Meyers", "978-0321334879",
                    "50 specific ways to improve your programs and designs", "005.13");
    library.addBook("C++ Concurrency in Action", "Anthony Williams", "978-1933988771",
                    "Practical multithreading and concurrent programming in C++", "005.13");
    library.addBook("The C++ Programming Language", "Bjarne Stroustrup", "978-0321563842",
                    "The definitive reference guide to C++ by its creator", "005.133");
    library.addBook("Modern C++ Design", "Andrei Alexandrescu", "978-0201704310",
                    "Advanced techniques for generic programming and templates", "005.133");
    library.addBook("C++ Templates: The Complete Guide", "David Vandevoorde", "978-0321714121",
                    "In-depth exploration of C++ template programming", "005.13");
    library.addBook("Accelerated C++", "Andrew Koenig", "978-0201379624",
                    "Practical programming by example for learning C++", "005.133");
    library.addBook("C++ Coding Standards", "Herb Sutter", "978-0321113586",
                    "101 rules, guidelines, and best practices for writing excellent C++ code", "005.13");
    library.addBook("Design Patterns in C++", "Gang of Four", "978-0201633610",
                    "Elements of reusable object-oriented software implementation in C++", "005.13");
    library.addBook("Thinking in C++", "Bruce Eckel", "978-0139798092",
                    "Volume Two: Practical Programming for advanced C++ developers", "005.133");
    
    // Process initial command-line arguments
    if (argc > 1) {
        std::string cmdLineArgs;
        for (int i = 1; i < argc; i++) {
            cmdLineArgs += argv[i];
            if (i < argc - 1) cmdLineArgs += " ";
        }
        parseAndExecute(cmdLineArgs, library);
    }
    
    // Interactive loop
    std::cout << "Library System - Enter commands (--help for options, Ctrl+C to exit):" << std::endl;
    while (true) {
        char* input_ptr = readline("> ");
        
        if (input_ptr == nullptr) {
            // Ctrl+D was pressed
            std::cout << std::endl;
            break;
        }
        
        std::string input(input_ptr);
        
        // Add to history if not empty
        if (!input.empty()) {
            add_history(input_ptr);
        }
        
        free(input_ptr);
        
        if (input.empty()) continue;
        
        parseAndExecute(input, library);
    }
    
    return 0;
}
