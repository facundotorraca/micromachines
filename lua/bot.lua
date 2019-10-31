i=-2;
map = {}
car = {turning = 0, increasing = 0, waitTurn = 0}

function init(keysDef, actionsDef)
  keys = keysDef
  actions = actionsDef
end

function addTile(xi, xf, yi, yf, value)
  for x=xi, xf do
    for y=yi, yf do
      if map[x] == nil then map[x] = {} end
      map[x][y] = value
    end
  end
end

function updateCar(newCar)
  for key, value in pairs(newCar) do
    car[key] = value
  end
end

function getDirections(rot_ini)
  local rot = math.rad(math.fmod(rot_ini, 360))
  local sen_a = math.sin(rot)
  local sen = sen_a * -1
  local cos = math.cos(rot)
  return sen, cos
end

function calcFuture(dirX, dirY, seg)
  local velX = car.vel * dirX
  local velY = car.vel * dirY
  local futureX = math.floor(car.posX + (velX * seg))
  local futureY = math.floor(car.posY + (velY * seg))
  return futureX, futureY
end

function canGo(dirX, dirY, seg)
  local futureX, futureY = calcFuture(dirX, dirY, seg)
  if map[futureX] == nil or map[futureX][futureY] == nil then
    return false
  end
  print(map[futureX][futureY])
  if map[futureX][futureY] >= 3 and map[futureX][futureY] <= 55 then
    return true
  end
  return false
end

function canTurn(to)
  local dirX, dirY = getDirections(car.rot + to)
  return canGo(dirX, dirY, 0.5)
end

function canTurnLeft()
  return canTurn(-45)
end

function canTurnRight()
  return canTurn(45)
end

function stopTurn()
  local turning = car.turning
  car.turning = 0
  car.waitTurn = 0
  if (turning == 1) then
    return actions.release, keys.right
  end
  return actions.release, keys.left
end

function keepTurning()
  if car.turning == 1 then
    return actions.press, keys.right
  end
  return actions.press, keys.left
end

function increase()
  print("INCREASE")
  car.increasing = 1
  return actions.press, keys.up
end

function turnRight()
  print("TURN RIGHT")
  car.turning = 1
  return actions.press, keys.right
end

function turnLeft()
  print("TURN LEFT")
  car.turning = 2
  return actions.press, keys.left
end

function stop()
  print("STOP")
  car.increasing = 0
  car.waitTurn = 1
  return actions.release, keys.up
end

function decideTurning(dirX, dirY)
  print("DECIDE TURNING")
  if canGo(dirX, dirY, 0.5) then
    return stopTurn()
  end
  return keepTurning()
end


function decideStoping(dirX, dirY)
  print("DECIDE STOPING")
  if car.waitTurn == 0 then
    return increase()
  end
  if canTurnRight() then
    return turnRight()
  elseif canTurnLeft() then
    return turnLeft()
  else
    return stop()
  end
end

function decideIncreasing(dirX, dirY)
  print("DECIDE INCREASING")
  if canGo(dirX, dirY, 0.4) then
    return increase()
  end
  return stop()
end


function decide()
  local dirX, dirY = getDirections(car.rot)
  if car.turning ~= 0 then
    return decideTurning(dirX, dirY)
  end
  if car.increasing == 0 then
    return decideStoping()
  end
  return decideIncreasing(dirX, dirY)
end

function fakeInit()
  init({up=1, down=2, left= 3, right=4}, {press=1, release=2})
  createFakeCar()
  createFakeMap()
end

function createFakeMap()
  addTile(1, 100, 1, 100, 40)
end


function createFakeCar ()
  updateCar({posX = 5, posY=5, rot = 180, vel=20})
end