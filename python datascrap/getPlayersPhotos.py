import mwclient
import urllib.request
import json
import re
import time
import os
from PIL import Image

def get_filename_url_to_open(site, filename, player, size=None):
    pattern = r'.*src\=\"(.+?)\".*'
    size = '|' + str(size) + 'px' if size else ''
    to_parse_text = '[[File:{}|link=%s]]'.format(filename, size)
    result = site.api('parse', title='Main Page', text=to_parse_text, disablelimitreport=1)
    parse_result_text = result['parse']['text']['*']

    url = re.match(pattern, parse_result_text)[1]
    folder = "G:\GIT\LoL-Manager\python datascrap\data\player images\\"
    urllib.request.urlretrieve(url, folder + player + '.png')

def imagesManipulation(player):
    path = "G:\GIT\LoL-Manager\python datascrap\data\player images\\"
    image = Image.open(path+player+'.png')

    #resize
    try:
        image.thumbnail((256, 256))
        image.save(path+"resize\\" + player + ".png")
        image = Image.open(path+"resize\\"+player+'.png')
        if(image.size[0] < 256 or image.size[1] < 256):
            x_crop = (image.size[0]/2)-128, (image.size[0]/2)+128
            box = (x_crop[0], 0+(image.size[1]-256), x_crop[1], 256+(image.size[1]-256))
            image = image.crop(box)
            image.save(path+"resize\\" + player + ".png")
    except:
        print(player+" fail in resizing")

    #crop
    try:
        image = Image.open(path+player+'.png')
        image.thumbnail((256, 256))
        image.save(path+"crops\\"+player+".png")
        image = Image.open(path+"crops\\"+player+'.png')
        x_crop = (image.size[0]/2)-128, (image.size[0]/2)+128
        box = (x_crop[0], 0, x_crop[1], 256)
        image = image.crop(box)
        image.save(path+"crops\\" + player + ".png")
    except:
        print(player+" fail in cropping")


players = set(line.strip() for line in open("G:\GIT\LoL-Manager\python datascrap\players.txt"))
faileds = []

while(len(players) > 0):
    player = players.pop()
    site = mwclient.Site('lol.fandom.com', path='/')
    response = site.api('cargoquery',
                        limit=1,
                        tables="PlayerImages",
                        fields="FileName",
                        where='Link="%s"' % player,
                        format="json"
                        )
    parsed = json.dumps(response)
    decoded = json.loads(parsed)
    
    try:
        url = str(decoded['cargoquery'][0]['title']['FileName'])
        get_filename_url_to_open(site, url, player)
        print(player+" OK")
        imagesManipulation(player)
        time.sleep(2)
    except:
        faileds.append(player)
        print(player+" not found")

print(faileds)