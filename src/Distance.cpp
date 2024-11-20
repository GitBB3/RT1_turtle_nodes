#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Float32.h"
#include <string>
double THR=0.05;
float dx,dy;
double x_mv,y_mv;


ros::Publisher pub_turtle;
ros::Publisher pub_dist;


void turtleCallback(const std_msgs::Float32MultiArray::ConstPtr& msg_dist){
	ROS_INFO("Turtle subscriber@[%f, %f]",
	msg_dist->data[0],msg_dist->data[1]);
	
	if (msg_dist->data[0] > THR || msg_dist->data[1] > THR){
	
	}
	
	//if (dx <= THR || dy <= THR || x_mv > 10.0 || x_mv < 0.0 || y_mv > 10.0 || y_mv < 0.0)
	//{
	//my_vel_mv.linear.x = 0.0;
	//my_vel_mv.linear.y = 0.0;
	//my_vel_mv.angular.z = 0.0;
	//}

}










int main(int argc, char **argv){
	ros::init(argc, argv, "turtlebot_subscriber");  
	ros::NodeHandle nh;
	
	
	while (ros::ok()){
		
		ROS_INFO("Turtle subscriber@[%f, %f, %f]",
		msg1->x, msg1->y, msg1->theta);
		geometry_msgs::Twist my_vel1;
		
		ROS_INFO("Turtle subscriber@[%f, %f, %f]",
		msg2->x, msg2->y, msg2->theta);
		geometry_msgs::Twist my_vel2;
		
		string mv_turtle;
	
		if (msg1->x ~= 0 || msg1->y ~= 0 || msg1->theta ~= 0){
			mv_turtle = "turtle1";
		}
		else if (msg2->x ~= 0 || msg2->y ~= 0 || msg2->theta ~= 0){
			mv_turtle = "turtle2";
		}
		
		std_msgs::Float32MultiArray msg_dist;
		msg_dist.data = {abs(msg1->x - msg2->x), abs(msg1->y - msg2->y)};
		
		
		ros::Subscriber sub_turtle = nh.subscribe(mv_turtle +"/pose", 1,turtleCallback);
		pub_turtle = nh.advertise<geometry_msgs::Twist> (mv_turtle + "/cmd_vel", 1);
		
		ros::Subscriber sub_dist = nh.subscribe(msg_dist, 1,turtleCallback);
		pub_dist = nh.advertise<std_msgs::Float32> (msg_dist, 1);
		
		
		pub_turtle.publish(msg);
		pub_dist.publish(my_vel);
		
		
		// publish distance
		
		
		
		
		
		
		ros::spin();	
	}
	
	
	return 0;
}
