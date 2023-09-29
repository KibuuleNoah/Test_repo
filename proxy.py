import requests

r = requests.get("https://ipinfo.io/json")
print(r.text)

