# Expression Evaluator with Variables (C Project)

This project implements an **infix expression evaluator with variable assignment** using **Binary Search Trees (BST)**, **Stacks**, and **Heap Sort** in C.  
It allows reading equations from a file, validating them, evaluating them, and storing results in a symbol table (BST).

---

## 📂 Project Structure
```
.
|-- main.c        # Source code
|-- input.txt     # Input file containing equations (user-provided)
`-- README.md     # Project documentation
```

---

## ✨ Features
- **Equation Parsing & Validation**:
  - Detect invalid symbols
  - Check for balanced parentheses
  - Ensure valid variable names
- **Infix to Postfix Conversion**
- **Postfix Expression Evaluation**
- **Variable Management**:
  - Store variables in a Binary Search Tree (BST)
  - Search and update variable values
  - Print sorted variables (by name)
- **Heap Sort Integration**:
  - Sort variables by value
- **Error Handling**:
  - Invalid symbols
  - Unbalanced parentheses
  - Invalid variable names
  - Missing `=` in equation
  - Undefined variables

---

## ▶️ Compilation & Execution

### Compile
```bash
gcc main.c -o evaluator -lm
```

### Run
```bash
./evaluator
```

You will be prompted to enter the name of an input file.

---

## 📘 Input File Format
- Each line should contain an equation of the form:
```
x = 5 + 3 * ( 2 + y )
y = 10
z = x ^ 2 - y / 2
```
- Variables must start with a letter and can contain letters and digits.
- Parentheses must be balanced.
- Supported operators: `+ - * / % ^`

---

## 🧪 Example Run
**Input File (`equations.txt`)**
```
a = 5
b = 3
c = a + b * 2
d = ( a + b ) * ( c - 4 )
```

**Program Output**
```
Enter file name or Ctrl+Z to exit:
----------------------------------
equations.txt
Equations:
a = 5
b = 3
c = a + b * 2
d = ( a + b ) * ( c - 4 )
----------------------------------
Sorting by variable name:
a : 5.00
b : 3.00
c : 11.00
d : 16.00
----------------------------------
Sorting by value:
b : 3.00
a : 5.00
c : 11.00
d : 16.00
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
```

---

## 🚀 Possible Improvements
- Support floating-point formatting for more precision
- Extend to support more functions (e.g., `sin`, `cos`, `log`)
- Add deletion of variables from BST
- Add interactive mode (direct equation input instead of file only)

---

## 🛠️ Requirements
- A C compiler (e.g., GCC)
- Math library (`-lm` flag when compiling)
- Linux, macOS, or Windows with `gcc`

---

> README.md is generated using ChatGPT