i=-2;
map = {}
car = {}

function init(keysDef, actionsDef)
    keys = keysDef
    actions = actionsDef
end

function addTile(x, y, value) 
  if map[x] == nil then map[x] = {} end
  map[x][y] = value
end

function updateCar(newCar)
  for key, value in pairs(newCar) do
    car[key] = value
  end
end

function decide()
    print("HOLA DESDE DECIDE")
    local action
    local key
    if (i == 0) then
        i = i + 1
        return actions.press, keys.up
    end
    if (i == 40) then
        return actions.release, keys.up
    end
    i = i + 1
    local aux = math.fmod(i, 4)
    if (aux == 0) or (aux == 1) then
        key = keys.rigth
    else
        key = keys.left
    end
    aux = math.fmod(i,2)
    if (aux == 0) then
        action = actions.press
    else
        action = actions.release
    end

    return action, key
end
