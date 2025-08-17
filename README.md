# OOP345-Advanced Cpp-Assignments
## 📌 Course Description
**OOP345** is an advanced course in **Object-Oriented Software Development** with a focus on **modern C++ (C++11/14/17)**.  
The course emphasizes efficiency, scalability, and safe coding practices using modern language features and libraries.  
This repository contains my **assignments**, each designed to explore real-world software development techniques.

---

## 🎯 Learning Objectives
Through this course, I gained practical experience in:
- Applying **RAII (Resource Acquisition Is Initialization)** and proper resource management
- Using **smart pointers** (`unique_ptr`, `shared_ptr`) for safe memory handling
- Leveraging the **Standard Template Library (STL)** for algorithms and containers
- Implementing **multi-threading** with synchronization primitives
- Designing and applying **lambda expressions** and functional-style programming
- Writing modular, reusable, and efficient C++ applications
- Applying **exception handling** and **design patterns**

---

## 📂 Repository Structure
```

OOP345/
├── asgn1/       # Assignment 1: Advanced C++ basics
│   └── src/     # Source files
├── asgn2/       # Assignment 2: Templates, STL & memory safety
│   └── src/
├── asgn3/       # Assignment 3: Concurrency & Multi-threading
├── asgn4/       # Assignment 4: Final project (design-focused)

````

---

## ⚙️ Setup & Compilation
To compile an assignment:
```bash
g++ src/*.cpp -o program -std=c++17 -pthread -Wall
./program
````

General guidelines:

* Use the **C++17 standard** or higher.
* Include `-pthread` for multi-threaded programs.
* Run with different datasets to test performance and correctness.

---

## 🧪 Testing

* Each assignment includes **sample input and output files**.
* Testing involved:

  * **Functional correctness** (expected vs. actual output)
  * **Stress testing** with large datasets
  * **Concurrency tests** to ensure thread safety
  * **Memory leak checks** using `valgrind`

---

## 📖 Key Topics Covered

* Modern C++ (C++11/14/17) Features
* Smart Pointers & RAII
* STL Containers & Algorithms
* Templates & Generic Programming
* Multi-threading & Synchronization
* Lambda Expressions & Functional Programming
* Exception Handling & Error Safety
* Design Patterns in C++

---

## 🏆 Capstone Focus

Assignments in OOP345 are structured as **progressive challenges**, culminating in advanced software design.
Key outcomes include:

* Writing **safe, efficient C++17 code**
* Applying **multi-threading** in real-world scenarios
* Designing modular, reusable libraries
* Demonstrating **professional coding practices** suitable for industry

---

## 👨‍💻 Author

Developed as part of **OOP345 coursework at Seneca College**.
This repository showcases my expertise in **modern C++ software development**, preparing me for advanced system-level programming and professional software engineering roles.

