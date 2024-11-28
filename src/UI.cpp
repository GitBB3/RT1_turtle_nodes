#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Spawn.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

ros::Publisher pub;

vector<float> speed_input(3);

void turtleCallback(const turtlesim::Pose::ConstPtr& msg)
	{
	
	ROS_INFO("Moving turtle pose@[%f, %f, %f]",
	msg->x, msg->y, msg->theta);
	geometry_msgs::Twist my_vel;	
	
	my_vel.linear.x = speed_input[0];
	my_vel.linear.y = speed_input[1];
	my_vel.angular.z = speed_input[2];
	
	cout << "Speed input:";
	cout << speed_input[0] <<";";
	cout << speed_input[1]<<";";
	cout << speed_input[2] << endl;
	
	pub.publish(my_vel);
	
	}
	
	
int main (int argc, char **argv)
{

	ros::init(argc, argv, "turtlebot_subscriber");
	ros::NodeHandle nh;
	
	
	ros::ServiceClient client1 = nh.serviceClient<turtlesim::Spawn>("/spawn");
	turtlesim::Spawn srv1;
	srv1.request.x = 2.0;
	srv1.request.y = 1.0;
	srv1.request.theta = 0.0;
	srv1.request.name="turtle2";
	client1.waitForExistence();
	client1.call(srv1);
	
	
	while (ros::ok()){
	
		string turtle_nb;
		cout << "Which one do you want to move? turtle1 or turtle2:" << endl;
		cin >> turtle_nb;
		cout << "Choose the speed {Vx, Vy, Wz}:" << endl;
		cout << "Vx:" << endl;
		cin >> speed_input[0];
		cout << "Vy:" << endl;
		cin >> speed_input[1];
		cout << "Wz:" << endl;
		cin >> speed_input[2];
		
		pub = nh.advertise<geometry_msgs::Twist>(turtle_nb + "/cmd_vel",1);
		ros::Subscriber sub = nh.subscribe(turtle_nb + "/pose",1,turtleCallback);
		
		//geometry_msgs::Twist my_vel;
		//my_vel.linear.x = speed_input[0];
		//my_vel.linear.y = speed_input[1];
		//my_vel.angular.z = speed_input[2];
		
		//pub.publish(my_vel);
		
		sleep(1);
		ros::spinOnce();
	}
	return 0;

}
