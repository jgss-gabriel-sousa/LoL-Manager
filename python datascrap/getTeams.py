import mwclient
import json
from io import StringIO

site = mwclient.Site('lol.fandom.com', path='/')
response = site.api('cargoquery',
	limit = 'max',
	tables = "Teams",
	fields = "Name,Short,Image,TeamLocation,Location,Facebook,IsDisbanded,RenamedTo"
)
parsed = json.dumps(response)
decoded = json.loads(parsed)

out_file = open(r"data\team.json", "w") 
json.dump(decoded, out_file, indent = 6) 
out_file.close() 