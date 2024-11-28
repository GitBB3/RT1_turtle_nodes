# assignment1_rt

## Description
Package of 2 nodes in C++ (Python folder "/script" is work in progress):
### UI: 
- spawns a new turtle "turtle2" in the environment;
- The user should be able to select the robot they want to control (turtle1 or turtle2), and the velocity of the robot.

### Distance: 
- checks the relative distance between the 2 turtles;
- stops the turtles when they are too close to each other;
- stops a turtle if it is too close to a boundary of the environment.


## Run the nodes

### Lauchfile (bêta)
Run in 2 different terminals:
- roslaunch assignment1_rt assignment1_rt.launch
- rosrun assignment1_rt Distance (should be integrated in the launchfile - and run correctly)

### Run the files one by one in different terminals
1) rosrun turtlesim turtlesim_node
2) rosrun assignment1_rt UI
3) rosrun assignment1_rt Distance

## Move the turtles

#### The terminal for UI should display the following:
- "Which one do you want to move ? turtle1 or turtle2:"
  
(write turtle1 or turtle2)
- "Choose the speed {Vx, Vy, Wz}:"
- "Vx:"
  
(write the linear speed along x)
- "Vy:"
  
(write the linear speed along y)
- "Wz:"
  
(write the angular speed with respect to z)

#### The terminal for Distance:
Shows the distance between the turtles continuously, spawns Warning message "Turtle x: Collision risk!" if there is a risk of collision of turtle x with the other turtle, or with the wall.
