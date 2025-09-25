//
// Created by chonqin on 2025/9/24.
//
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>


ros::Publisher vel_pub ;
int n = 0;
void lidar_Callback(const sensor_msgs::LaserScan msg) {
    float fMidDist = msg.ranges[180];
    ROS_INFO("前方测距 ranges[180] = %f 米",fMidDist);

    if (n>0) {
        n--;
        return;
    }
    geometry_msgs::Twist vel_cmd;
    if (fMidDist < 1.5) {
        vel_cmd.angular.z = 0.3;
        n=50;
    }
    else {
        vel_cmd.linear.x = 0.1;
    }
    vel_pub.publish(vel_cmd);
}


int main(int argc, char **argv) {
    setlocale(LC_ALL, "");

    ros::init(argc, argv, "lidar_node");

    ros::NodeHandle n ;

    ros::Subscriber lidar_sub = n.subscribe("/scan", 10, &lidar_Callback);

                    vel_pub  = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    ros::spin ();

    return 0;
}
