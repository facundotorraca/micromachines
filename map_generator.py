import yaml
import collections

filename = "map.yml"
map_col = 50
map_row = 50

with open('map.yml', 'w') as outfile:
    for i in range(map_row):
        for j in range(map_col):
            entitie = collections.OrderedDict()
            entitie["type"] = "TYPE_GRASS"
            entitie["x"] = i
            entitie["y"] = j
            entitie["rotation"] = 0
            yaml.dump(entitie, outfile, default_flow_style = False)
