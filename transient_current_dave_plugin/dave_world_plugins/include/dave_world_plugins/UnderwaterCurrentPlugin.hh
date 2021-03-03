// Copyright (c) 2016 The dave Simulator Authors.
// All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/// \file UnderwaterCurrentPlugin.hh
/// \brief Plugin that for the underwater world

#ifndef __UNDERWATER_CURRENT_PLUGIN_HH__
#define __UNDERWATER_CURRENT_PLUGIN_HH__

#include <StratifiedCurrentVelocity.pb.h>

#include <map>
#include <cmath>
#include <string>
#include <vector>

#include <gazebo/gazebo.hh>
#include <gazebo/transport/TransportTypes.hh>
#include <dave_world_plugins/GaussMarkovProcess.hh>
#include <sdf/sdf.hh>

namespace gazebo
{
  /// \brief Class for the underwater current plugin

  typedef const boost::shared_ptr<const gazebo::msgs::Any> AnyPtr;

  class UnderwaterCurrentPlugin : public WorldPlugin
  {
    /// \brief Class constructor
    public: UnderwaterCurrentPlugin();

    /// \brief Class destructor
    public: virtual ~UnderwaterCurrentPlugin();

    // Documentation inherited.
    public: virtual void Load(physics::WorldPtr _world,
        sdf::ElementPtr _sdf);

    // Documentation inherited.
    public: virtual void Init();

    /// \brief Update the simulation state.
    /// \param[in] _info Information used in the update event.
    public: void Update(const common::UpdateInfo &_info);

    /// \brief Publish current velocity and the pose of its frame
    protected: void PublishCurrentVelocity();

    /// \brief Publish stratified oceqan currnet velocity
    protected: void PublishStratifiedCurrentVelocity();

    /// \brief Subscribe vehicle depth and the pose of its frame
    protected: void SubscribeVehicleDepth(AnyPtr &_msg);

    /// \brief Subscribe vehicle depth and the pose of its frame
    protected: void  ApplyDatabase();

    /// \brief Update event
    protected: event::ConnectionPtr updateConnection;

    /// \brief Pointer to world
    protected: physics::WorldPtr world;

    /// \brief Pointer to sdf
    protected: sdf::ElementPtr sdf;

    /// \brief True if the sea surface is present
    protected: bool hasSurface;

    /// \brief Pointer to a node for communication
    protected: transport::NodePtr node;

    /// \brief Map of publishers
    protected: std::map<std::string, transport::PublisherPtr>
      publishers;

    /// \brief Vehicle Depth Subscriber
    protected: transport::SubscriberPtr subscriber;

    /// \brief Current velocity topic
    protected: std::string currentVelocityTopic;

    /// \brief Stratified Ocean current topic
    protected: std::string stratifiedCurrentVelocityTopic;

    /// \brief Vehicle depth topic
    protected: std::string vehicleDepthTopic;

    /// \brief Database file path for csv file
    protected: std::string databaseFilePath;

    /// \brief Vector for read database
    protected: std::vector<ignition::math::Vector3d> database;

    /// \brief Namespace for topics and services
    protected: std::string ns;

    /// \brief Gauss-Markov process instance for the current velocity
    protected: GaussMarkovProcess currentVelModel;

    /// \brief Gauss-Markov process instance for horizontal angle model
    protected: GaussMarkovProcess currentHorzAngleModel;

    /// \brief Gauss-Markov process instance for vertical angle model
    protected: GaussMarkovProcess currentVertAngleModel;

    /// \brief Last update time stamp
    protected: common::Time lastUpdate;

    /// \brief Current linear velocity vector
    protected: ignition::math::Vector3d currentVelocity;

    /// \brief Vehicle depth
    protected: double vehicleDepth;

    /// \brief File path for stratified current database
    protected: std::string db_path;
  };
}

#endif  // __UNDERWATER_CURRENT_PLUGIN_HH__
