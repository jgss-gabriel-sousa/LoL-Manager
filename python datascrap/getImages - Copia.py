import mwclient
site = mwclient.Site('lol.gamepedia.com', path='/')

with open('urlist.txt') as file:
    lines = [i.strip() for i in file]

for url in lines:
    newFile = url
    url = "https://lol.gamepedia.com/File:"+url
    file = site.images[url]
    with open(newFile, 'wb') as fd:
        image.download(fd)
    print(url)
    
print("Process Finished")
