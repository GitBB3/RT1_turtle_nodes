#!/usr/bin/env python3

import rospy
from turtlesim.msg import Pose
from geometry_msgs.msg import Twist
from turtlesim.srv import Spawn

turtle_name = "turtle1"
pub = rospy.Publisher(turtle_name + "/cmd_vel", Twist, queue_size=1)

Vx, Vy, Wz = 0,0,0

def turtleCallback(msg):
	global Vx, Vy, Wz
	#rospy.loginfo("Moving turtle pose @[%f, %f, %f]", msg.x, msg.y, msg.theta)
	
	vel = Twist()
	vel.linear.x = Vx
	vel.linear.y = Vy
	vel.angular.z = Wz
	
	print("Vx Vy Wz: ", Vx, Vy, Wz)
	pub.publish(vel)
	
	

def turtleMove():
	rospy.init_node("turtle_move")
	rospy.wait_for_service("/spawn")
	client2 = rospy.ServiceProxy("/spawn", Spawn)
	client2(2.0, 1.0, 0.0, "turtle2")
	rate = rospy.Rate(0.1)
	while not rospy.is_shutdown():
		global Vx, Vy, Wz, turtle_name
		turtle_name = input("Which turtle do you want to move (turtle1 or turtle2):")
		Vx = float(input("Vx:"))
		Vy = float(input("Vy:"))
		Wz = float(input("Wz:"))
		
		rate.sleep()
		
		pub = rospy.Publisher(turtle_name + '/cmd_vel', Twist, queue_size=1)
		rospy.Subscriber(turtle_name + '/pose', Pose, turtleCallback)
		print("Onara1")

		#rospy.sleep(1) 
		rate.sleep()
		print("Onara2")
		#rospy.spin()


if __name__ == '__main__':
	turtleMove()
