# Scientific Calculator

A desktop scientific calculator written in C++ with Qt, which evaluates expressions by converting them to Reverse Polish Notation.

## Overview

Expressions are entered with on-screen buttons in standard infix notation, for example `2*(3+4)^2` or `sin(pi/2)`. Pressing `=` evaluates the expression in two stages:

1. `RPN::parseString` converts the infix string to a list of tokens in Reverse Polish Notation (postfix), using the shunting-yard algorithm. `^` is right-associative and takes precedence over `*` and `/`, which in turn take precedence over `+` and `-`.
2. `RPNEvaluator::evaluateRPN` evaluates the postfix tokens with a stack of `long double` values.

The result replaces the expression in the display.

## Features

- Arithmetic: `+`, `-`, `*`, `/` and `^` (exponentiation), with brackets
- Trigonometric functions (in radians): `sin`, `cos`, `tan` and their inverses `asin`, `acos`, `atan`
- Hyperbolic functions: `sinh`, `cosh`, `tanh` and their inverses `asinh`, `acosh`, `atanh`
- Logarithms: `ln` (natural) and `log` (base 10)
- Roots: square root and cube root
- Rounding and magnitude: `ceil`, `floor`, `abs`
- Two-argument functions: `min(a,b)` and `max(a,b)`
- Constants: `e`, `π` and `Φ` (the golden ratio)
- Decimal numbers
- `C` clears the display

## Tech stack

- C++ (C++11 or later)
- Qt 5 (Core, GUI, Widgets); the Qt Creator configuration in the repository targets Qt 5.11.1 with MSVC 2017 64-bit
- qmake

## Getting started

### Prerequisites

- Qt 5 with the Widgets module
- A C++ compiler supported by your Qt installation
- Optionally, Qt Creator

### Build and run

With Qt Creator, open `ScientificCalculatorGUI.pro`, then build and run. From the command line:

```sh
qmake ScientificCalculatorGUI.pro
make            # or nmake / jom with MSVC
```

This produces the `ScientificCalculatorGUI` executable.

## Usage

The display is read-only, so expressions are entered with the buttons. Function buttons insert the function name (for example `sin⁻¹` inserts `asin`), after which the argument should be wrapped in brackets: `sqrt(2)`, `max(3,7)`. Press `=` to evaluate and `C` to clear.

Results are shown with six decimal places.

## Project structure

```
.
├── ScientificCalculatorGUI.pro        # qmake project file
├── ScientificCalculatorGUI.pro.user   # Qt Creator per-user settings
├── main.cpp                           # Creates the QApplication and shows the main window
├── mainwindow.h/.cpp                  # Button handling, evaluation and clearing
├── mainwindow.ui                      # Qt Designer layout of the display and keypad
├── RPN.h/.cpp                         # Infix-to-RPN conversion (shunting-yard) and token helpers
└── RPNEvaluator.h/.cpp                # Stack-based evaluation of RPN tokens
```

## Status and limitations

The repository is described in its single commit as a mock-up GUI. Limitations visible in the code:

- The `Ans` button inserts `Ans` into the expression, but no previous answer is stored and the token is ignored during evaluation.
- Unary minus works only at the start of an expression (for example `-5+2`), not after an operator or bracket (for example `2*-3`).
- There is no error handling: malformed input such as unbalanced brackets or missing operands can produce incorrect results or crash the application.
- The `.pro` file's `DISTFILES` list refers to object files in a local build directory outside the repository; these entries are not needed to build.
- The Help menu has no working entries.
