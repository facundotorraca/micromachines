i=-2;
map = {}
car = {}

function init(keysDef, actionsDef)
  keys = keysDef
  actions = actionsDef
end

function addTile(xi, xf, yi, yf, value)
  for x=xi, xf do
    for y=yi, yf do
      if map[x] == nil then map[x] = {} end
      map[x][y] = value
      print(x, y)
    end
  end
end

function updateCar(newCar)
  for key, value in pairs(newCar) do
    car[key] = value
  end
end

function getDirections(rot_ini)
  local rot = math.fmod(rot_ini, 360)
  if 337 <= rot or rot < 22 then
    return 0, 1
  elseif 22 <= rot and rot < 67 then 
    return -0.5, 0.5
  elseif 67 <= rot and rot < 112 then
    return -1, 0
  elseif 112 <= rot and rot < 157 then
    return -0.5, -0.5
  elseif 157 <= rot and rot < 202 then
    return 0, -1
  elseif 202 <= rot and rot < 247 then
    return 0.5, -0.5
  elseif 247 <= rot and rot < 292 then
    return 1, 0
  elseif 292 <= rot and rot < 337 then
    return 0.5, 0.5
  end
  return 0, 0
end

function canGo(futureX, futureY)
  print(futureX, futureY)
  if map[futureX] == nil then
    return false
  elseif map[futureX][futureY] == nil then
    return false
  end
  return true
end

function canTurn(to)
  local dirX, dirY = getDirections(car.rot + to)
  local futureX, futureY = calcFuture(dirX, dirY)
  return canGo(futureX, futureY)
end

function canTurnLeft()
  print("LEFT")
  return canTurn(-45)
end

function canTurnRight()
  print("RIGHT")
  return canTurn(45)
end

function calcFuture(dirX, dirY)
  local futureX = car.posX + (100 * dirX)
  local futureY = car.posY + (100 * dirY)
  return futureX, futureY
end


function decide()
  print("DECIDE")
  print(car.posX, car.posY, car.rot)
  local dirX, dirY = getDirections(car.rot)
  local futureX, futureY = calcFuture(dirX, dirY)
  if not canGo(futureX, futureY) then
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
