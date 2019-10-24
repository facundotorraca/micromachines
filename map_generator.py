import yaml

filename = "map.yml"
map_col = 50
map_row = 50

with open('map.yml', 'w') as outfile:
    for i in range(map_row):
        for j in range(map_col):
            entitie_type = {"type":"TYPE_GRASS"}
            entitie_coord = {"x":i, "y":j}
            entitie_rot = {"rotation":0}
            
            yaml.dump(entitie_type, outfile, default_flow_style = False)
            yaml.dump(entitie_coord, outfile, default_flow_style = False)
            yaml.dump(entitie_rot, outfile, default_flow_style = False)
