import mwclient
import time
import datetime as dt
from datetime import date, timedelta
import json

def getGames(startDate, endDate):
    #startDate Example: "2021-08-01"
    startDate=dt.datetime.strptime(startDate, "%Y-%m-%d").date()

    #endDate Example: "2021-08-01"
    endDate=dt.datetime.strptime(endDate, "%Y-%m-%d").date()

    site = mwclient.Site('lol.fandom.com', path='/')
    response = site.api('cargoquery',
        limit = "max",
        tables = "ScoreboardGames=SG",
        #join_on = "SG.UniqueGame=SP.UniqueGame",
        fields = "SG.Tournament, SG.DateTime_UTC, SG.Team1, SG.Team2, SG.Winner",
        where = "SG.DateTime_UTC >= '" + str(startDate) + " 00:00:00' AND SG.DateTime_UTC <= '" + str(endDate+dt.timedelta(1)) + " 00:00:00'"
    )
    parsed = json.dumps(response)
    decoded = json.loads(parsed)
    time.sleep(2)
    return decoded

i = 0
while(i < 31):
    i += 1
    out_file = open("data\\games\\"+str(i)+".json", "w") 
    date = "2021-07-"+str(i)
    games = getGames(date, date)
    json.dump(games, out_file, indent = 6) 
    out_file.close()

