import sys
import platform
import subprocess

build_help = "buildhelp.txt"
premake5_path = "./vendor/bin/premake/premake5.exe"

def build(action:str):
    system = platform.system()
    
    match system:
        case "Windows":
            print(f"Building for Windows ({action})..")
            subprocess.run([premake5_path, action])
        case "Linux":
            print(f"Building for Linux ({action})..")
            subprocess.run([premake5_path, action])
        case "Darwin": # MacOS
            print(f"Building for MacOS ({action})..")
            subprocess.run([premake5_path, action])
        case _:
            print("Your operating system is unsupported.")

def print_help():
    try:
        help_file = open(build_help)
        print("Please select a build target. Please ensure that your system supports your selected build target!")
        print(help_file.read())
    except:
        print(build_help, "not found.")
    finally:
        help_file.close()
    print("")
    return

def main():
    while True:
        action = input("Enter build target: ")
        print("")
        # Empty action string
        if not action or  action.lower()== 'help':
            print_help()
            continue
        else:
            build(action)
            break
            

if __name__ == "__main__":
    main()