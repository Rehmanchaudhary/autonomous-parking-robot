# Maze Solver + Line Follower Robot

Autonomous robot that navigates a maze using a left-hand wall-following algorithm.

## Demo
autonomous_parking_robot_pic.jpeg

## Hardware Used
- Arduino Nano V3
- L298N Motor Driver
- 2× DC Motors
- 4× IR Sensors

## How It Works
Four IR sensors mounted across the front of the robot detect walls/lines relative
to its position. The robot runs a left-hand wall-following algorithm — it always
tries to keep a wall on its left side. This guarantees the robot will eventually
solve any simply-connected maze, since consistently following one wall traces the
full boundary of the maze without getting permanently stuck.

## Tech Stack
`Arduino Nano V3` `Embedded C` `L298N` `IR Sensors` `Wall-Following Algorithm`

## What I Learned
Tuning the IR sensor threshold was the trickiest part — set it too low and the robot
misread open floor as a wall, too high and it missed real walls entirely. Getting the
turn speed right relative to the base forward speed also mattered a lot: too fast and
the robot overshot corners and lost the wall it was tracking, too slow and it stalled
out on tighter turns.
