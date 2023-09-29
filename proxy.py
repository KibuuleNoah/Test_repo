import requests

r = requests.get("https://ipinfo.io/json")
print(r.text)

if r.status_code == 200:
    print("access granted")
