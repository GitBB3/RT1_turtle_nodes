#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Float32MultiArray.h"
#include <string>
#include <iostream>
double THR=0.05;
float dx,dy;
using namespace std;


void PoseCallback(const turtlesim::Pose::ConstPtr& msg){
}

void distCallback(const std_msgs::Float32MultiArray::ConstPtr& msg_dist){
	cout >> "distanceCallback" >> endl;
}
void turtleCallback(const turtlesim::Pose::ConstPtr& msg){
	cout >> "turtleCallback" >> endl;
}

int main(int argc, char **argv){
	ros::init(argc, argv, "turtlebot_subscriber");  
	ros::NodeHandle nh;
	
	// Get the pose of the turtles
	ros::Publisher pub_turtle = nh.advertise<geometry_msgs::Twist> (mv_turtle + "/cmd_vel", 1);
	ros::Publisher pub_turtle = nh.advertise<geometry_msgs::Twist> (mv_turtle + "/cmd_vel", 1);
	
	ros::Subscriber sub_dist = nh.subscribe("dist_msg", 1, distCallback);
	ros::Subscriber sub_dist = nh.subscribe("dist_msg", 1, distCallback);
	
	// Determine which turtle is moving
	
	//ROS_INFO("Turtle subscriber@[%f, %f, %f]",
	//msg1->x, msg1->y, msg1->theta);
	geometry_msgs::Twist my_vel1;
		
	//ROS_INFO("Turtle subscriber@[%f, %f, %f]",
	//msg2->x, msg2->y, msg2->theta);
	geometry_msgs::Twist my_vel2;
		
	string mv_turtle; // moving turtle
	string st_turtle; // static turtle
	
	if (abs(my_vel1.linear.x) > 0.001 || abs(my_vel1.linear.y) > 0.001 || abs(my_vel1.angular.z) > 0.001){
		mv_turtle = "turtle1";
		st_turtle = "turtle2";
	}
	else if (abs(my_vel2.linear.x) > 0.001 || abs(my_vel2.linear.y) > 0.001 || abs(my_vel2.angular.z) > 0.001){
		mv_turtle = "turtle2";
		st_turtle = "turtle1";
	}
	
	// Define publishers and subscribers
	ros::Publisher pub_dist = nh.advertise<std_msgs::Float32MultiArray> ("dist_msg", 1);
	ros::Publisher pub_turtle = nh.advertise<geometry_msgs::Twist> (mv_turtle + "/cmd_vel", 1);
	
	ros::Subscriber sub_dist = nh.subscribe("dist_msg", 1, distCallback);
	ros::Subscriber sub_turtle = nh.subscribe(mv_turtle +"/pose", 1, turtleCallback);
	
	ros::spin();
	return 0;
}
