#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Float32.h"
#include <string>
#include <iostream>
using namespace std;

double THR=1;
float dx, dy, dist_cart=THR;
double x1_mem=0, y1_mem=0, x2_mem=5, y2_mem=5;

turtlesim::Pose pose_turtle1, pose_turtle2;
geometry_msgs::Twist vel_turtle1, vel_turtle2;

ros::Publisher pub_turtle1;
ros::Publisher pub_turtle2;
ros::Publisher pub_dist;

void turtle1Callback(const turtlesim::Pose::ConstPtr& msg)
{
	geometry_msgs::Twist my_vel1;
	pose_turtle1 = *msg;
	vel_turtle1 = my_vel1;
	
	dx = abs(pose_turtle2.x - pose_turtle1.x);
	dy = abs(pose_turtle2.y - pose_turtle1.y);
	dist_cart = sqrt(dx*dx + dy*dy);
	ROS_INFO("Distance@[%f]", dist_cart);
	
	if (dist_cart < THR || msg->x > 10.0 || msg->x <= 0.0 || msg->y > 10.0 || msg->y <= 0.0){
	my_vel1.linear.x = 0.0;
	my_vel1.linear.y = 0.0;
	pose_turtle1.x = x1_mem;
	pose_turtle1.y = y1_mem;
	ROS_WARN("Turtle1: Collision Risk!");
	pub_turtle1.publish(my_vel1);
	//sleep(1);
	}
	
	x1_mem = pose_turtle1.x;
	y1_mem = pose_turtle1.y;
	
	std_msgs::Float32 msg_dist;
	msg_dist.data = dist_cart;
	pub_dist.publish(msg_dist);
	
	
}

void turtle2Callback(const turtlesim::Pose::ConstPtr& msg)
{
	geometry_msgs::Twist my_vel2;
	pose_turtle2 = *msg;
	vel_turtle2 = my_vel2;
	
	dx = abs(pose_turtle2.x - pose_turtle1.x);
	dy = abs(pose_turtle2.y - pose_turtle1.y);
	dist_cart = sqrt(dx*dx + dy*dy);
	ROS_INFO("Distance@[%f]", dist_cart);
	
	if (dist_cart < THR || msg->x > 10.0 || msg->x <= 0.0 || msg->y > 10.0 || msg->y <= 0.0){
	my_vel2.linear.x = 0.0;
	my_vel2.linear.y = 0.0;
	pose_turtle2.x = x2_mem;
	pose_turtle2.y = y2_mem;
	ROS_WARN("Turtle2: Collision Risk!");
	pub_turtle2.publish(my_vel2);
	//sleep(1);
		}
	
	x2_mem = pose_turtle2.x;
	y2_mem = pose_turtle2.y;
	
	std_msgs::Float32 msg_dist;
	msg_dist.data = dist_cart;
	pub_dist.publish(msg_dist);
	
	
}



int main(int argc, char **argv){
	ros::init(argc, argv, "turtlebot_distance");  
	ros::NodeHandle nh;
	
	// pub/sub Pose tortue 1
	pub_turtle1 = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1);
	ros::Subscriber sub_turtle1 = nh.subscribe("turtle1/pose", 1, turtle1Callback);
	// pub/sub Pose tortue 2
	pub_turtle2 = nh.advertise<geometry_msgs::Twist>("turtle2/cmd_vel", 1);
	ros::Subscriber sub_turtle2 = nh.subscribe("turtle2/pose", 1, turtle2Callback);
	// pub distance
	pub_dist = nh.advertise<std_msgs::Float32>("dist_msg", 1);
	
	
	sleep(1);
	ros::spin();
	return 0;
}
