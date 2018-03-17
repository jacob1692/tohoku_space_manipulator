/* copyright (C) 2017 <tohoku university/jacob hernandez> */
/* license BSD */

#ifndef GAZEBO_PID_JOINTS_HH
#define GAZEBO_PID_JOINTS_HH

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <map>

#include <gazebo/common/common.hh>
#include <gazebo/physics/physics.hh>
#include <sdf/sdf.hh>

#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <ros/advertise_options.h>
#include <ros/callback_queue.h>
#include <ros/ros.h>


#include <gazebo/math/gzmath.hh>

#include "spacedyn_integration/dataext.h"


namespace gazebo {

  class GazeboJointsPID : public ModelPlugin {

    public: 
      GazeboJointsPID();
      ~GazeboJointsPID();
      void Load(physics::ModelPtr, sdf::ElementPtr);
      void OnUpdate(); 
     
    private:
      void Finalize();
      physics::ModelPtr parent_;
           
      //! physics::JointController * D1_; //! Compliant Wrist
      //! Ignore fixed joint of the camera
      
      physics::JointPtr j1_;
      physics::JointPtr j2_;
      physics::JointPtr j3_;
      physics::JointPtr j4_;
      physics::JointPtr j5_;
      physics::JointPtr j6_;
      //! physics::JointPtr d1_; //! Compliant Wrist
      //! Ignore fixed joint of the camera
      
     //! double cmd1_ ,cmd2_, cmd3_, cmd4_ , cmd5_, cmd6_; THE COMMAND IN NAVIGATION MODE IS ZERO
          
      event::ConnectionPtr update_connection_;

      boost::shared_ptr<ros::NodeHandle> rosnode_; //! nodehandle from gazebo
      ros::Subscriber joy_sub_;
      boost::mutex lock;

      std::string robot_namespace_;
      std::string command_topic_;
    
      double scale_;
      
      double errorlimit_;
      
      //Custom Callback Subscriber Queue
      common::Time last_time_;
      bool alive_;
      ros::CallbackQueue queue_;
      boost::thread callback_queue_thread_;
      void QueueThread();
      
      //joystick message Callback

      void JoyCallback (const sensor_msgs::Joy::ConstPtr& joy);
      int bax_change_ctrl1_;
      
      //! both flags are redundant acknowledgment of change of control mode
      bool flag_CH_CTRL_;
      
      int p_b_ctrl1_;
      
      gazebo::math::Vector4 PIDj1_, PIDj2_, PIDj3_, PIDj4_, PIDj5_, PIDj6_;      
  };
}

#endif /* end of include guard: GAZEBO_PID_JOINTS_HH */
