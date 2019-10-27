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

function getDirections(rot)
  if 337 <= rot and rot < 22 then
    return 0, 1
  elseif 22 <= rot and rot < 67 then 
    return 1, 1
  elseif 67 <= rot and rot < 112 then
    return 1, 0
  elseif 112 <= rot and rot < 157 then
    return 1, -1
  elseif 157 <= rot and rot < 202 then
    return 0, -1
  elseif 202 <= rot and rot < 247 then
    return -1, -1
  elseif 247 <= rot and rot < 292 then
    return -1, 0
  elseif 292 <= rot and rot < 337 then
    return -1, 1
end

function canGo(futureX, futureY)
  return ~(0 > futureX or futureX > 100 or 0 > futureY or futureY > 100)

function canTurn(to)
  local dirX, dirY = getDirections(car.rot + to)
  local futureX = car.posX + (3 * dirX)
  local futureY = car.posY + (3 * dirY)
  return canGo(futureX, futureY)
end

function canTurnLeft()
  return canTurn(45)
end

function canTurnRight()
  return canTurn(-45)
end



function decide()
  print("HOLA DESDE DECIDE")
  local dirX, dirY = getDirections(car.rot)
  local futureX = car.posX + (3 * dirX)
  local futureY = car.posY + (3 * dirY)
  if ~canGo(futureX, futureY) then
    if canTurnLeft() then
      return actions.press, keys.left
    elseif canTurnRight() then
      return actions.press, keys.right
    else
      return actions.release, keys.up
    end
  end
  return actions.press, keys.up
end
