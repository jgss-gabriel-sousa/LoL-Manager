import mwclient
import time
import datetime as dt
from datetime import date, timedelta
import json
import pandas as pd

def RequestGamesFromLeaguepediaAPI(date): #Get all games from a specified day.
    site = mwclient.Site('lol.fandom.com', path='/')
    response = site.api('cargoquery',
        limit = "max",
        tables = "ScoreboardGames=SG",
        fields = "SG.Tournament, SG.DateTime_UTC, SG.Team1, SG.Team2, SG.Winner",
        where = "SG.DateTime_UTC >= '" + str(date) + " 00:00:00' AND SG.DateTime_UTC <= '" + str(date+dt.timedelta(1)) + " 00:00:00'"
    )
    parsed = json.dumps(response)
    decoded = json.loads(parsed)
    time.sleep(1)
    print(str(date)+" OK")
    return decoded

def GetGamesToDataFrame(StartDate):
    gamesData = pd.DataFrame()

    while(str(StartDate) != str(date.today())): 
        StartDate += timedelta(days=1)

        games = RequestGamesFromLeaguepediaAPI(StartDate)
        df = pd.json_normalize(games, record_path =['cargoquery'])

        if(len(gamesData) == 0):
            gamesData = df
        else:
            gamesData = pd.concat([df,gamesData])
    
    return gamesData
    
def SaveGamesDataFrame(data, filePath):
    data.to_csv(filePath, index = None)


StartDate = date.today()-timedelta(days=365)

gamesDF = GetGamesToDataFrame(StartDate)

filePath = r"G:\GIT\LoL-Manager\python datascrap\data\games\games.csv"
SaveGamesDataFrame(gamesDF, filePath)