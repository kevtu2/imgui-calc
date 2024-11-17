# imgui-calc
imgui-calc is a simple calculator application utilizing the [Dear Imgui](https://github.com/ocornut/imgui) framework as the frontend of choice.

## Features
- Perform basic operations: `+`, `-`, `*`, `/`
- Basic trigonometric functions: `sin`, `cos`, `tan`
- Set different trigonometric modes (radians, degrees)
- Display past calculations (History tab)
- Adjustable floating point precision
- Real-time display of user inputs and results.

## Current Limitations
- No support for exponential functions
- No support for square and square root functions
- Some forms of invalid input (not including division by zero) are not handled
- Quality of life features such as previous answer (ANS) button have not been implemented
- Limited to rendering via DirectX11 (Windows only)
- Currently limited to running in Visual Studio

## Getting Started
### Prerequisites
- Windows 10/11
- DirectX11
- Python3.10 or newer
- Microsoft Visual Studio 2022

### Installation and usage in windows
1. Clone the repository:
```markdown
git clone https://github.com/kevtu2/imgui-calc.git
```
2. Navigate to working directory in powershell or command prompt
```markdown
cd imgui-calc
```
3. Run build.py:
```markdown
python3 build.py
Enter build target: vs2022 
```

## Running the Project
1. After running build.py, the project can be run inside Visual Studio. A more robust and cross-platform version of the project will be added in the future.
3. An information and introduction window will popup prompting you to start the calculator.
