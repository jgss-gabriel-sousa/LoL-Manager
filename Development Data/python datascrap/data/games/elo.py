import pandas as pd
import numpy as np
import csv

df = pd.read_csv (r'G:\GIT\LoL-Manager\Development Data\python datascrap\data\games\games18-21.csv')

df.drop(labels=["title.DateTime UTC__precision"], inplace=True, axis=1)

mean_elo = 1000

elo_width = 400
k_factor = 64

teams = {}

def checkLeague(league):
    # Main Leagues ###################################################
    international = [
        "Worlds 2021 Main Event", "Worlds 2021 Play-In", "MSI 2021",
        "Worlds 2020 Main Event", "Worlds 2020 Play-In"
    ]
    na = [
        "LCS 2021 Championship","LCS 2021 Summer","LCS 2021 Mid-Season Showdown","LCS 2021 Spring","LCS 2021 Lock In",
        "LCS 2020 Summer Playoffs","LCS 2020 Summer","LCS 2020 Spring","LCS 2020 Spring Playoffs",
        "LCS 2019 Regional Finals","LCS 2019 Summer Playoffs","LCS 2019 Summer","LCS 2019 Spring","LCS 2019 Spring Playoffs"
    ]
    eu = [
        "LEC 2021 Summer Playoffs","LEC 2021 Summer","LEC 2021 Spring Playoffs","LEC 2021 Spring",
        "LEC 2020 Summer Playoffs","LEC 2020 Summer","LEC 2020 Spring Playoffs","LEC 2020 Spring",
        "LEC 2019 Regional Finals","LEC 2019 Summer Playoffs","LEC 2019 Summer","LEC 2019 Spring Playoffs","LEC 2019 Spring"
    ]
    korea = [
        "LCK 2021 Regional Finals","LCK 2021 Summer Playoffs","LCK 2021 Summer","LCK 2021 Spring Playoffs","LCK 2021 Spring",
        "LCK 2020 Regional Finals","LCK 2020 Summer Playoffs","LCK 2020 Summer","LCK 2020 Spring Playoffs","LCK 2020 Spring","KeSPA Cup 2020","LCK 2020 Spring Promotion","LCK 2020 Summer Promotion",
        "LCK 2019 Regional Finals","LCK 2019 Summer Playoffs","LCK 2019 Summer","LCK 2019 Spring Playoffs","LCK 2019 Spring","KeSPA Cup 2019","LCK 2019 Spring Promotion","LCK 2019 Summer Promotion"
    ]
    china = [
        "LPL 2021 Regional Finals","LPL 2021 Summer Playoffs","LPL 2021 Summer","LPL 2021 Spring Playoffs","LPL 2021 Spring",
        "LPL 2020 Regional Finals","LPL 2020 Summer Playoffs","LPL 2020 Summer","LPL 2020 Spring Playoffs","LPL 2020 Spring",
        "LPL 2019 Regional Finals","LPL 2019 Summer Playoffs","LPL 2019 Summer","LPL 2019 Spring Playoffs","LPL 2019 Spring"
    ]
    brazil = [
        "CBLOL 2021 Split 1","CBLOL 2021 Split 1 Playoffs","CBLOL 2021 Split 2","CBLOL 2021 Split 2 Playoffs",
        "CBLOL 2020 Split 1","CBLOL 2020 Split 1 Playoffs","CBLOL 2020 Split 2","CBLOL 2020 Split 2 Playoffs","CBLOL 2020 Split 1 Promotion","CBLOL 2020 Split 2 Promotion",
        "CBLOL 2019 Split 1","CBLOL 2019 Split 1 Playoffs","CBLOL 2019 Split 2","CBLOL 2019 Split 2 Playoffs","CBLOL 2019 Split 1 Promotion","CBLOL 2019 Split 2 Promotion"
    ]
    cis = [
        "LCL 2021 Summer Playoffs","LCL 2021 Summer","LCL 2021 Spring Playoffs","LCL 2021 Spring",
        "LCL 2020 Summer Playoffs","LCL 2020 Summer","LCL 2020 Spring Playoffs","LCL 2020 Spring","LCL 2020 Spring Open Cup",
        "LCL 2019 Spring Promotion","LCL 2019 Spring Open Cup","LCL 2019 Spring","LCL 2019 Spring Playoffs","LCL 2019 Summer Open Cup","LCL 2019 Summer","LCL 2019 Summer Playoffs"
    ]
    japan = [
        "LJL 2021 Summer Playoffs","LJL 2021 Summer","LJL 2021 Spring Playoffs","LJL 2021 Spring",
        "LJL 2020 Summer Playoffs","LJL 2020 Summer","LJL 2020 Spring Playoffs","LJL 2020 Spring",
        "LJL 2019 Spring Promotion","LJL 2019 Spring","LJL 2019 Spring Playoffs","LJL 2019 Summer","LJL 2019 Summer Playoffs"
    ]
    latam = [
        "LLA 2021 Closing Playoffs","LLA 2021 Closing","LLA 2021 Opening Playoffs","LLA 2021 Opening",
        "LLA 2020 Closing Playoffs","LLA 2020 Closing","LLA 2020 Opening Playoffs","LLA 2020 Opening","LLA 2020 Opening Promotion",
        "LLA 2019 Opening","LLA 2019 Opening Playoffs","LLA 2019 Closing","LLA 2019 Closing Playoffs"
    ]
    oceania = [
        "LCO 2021 Split 1","LCO 2021 Split 1 Playoffs","LCO 2021 Split 2","LCO 2021 Split 2 Playoffs",
        "OPL 2020 Split 1","OPL 2020 Split 1 Playoffs","OPL 2020 Split 2","OPL 2020 Split 2 Playoffs",
        "OPL 2019 Split 1 Promotion","OPL 2019 Split 1","OPL 2019 Split 1 Playoffs","OPL 2019 Split 2","OPL 2019 Split 2 Playoffs"
    ]
    sea = [
        "PCS 2021 Summer Playoffs","PCS 2021 Summer","PCS 2021 Spring Playoffs","PCS 2021 Spring","PCS 2021 Spring Promotion",
        "PCS 2020 Summer Playoffs","PCS 2020 Summer","PCS 2020 Spring Playoffs","PCS 2020 Spring",
        "LMS 2019 Regional Finals","LMS 2019 Summer Playoffs","LMS 2019 Summer","LMS 2019 Spring Playoffs","LMS 2019 Spring","LMS 2019 Spring Promotion","LMS 2019 Summer Promotion"
    ]
    lst = [
        "LST 2019 Spring","LST 2019 Summer","LST 2019 Summer Playoffs"
    ]
    turkey = [
        "TCL 2021 Summer Playoffs","TCL 2021 Summer","TCL 2021 Winter Playoffs","TCL 2021 Winter",
        "TCL 2020 Summer Playoffs","TCL 2020 Summer","TCL 2020 Winter Playoffs","TCL 2020 Winter",
        "TCL 2019 Winter Qualifiers","TCL 2019 Winter","TCL 2019 Winter Playoffs","TCL 2019 Summer","TCL 2019 Summer Playoffs"
    ]
    vietnam = [
        "VCS 2021 Summer Playoffs","VCS 2021 Summer","VCS 2021 Spring Playoffs","VCS 2021 Spring","VCS 2021 Spring Promotion","VCS 2021 Summer Promotion",
        "VCS 2020 Summer Playoffs","VCS 2020 Summer","VCS 2020 Spring Playoffs","VCS 2020 Spring","VCS 2020 Spring Promotion","VCS 2020 Summer Promotion",
        "VCS 2019 Spring Promotion","VCS 2019 Spring","VCS 2019 Spring Playoffs","VCS 2019 Summer Promotion","VCS 2019 Summer","VCS 2019 Summer Playoffs"
    ]

    # Regional Leagues ###################################################

    korea_ck = [
        "CK 2020 Spring","CK 2020 Spring Playoffs","CK 2020 Summer","CK 2020 Summer Playoffs",
        "CK 2019 Spring","CK 2019 Spring Playoffs","CK 2019 Summer","CK 2019 Summer Playoffs"
    ]
    china_secondary = [
        "LDL 2021 Spring","LDL 2021 Spring Playoffs","LDL 2021 Summer","LDL 2021 Summer Playoffs","LDL 2021 Summer Cup",
        "LDL 2020 Spring","LDL 2020 Summer","LDL 2020 Summer Playoffs",
        "LDL 2019 Spring","LDL 2019 Spring Playoffs","LDL 2019 Summer","LDL 2019 Summer Playoffs"
    ]
    sea_secondary = [
        "ECS 2019 Spring","ECS 2019 Spring Playoffs","ECS 2019 Summer","ECS 2019 Summer Playoffs"
    ]
    brcc = [
        "BRCC 2020 Split 1 Promotion","BRCC 2020 Split 1","BRCC 2020 Split 1 Playoffs","BRCC 2020 Split 2 Promotion","BRCC 2020 Split 2","BRCC 2020 Split 2 Playoffs",
        "BRCC 2019 Split 1 Promotion","BRCC 2019 Split 1","BRCC 2019 Split 1 Playoffs","BRCC 2019 Split 2 Promotion","BRCC 2019 Split 2","BRCC 2019 Split 2 Playoffs"
    ]
    regional_latam = [
        "Regional Sur 2021","Regional Norte 2021",
        "Regional Sur 2020","Regional Norte 2020",
        "Regional Sur 2019","Regional Norte 2019"
    ]
    eu_masters = [
        "EM 2021 Summer Main Event","EM 2021 Spring Main Event","EM 2021 Summer Play-In","EM 2021 Spring Play-In",
        "EM 2020 Summer Main Event","EM 2020 Spring Main Event","EM 2020 Summer Play-In","EM 2020 Spring Play-In",
        "EM 2019 Summer Main Event","EM 2019 Spring Main Event","EM 2019 Summer Play-In","EM 2019 Spring Play-In"
    ]

    if(league in na):
        return 1200
    elif(league in eu):
        return 1500
    elif(league in eu_masters):
        return 1000
    elif(league in korea):
        return 1500
    elif(league in korea_ck):
        return 1000
    elif(league in china):
        return 1500
    elif(league in china_secondary):
        return 1000
    elif(league in brazil):
        return 1000
    elif(league in brcc):
        return 667
    elif(league in cis):
        return 1000
    elif(league in japan):
        return 1000
    elif(league in latam):
        return 1000
    elif(league in regional_latam):
        return 667
    elif(league in oceania):
        return 1000
    elif(league in sea):
        return 1200
    elif(league in sea_secondary):
        return 800
    elif(league in lst):
        return 1000
    elif(league in turkey):
        return 1000
    elif(league in vietnam):
        return 1200
    else:
        return 0


for row in df.itertuples():
    if(row[3] not in teams):
        if(checkLeague(row[1]) != 0):
            teams[row[3]] = checkLeague(row[1])
    else:
        if(teams[row[3]] < checkLeague(row[1])):
            teams[row[3]] = checkLeague(row[1])

    if(row[4] not in teams):
        if(checkLeague(row[1]) != 0):
            teams[row[4]] = checkLeague(row[1])
    else:
        if(teams[row[4]] < checkLeague(row[1])):
            teams[row[4]] = checkLeague(row[1])

    
def update_elo(winner_elo, loser_elo):
    expected_win = expected_result(winner_elo, loser_elo)
    change_in_elo = k_factor * (1-expected_win)
    winner_elo += change_in_elo
    loser_elo -= change_in_elo
    return winner_elo, loser_elo

def expected_result(elo_a, elo_b):
    expect_a = 1.0/(1+10**((elo_b - elo_a)/elo_width))
    return expect_a

def getTeamName(id):
    return teams[id]


for row in df.itertuples():    
    if row[3] in teams:
        if row[4] in teams:
            if(row[5] == 1):
                teams[row[3]], teams[row[4]] = update_elo(teams[row[3]], teams[row[4]])
            else:
                teams[row[4]], teams[row[3]] = update_elo(teams[row[4]], teams[row[3]])


teams = dict(sorted(teams.items(), key=lambda item: item[1], reverse=True))

for i in list(teams.keys()):
    if(teams[i] < 0):
        del teams[i]

print(teams)

filepath = r"G:\GIT\LoL-Manager\Development Data\python datascrap\data\games\elo.csv"

pd.DataFrame.from_dict(data=teams, orient='index').to_csv(filepath, header=True, index=True)

read_file = pd.read_csv (r"G:\GIT\LoL-Manager\Development Data\python datascrap\data\games\elo.csv")
read_file.to_excel (r"G:\GIT\LoL-Manager\Development Data\python datascrap\data\games\elo.xlsx", index = None, header=True)