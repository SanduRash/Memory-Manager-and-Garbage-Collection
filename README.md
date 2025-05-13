# 📝 CSC45500 Programming Project #3: Memory Manager and Garbage Collection

## 🎯 Objective
Implemented a programming language memory manager with garbage collection, free list compression, and dynamic memory allocation.

---

## 🖥️ Platform
- **Developed on:** Linux  
- **Language:** C++

---

## 🛠️ Technologies Used
- **Languages:** C++
- **Tools:** GCC, Linux Terminal

---

## 💡 Project Description
This project builds an interpreter that simulates:
- Dynamic memory allocation using a custom language
- Variable copying
- Garbage collection using reference counting
- Free list compression to reduce fragmentation

### 🔑 Key Features
- **First-fit memory allocation**
- **Garbage collection** to reclaim unused blocks
- **Free list compression** (merging adjacent free blocks)
- **Recursive descent parser** for a mini-language defined by a BNF grammar

---

## ⚙️ Sample Input and Output

**Input Prompt:**
Please enter the initial freelist (heap) size: 512
Please enter the name of an input file: test.myl

**Sample Execution Output:**
```bash
Variables:
b:34(57) [1]
c:0(17) [1]
Free List:
17(17) [0], 91(421) [0]
...

```
---

## ⚡ Approach and Implementation

### 🧠 User Input
- Prompts the user for initial heap size and input filename.

### 🧩 Parsing
- A recursive descent parser interprets commands according to BNF grammar.

### 📦 Memory Management
- **alloc**: Allocates memory using the first-fit approach.
- **free**: Frees blocks and returns them to the freelist.
- **compress**: Merges adjacent free blocks.
- **dump**: Prints variable list and freelist.

### ♻️ Garbage Collection
- Tracks reference counts and reclaims memory for unused variables.

---

## 🚀 Setup and Instructions
- Requires C++17 standard or newer

```bash
### 1. Clone the Repository
git clone https://github.com/yourusername/project-repo.git

### 2. Compile the Code
g++ -o memory_manager memory_manager.cpp

### 3. Run the Program
./memory_manager



