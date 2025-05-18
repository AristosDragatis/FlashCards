# FlashCards

**FlashCards** is a command-line interface (CLI) application for creating and managing flashcards, implemented in C++ using SQLite for data storage.

## Features

- Add, edit, and delete flashcards
- Store data in a local SQLite database
- Simple and user-friendly command-line interface

## Prerequisites

- C++17 or later
- CMake
- SQLite3

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/AristosDragatis/FlashCards.git
   cd FlashCards
   ```

2. Create a build folder and compile the project:

   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

## Usage

After compiling, run the application:

```bash
./FlashCards
```

The application provides options to:
- Add new flashcards
- View existing flashcards
- Edit or delete flashcards

## Project Structure

- `main.cpp`: Entry point of the application
- `Database.h` / `Database.cpp`: SQLite database handling
- `CMakeLists.txt`: Build configuration for CMake

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
