# LearningC

My journey learning C++. This project contains two applications:

## 1. MyCppProject
A simple CLI echo program that takes named input parameters and outputs them in alphabetical order.

## 2. LibrarySystem
A sample command-line library management system built in C++. This application demonstrates CRUD (Create, Read, Update, Delete) operations for managing a collection of books.

---

## LibrarySystem

### Overview
LibrarySystem is a CLI application that allows you to manage a library database of books. Each book contains the following information:
- **ID** - Auto-incremented identifier
- **Title** - Book title
- **Author** - Author name
- **ISBN** - Unique ISBN number
- **Summary** - Book description
- **Dewey Decimal** - Library classification number
- **Available** - Availability status

The application comes pre-loaded with 10 C++ programming books as sample data.

### Compilation

First, install the readline development library (required for command history and line editing):

```bash
sudo apt-get update
sudo apt-get install libreadline-dev
```

Then compile the program:

```bash
cd /workspaces/LearningC/LibrarySystem
g++ -o main main.cpp -lreadline
```

### Commands

#### List All Books
Display all books in the library with their details.

```bash
./main --list
```

#### Add a New Book
Add a new book to the library. ISBN must be unique.

```bash
./main --add --title="C++ Primer" --author="Stanley B. Lippman" --isbn="978-0321999999" --summary="A comprehensive guide" --dewey="005.133"
```

**Required parameters:**
- `--title=<book title>`
- `--author=<author name>`
- `--isbn=<isbn number>`

**Optional parameters:**
- `--summary=<book description>`
- `--dewey=<dewey decimal classification>`

#### Read a Book
View detailed information about a specific book by ID.

```bash
./main --read --id=1
```

**Parameters:**
- `--id=<book id>` - The ID of the book to view

#### Update a Book
Update one or more fields of an existing book.

```bash
./main --update --id=1 --title="Updated Title" --summary="New summary"
```

**Parameters:**
- `--id=<book id>` - The ID of the book to update (required)
- `--title=<new title>` - Updated title (optional)
- `--author=<new author>` - Updated author (optional)
- `--isbn=<new isbn>` - Updated ISBN (optional)
- `--summary=<new summary>` - Updated summary (optional)
- `--dewey=<new dewey>` - Updated Dewey Decimal (optional)

#### Delete a Book
Remove a book from the library by ID.

```bash
./main --delete --id=1
```

**Parameters:**
- `--id=<book id>` - The ID of the book to delete

#### Display Help
Show all available commands.

```bash
./main --help
```

### Interactive Mode

When run without arguments, LibrarySystem enters interactive mode where you can continuously enter commands:

```bash
./main
Library System - Enter commands (--help for options, Ctrl+C to exit):
> --list
> --add --title="New Book" --author="John Doe" --isbn="123456"
> --read --id=11
> --update --id=11 --title="Updated Book"
> --delete --id=11
```

#### Command History and Editing

The application uses the GNU readline library, which provides terminal-like command editing features:

- **Up/Down arrows** - Browse through your command history
- **Left/Right arrows** - Move cursor within the current line
- **Ctrl+A** - Jump to the beginning of the line
- **Ctrl+E** - Jump to the end of the line
- **Ctrl+C** - Cancel current input
- **Ctrl+D** - Exit the program
- **Ctrl+U** - Clear the current line
- **Ctrl+R** - Reverse search through history

This allows you to easily re-run previous commands with the up arrow, just like in your terminal!

### Error Handling

- **Duplicate ISBN**: If you try to add a book with an ISBN that already exists, you'll see an error message directing you to use the update command.
- **Book Not Found**: If you try to read, update, or delete a non-existent book ID, you'll receive a "not found" error.
- **Missing Required Fields**: Adding a book without required fields will show an error message listing what's missing.