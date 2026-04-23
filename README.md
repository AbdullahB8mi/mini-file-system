# Mini File System Simulator (ICS 433 – project)

## 📌 Overview

This project is a **Mini File System Simulator** implemented in C. It mimics the core behavior of a real operating system file system but operates entirely in **RAM (memory)**.

The system allows users to create, read, write, delete, list, and search files through a **command-line interface (CLI)**.

---

## 🎯 Objectives

* Understand file system design concepts
* Practice memory management in C
* Implement File Control Blocks (FCB)
* Simulate storage allocation and metadata handling

---

## ⚙️ Features

* Create files with unique names
* Write and read file content
* Delete files and free memory
* List all stored files (name, size, index)
* Search for files by name
* Error handling for invalid operations

---

## 🧠 System Design

The system is divided into three layers:

1. **User Interface (CLI)**

   * Handles user input and displays output

2. **Command Processor**

   * Parses commands and calls appropriate functions

3. **File System Core**

   * Manages file storage using an array of File Control Blocks

---

## 📦 Data Structure

```c
typedef struct {
    char name[50];
    int size;
    char content[1024];
    int isUsed;
} FileControlBlock;
```

* Maximum files: 100
* Maximum file size: 1 KB

---

## 💻 Supported Commands

| Command                    | Description          |
| -------------------------- | -------------------- |
| create <filename>          | Create a new file    |
| write <filename> <content> | Write data to a file |
| read <filename>            | Display file content |
| delete <filename> (phase3) | Delete a file        |
| list              (phase3) | Show all files       |
| search <filename> (phase3) | Find a file          |
| exit                       | Exit the program     |

---

## ▶️ How to Run

### Compile:

```bash
gcc src/main.c src/filesystem.c -o mfs
```

### Run:

```bash
./mfs
```

---

## 🧪 Example Usage

```
> create file1
File created successfully

> write file1 Hello World
Content written successfully

> read file1
Hello World

> list
[0] file1 - 11 bytes

> delete file1
File deleted
```

---

## ⚠️ Limitations

* Data is stored in RAM only (not persistent)
* All files are lost when the program exits
* No support for directories (flat structure)
* Fixed number of files (100 max)

---

## ❗ Error Handling

* Duplicate file names are not allowed
* File not found errors are handled
* Memory/file limit checks are enforced

---

## 👥 Team Members

* Abdullah Albuqami
* Abdulaziz Alotaibi
* Naif Alshalan
* Rayan Alsaedi


---

## 📚 Course Info

ICS 433 – Operating Systems
Project – Mini File System Simulator

---

## 🚀 Future Improvements

* Add file persistence using disk (fopen, fwrite)
* Support directories
* Improve command parsing
* Add file permissions

---
