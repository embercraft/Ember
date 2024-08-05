#!/usr/bin/env python

import os
import subprocess
from pathlib import Path
import Utils
import shutil

EMBER_VULKAN_VERSION = '1.3.283.0'
LINUX_VULKAN_SDK_INSTALLER_URL = f'https://sdk.lunarg.com/sdk/download/{EMBER_VULKAN_VERSION}/linux/vulkansdk-linux-x86_64-{EMBER_VULKAN_VERSION}.tar.xz'
OUTPUT_DIRECTORY = f'Ember/Vendor/VulkanSDK'
VULKAN_SDK_TAR_PATH = f'{OUTPUT_DIRECTORY}/VulkanSDK.tar.xz'
TEMP_DIRECTORY = f'{OUTPUT_DIRECTORY}/temp'

def install_vulkan_sdk():
    print(f'Downloading {LINUX_VULKAN_SDK_INSTALLER_URL} to {VULKAN_SDK_TAR_PATH}')
    Utils.download_file(LINUX_VULKAN_SDK_INSTALLER_URL, VULKAN_SDK_TAR_PATH)
    print("Done!")
    print("Extracting Vulkan SDK...")
    
    os.makedirs(TEMP_DIRECTORY, exist_ok=True)
    subprocess.run(['tar', '-xJf', VULKAN_SDK_TAR_PATH, '-C', TEMP_DIRECTORY])
    
    for item in Path(TEMP_DIRECTORY).iterdir():
        shutil.move(str(item), OUTPUT_DIRECTORY)
    
    shutil.rmtree(TEMP_DIRECTORY)
    os.remove(VULKAN_SDK_TAR_PATH)
    print("Vulkan SDK installed successfully.")

def main():
    if not os.path.exists(OUTPUT_DIRECTORY) or not os.listdir(OUTPUT_DIRECTORY):
        os.makedirs(OUTPUT_DIRECTORY, exist_ok=True)
        install_vulkan_sdk()
    else:
        print(f"Vulkan SDK version {EMBER_VULKAN_VERSION} is already present at {OUTPUT_DIRECTORY}")

if __name__ == "__main__":
    main()
