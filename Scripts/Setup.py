#!.venv/bin/python

import subprocess
import importlib.metadata

def install(package):
    print(f"Installing {package} module...")
    subprocess.check_call(['python', '-m', 'pip', 'install', package])

def validate_package(package):
    required = {package}
    installed = {pkg.metadata['Name'].lower() for pkg in importlib.metadata.distributions()}
    missing = required - installed

    if missing:
        install(package)

def validate_packages():
    validate_package('requests')
    validate_package('fake-useragent')

if __name__ == "__main__":
    validate_packages()
