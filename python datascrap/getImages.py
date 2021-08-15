import mwclient

with open('urlist.txt') as file:
    lines = [i.strip() for i in file]

for url in lines:
    file = open("downloads/"+url, "wb")
    url = "https://lol.gamepedia.com/File:"+url
    response = requests.get(url)
    
    file.write(response.content)
    print(url)
    file.close()
    
print("Process Finished")
