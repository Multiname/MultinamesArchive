import subprocess
import time
import requests

token = "t1.9euelZqaiZTNlp3GjZzGz56SyYmaje3rnpWanpvMz5SYjMvNzZ2Vz46alMrl8_coAAZP-e9FMWwC_t3z92guA0_570UxbAL-zef1656Vmo2djpeVmJiWysqTns6LicmN7_zF656Vmo2djpeVmJiWysqTns6LicmN.ttABqXurl_14i6U8PBFpU7jLrl9ZKXjmXLIAs6VO6gk1SNToJE1Wv2yy3U0YHtm6tqAkBQNzjmGs3SHkw16MAA"
folder_id = "b1ggmcide7uen9dlppos"
root_path = "D:\Progs"

def synthesize(text):
    url = 'https://tts.api.cloud.yandex.net/speech/v1/tts:synthesize'
    headers = {'Authorization': 'Bearer ' + token, }
    data = {
        'folderId': folder_id,
        'text': text,
        'lang': 'ru-RU',
        'voice': 'omazh',
        'emotion': 'evil',
        'speed': '1.0',
        'format': 'lpcm',
        'sampleRateHertz': 48000,
    }

    with requests.post(url, headers=headers, data=data, stream=True) as resp:
        if resp.status_code != 200:
            raise RuntimeError("Invalid response received: code: %d, message: %s" % (resp.status_code, resp.text))
        
        for chunk in resp.iter_content(chunk_size=None):
            yield chunk

def write_file(text):
    filename = str(int(time.time()))
    with open(filename + ".raw", "wb") as f:
        for audio_content in synthesize(text):
            f.write(audio_content)

    time.sleep(2)

    return filename

def convert(filename):
    cmd = " ".join([
        root_path + "\sox-14-4-2\sox.exe",
        "-r 48000 -b 16 -e signed-integer -c 1",
        filename + ".raw",
        filename + ".wav",
    ])

    subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True)
 
def read_text():
    with open("text.txt", "r", encoding="UTF-8") as f:
        text = f.read()

    return text

convert(write_file(read_text()))
