# Autonomous Car Parking Robot

Self-navigating robot that detects an open parking space and reverses into it autonomously.

## Hardware Used
- Arduino Nano V3
- L298N Motor Driver
- 2× DC Motors
- Servo Motor (steering)
- 3× HC-SR04 Ultrasonic Sensors

## How It Works
Three ultrasonic sensors (front, left, right) continuously measure distance to
detect obstacles and open space. When the side sensor detects a gap wide enough
to fit the robot, it stops, engages the servo to steer, and reverses into the
space — straightening out once centered, similar to how a real parallel-parking
assist system works on a much smaller scale.

## Tech Stack
`Arduino Nano V3` `Embedded C` `L298N` `HC-SR04 Ultrasonic` `Servo Control`

## What I Learned
Getting consistent ultrasonic readings was harder than expected — reflections
off angled or soft surfaces gave inaccurate distances, so the gap-detection
threshold needed real-world tuning rather than just trusting the sensor's rated
range. Timing the reverse-and-straighten servo sequence also took trial and
error to get the robot centered in the spot instead of ending up at an angle.
