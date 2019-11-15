i=-2;
map = {}
car = {turning = 0, increasing = 0, waitTurn = 0, inited = false }
TO_KEEP_AHEAD = 1
TO_STOP_TURN = 1
TO_TURN = 1.2
ANGLE = 60
STEP = 0.1

function init(keysDef, actionsDef)
  keys = keysDef
  actions = actionsDef
end

function resetCar()
  car.turning = 0;
  car.increasing = 0;
  car.waitTurn = 0;
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
  car.inited = true
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
  if map[futureX][futureY] == 8 or map[futureX][futureY] == 10 or map[futureX][futureY] == 26  or map[futureX][futureY] == 27 then
    return true
  end
  if map[futureX][futureY] == 28 or map[futureX][futureY] == 55  then
    return true
  end
  if map[futureX][futureY] >= 63 and map[futureX][futureY] <= 89 then
    return true
   end
  return false
end

function canGoAhead(dirX, dirY, seg)
  for k=0.5, seg, STEP do
    if not canGo(dirX, dirY, k) then
      return false
    end
  end
  return true
end

function canTurn(to)
  local dirX, dirY = getDirections(car.rot + to)
  return canGoAhead(dirX, dirY, TO_TURN)
end

function canTurnLeft()
  return canTurn(-ANGLE)
end

function canTurnRight()
  return canTurn(ANGLE)
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
  car.increasing = 1
  return actions.press, keys.up
end

function turnRight()
  car.turning = 1
  return actions.press, keys.right
end

function turnLeft()
  car.turning = 2
  return actions.press, keys.left
end

function stop()
  car.increasing = 0
  car.waitTurn = 1
  return actions.release, keys.up
end

function decideTurning(dirX, dirY)
  if canGoAhead(dirX, dirY, TO_STOP_TURN) then
    return stopTurn()
  end
  return keepTurning()
end


function decideStoping(dirX, dirY)
  if car.waitTurn == 0 then
    return increase()
  end
  local toLeft = canTurnLeft()
  local toRight = canTurnRight()
  if toLeft and  not toRight then
    return turnLeft()
  elseif toRight and not toLeft then
    return turnRight()
  else
    return stop()
  end
end

function decideIncreasing(dirX, dirY)
  if canGoAhead(dirX, dirY, TO_KEEP_AHEAD) then
    return increase()
  end
  return stop()
end


function decide()
  if(not car.inited) then
    print("CAR NOT INITED", car.inited)
    return stop()
  end
  local dirX, dirY = getDirections(car.rot)
  if car.vel == 0 then
    resetCar();
    return increase()
  end
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