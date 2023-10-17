function MoveLeft(deltaVel, spd)
  return deltaVel - spd
end

function MoveRight(deltaVel, spd)
  return deltaVel + spd
end

function Pause(deltaVel) 
  return deltaVel
end

function UpdateMovements(left, right, deltaVel, spd)
  if left then
    return MoveLeft(deltaVel, spd)
  elseif right then
    return MoveRight(deltaVel, spd)
  else
    return Pause(deltaVel)
  end
end