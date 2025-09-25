#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

#include "../../../../../../opt/ros/noetic/include/geometry_msgs/Twist.h"
#include "../../../../../../opt/ros/noetic/include/ros/init.h"
#include "../../../../../../opt/ros/noetic/include/ros/node_handle.h"
#include "../../../../../../opt/ros/noetic/include/ros/publisher.h"
#include "../../../../../../opt/ros/noetic/include/ros/rate.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "vel_node");

    ros::NodeHandle n ;

    ros::Publisher vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    geometry_msgs::Twist vel_msg;

    vel_msg.linear.x = 0;
    vel_msg.linear.y = 0;
    vel_msg.linear.z = 0;

    vel_msg.angular.x = 0;
    vel_msg.angular.y = 0;
    vel_msg.angular.z = 0.6;

    ros::Rate r(30);
    while (ros::ok()) {
        vel_pub.publish(vel_msg);
        r.sleep();
    }


    return 0 ;

}
