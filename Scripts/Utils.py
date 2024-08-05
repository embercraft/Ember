#!.venv/bin/python

import requests
import sys
import time
from fake_useragent import UserAgent

def download_file(url, filepath):
    with open(filepath, 'wb') as f:
        ua = UserAgent()
        headers = {'User-Agent': ua.chrome}
        response = requests.get(url, headers=headers, stream=True)
        total = response.headers.get('content-length')

        if total is None:
            f.write(response.content)
        else:
            downloaded = 0
            total = int(total)
            start_time = time.time()
            for data in response.iter_content(chunk_size=max(int(total / 1000), 1024 * 1024)):
                downloaded += len(data)
                f.write(data)
                done = int(50 * downloaded / total)
                percentage = (downloaded / total) * 100
                elapsed_time = time.time() - start_time
                avg_kb_per_second = (downloaded / 1024) / elapsed_time
                avg_speed_string = f'{avg_kb_per_second:.2f} KB/s'
                if avg_kb_per_second > 1024:
                    avg_mb_per_second = avg_kb_per_second / 1024
                    avg_speed_string = f'{avg_mb_per_second:.2f} MB/s'
                sys.stdout.write(f'\r[{"█" * done}{"." * (50 - done)}] {percentage:.2f}% ({avg_speed_string})     ')
                sys.stdout.flush()
    sys.stdout.write('\n')

def yes_or_no():
    while True:
        reply = str(input('[Y/N]: ')).lower().strip()
        if reply[:1] == 'y':
            return True
        if reply[:1] == 'n':
            return False
