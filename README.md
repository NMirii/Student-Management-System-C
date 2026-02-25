# 🎓 Student Manager CLI (C)

A fast and simple **command-line student management system** written in pure C.

Manage student records, store them locally, and perform full CRUD operations — all from the terminal.

Built as a practice project for learning **structs, file handling, input validation, and program flow in C**.

---

## 🚀 What It Does

* ➕ Add students
* 🗑 Delete students by ID
* ✏ Update student info
* 📋 List all students
* 💾 Auto-save to file
* 🔢 Auto-increment student IDs
* ✅ Safe input validation

All data is saved in:

```
students.txt
```

So nothing is lost when the program closes.

---

## 🧠 How It Works

Each student record contains:

```
ID | Name | Surname | Age
```

Data is stored in CSV-like format:

```
1,Ali,Aliyev,20
2,Leyla,Mammadova,22
```

## 🛠 Tech Stack

* C (ANSI C)
* File I/O
* Structs
* Input validation
* Console interface

No external libraries.

---

## ⚙ Compile & Run

### Compile

```
gcc main.c -o student-manager
```

### Run (Linux / macOS)

```
./student-manager
```

### Run (Windows)

```
student-manager.exe
```

---

## 📟 Program Menu

```
1 → Add student
2 → Delete student
3 → Update student
4 → Show all students
5 → Exit
```

---

## 🧪 Validation Rules

* Names → letters only
* Age → 1 to 120
* Invalid input → rejected safely

---

## 📌 Why This Project?

Practice core C programming concepts:

* memory & structs
* file persistence
* user input handling
* CRUD logic
* program architecture

---

## 🔮 Possible Upgrades

* Search by name or ID
* Sorting
* Binary storage
* GUI version
* Database support
* Edit specific fields only
