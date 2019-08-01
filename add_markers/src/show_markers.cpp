#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <math.h>

double pickUpX = -3.0;
double pickUpY = 2.0;
double dropOffX = -3.0;
double dropOffY = -3.0;

// void amclCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg) {
    
//   double robotX = msg->pose.pose.position.x;
//   double robotY = msg->pose.pose.position.y;
//   // ROS_INFO("Received nav_msgs");

//   double distanceToPickup = sqrt(pow(robotX - pickUpX, 2) + pow(robotY - pickUpY, 2));
//   double distanceToDropoff = sqrt(pow(robotX - dropOffX, 2) + pow(robotY - dropOffY, 2));  

//   if (distanceToPickup < 0.5) {
//     itemPickedUp = true;
//     ROS_INFO("Reach the pickup zone!");
//   }
  
//   if (distanceToDropoff < 0.3) {
//     itemDroppedOff = true;
//     ROS_INFO("Reach the dropoff zone!");
//   }
// }


int main( int argc, char** argv )
{
  ros::init(argc, argv, "show_markers");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  // ros::Subscriber amcl_sub = n.subscribe("amcl_pose", 10, amclCallback);

  visualization_msgs::Marker marker;

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "cube";
  marker.id = 0;

  // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  marker.type = shape;

  // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
  marker.pose.position.x = pickUpX;
  marker.pose.position.y = pickUpY;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;

  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = 0.2;
  marker.scale.y = 0.2;
  marker.scale.z = 0.2;

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;

  marker.lifetime = ros::Duration();
  if (ros::ok())
  {
    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    
    
    marker.action = visualization_msgs::Marker::ADD;
    marker_pub.publish(marker);
    ROS_INFO("Show marker at the pickup location");
    ros::Duration(5.0).sleep();
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);
    ROS_INFO("Hide marker at the pickup location");

    ros::Duration(5.0).sleep();
    
    marker.pose.position.x = dropOffX;
    marker.pose.position.y = dropOffY;
    marker.action = visualization_msgs::Marker::ADD;
    marker_pub.publish(marker);
    ROS_INFO("Show marker at the dropoff location");
    ros::Duration(10.0).sleep();

    ros::spinOnce();
  }
}
