deltaVel = 0;

function MoveLeft(deltaVel, spd)
  return deltaVel - spd

function MoveRight(deltaVel, spd)
  return deltaVel + spd

function Pause(deltaVel) 
  return deltaVel

function UpdateMovements(left, right, deltaVel, spd)
  if left then
    MoveLeft(left, right, deltaVel, spd)
  else if right then
    MoveRight(left, right, deltaVel, spd)
  else
    Pause(left, right, deltaVel)
  end     