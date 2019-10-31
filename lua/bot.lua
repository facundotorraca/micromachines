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
      --print(x, y)
    end
  end
end

function updateCar(newCar)
  for key, value in pairs(newCar) do
    car[key] = value
  end
end

function getDirections(rot_ini)
  print("GET DIR")
  local rot = math.rad(math.fmod(rot_ini, 360))
  local sen_a = math.sin(rot)
  local sen = sen_a * -1
  local cos = math.cos(rot)
  return sen, cos
end

function canGo(futureX, futureY)
  if map[futureX] == nil then
    print("FALSE NILL")
    return false
  elseif map[futureX][futureY] >= 3 and map[futureX][futureY] <= 55 then
    print(map[futureX][futureY])
    print("TRUE")
    return true
  end
  print(map[futureX][futureY])
  print("FALSE")
  return false
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
  print("CALCU")
  print(dirX, dirY)
  local velX = car.vel * dirX
  local velY = car.vel * dirY
  local futureX = math.floor(car.posX + (velX * 0.7))
  local futureY = math.floor(car.posY + (velY * 0.7))
  print(futureX, futureY)
  return futureX, futureY
end


function decide()
  print("DECIDE")
  local dirX, dirY = getDirections(car.rot)
  local futureX, futureY = calcFuture(dirX, dirY)
  if not canGo(futureX, futureY) then
    if canTurnLeft() then
      print("TURN LERFT")
      return actions.press, keys.left
    elseif canTurnRight() then
      print("TURN RIGHT")
      return actions.press, keys.right
    else
      print("STOP")
      return actions.release, keys.up
    end
  end
  print("GO")
  return actions.press, keys.up
end
