//#line 2 "/opt/ros/indigo/share/dynamic_reconfigure/cmake/../templates/ConfigType.h.template"
// *********************************************************
// 
// File autogenerated for the geobot_navigation package 
// by the dynamic_reconfigure package.
// Please do not edit.
// 
// ********************************************************/

#ifndef __geobot_navigation__GAINSCONFIG_H__
#define __geobot_navigation__GAINSCONFIG_H__

#include <dynamic_reconfigure/config_tools.h>
#include <limits>
#include <ros/node_handle.h>
#include <dynamic_reconfigure/ConfigDescription.h>
#include <dynamic_reconfigure/ParamDescription.h>
#include <dynamic_reconfigure/Group.h>
#include <dynamic_reconfigure/config_init_mutex.h>
#include <boost/any.hpp>

namespace geobot_navigation
{
  class GainsConfigStatics;
  
  class GainsConfig
  {
  public:
    class AbstractParamDescription : public dynamic_reconfigure::ParamDescription
    {
    public:
      AbstractParamDescription(std::string n, std::string t, uint32_t l, 
          std::string d, std::string e)
      {
        name = n;
        type = t;
        level = l;
        description = d;
        edit_method = e;
      }
      
      virtual void clamp(GainsConfig &config, const GainsConfig &max, const GainsConfig &min) const = 0;
      virtual void calcLevel(uint32_t &level, const GainsConfig &config1, const GainsConfig &config2) const = 0;
      virtual void fromServer(const ros::NodeHandle &nh, GainsConfig &config) const = 0;
      virtual void toServer(const ros::NodeHandle &nh, const GainsConfig &config) const = 0;
      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, GainsConfig &config) const = 0;
      virtual void toMessage(dynamic_reconfigure::Config &msg, const GainsConfig &config) const = 0;
      virtual void getValue(const GainsConfig &config, boost::any &val) const = 0;
    };

    typedef boost::shared_ptr<AbstractParamDescription> AbstractParamDescriptionPtr;
    typedef boost::shared_ptr<const AbstractParamDescription> AbstractParamDescriptionConstPtr;
    
    template <class T>
    class ParamDescription : public AbstractParamDescription
    {
    public:
      ParamDescription(std::string name, std::string type, uint32_t level, 
          std::string description, std::string edit_method, T GainsConfig::* f) :
        AbstractParamDescription(name, type, level, description, edit_method),
        field(f)
      {}

      T (GainsConfig::* field);

      virtual void clamp(GainsConfig &config, const GainsConfig &max, const GainsConfig &min) const
      {
        if (config.*field > max.*field)
          config.*field = max.*field;
        
        if (config.*field < min.*field)
          config.*field = min.*field;
      }

      virtual void calcLevel(uint32_t &comb_level, const GainsConfig &config1, const GainsConfig &config2) const
      {
        if (config1.*field != config2.*field)
          comb_level |= level;
      }

      virtual void fromServer(const ros::NodeHandle &nh, GainsConfig &config) const
      {
        nh.getParam(name, config.*field);
      }

      virtual void toServer(const ros::NodeHandle &nh, const GainsConfig &config) const
      {
        nh.setParam(name, config.*field);
      }

      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, GainsConfig &config) const
      {
        return dynamic_reconfigure::ConfigTools::getParameter(msg, name, config.*field);
      }

      virtual void toMessage(dynamic_reconfigure::Config &msg, const GainsConfig &config) const
      {
        dynamic_reconfigure::ConfigTools::appendParameter(msg, name, config.*field);
      }

      virtual void getValue(const GainsConfig &config, boost::any &val) const
      {
        val = config.*field;
      }
    };

    class AbstractGroupDescription : public dynamic_reconfigure::Group
    {
      public:
      AbstractGroupDescription(std::string n, std::string t, int p, int i, bool s)
      {
        name = n;
        type = t;
        parent = p;
        state = s;
        id = i;
      }

      std::vector<AbstractParamDescriptionConstPtr> abstract_parameters;
      bool state;

      virtual void toMessage(dynamic_reconfigure::Config &msg, const boost::any &config) const = 0;
      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, boost::any &config) const =0;
      virtual void updateParams(boost::any &cfg, GainsConfig &top) const= 0;
      virtual void setInitialState(boost::any &cfg) const = 0;


      void convertParams()
      {
        for(std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = abstract_parameters.begin(); i != abstract_parameters.end(); ++i)
        {
          parameters.push_back(dynamic_reconfigure::ParamDescription(**i));
        }
      }
    };

    typedef boost::shared_ptr<AbstractGroupDescription> AbstractGroupDescriptionPtr;
    typedef boost::shared_ptr<const AbstractGroupDescription> AbstractGroupDescriptionConstPtr;

    template<class T, class PT>
    class GroupDescription : public AbstractGroupDescription
    {
    public:
      GroupDescription(std::string name, std::string type, int parent, int id, bool s, T PT::* f) : AbstractGroupDescription(name, type, parent, id, s), field(f)
      {
      }

      GroupDescription(const GroupDescription<T, PT>& g): AbstractGroupDescription(g.name, g.type, g.parent, g.id, g.state), field(g.field), groups(g.groups)
      {
        parameters = g.parameters;
        abstract_parameters = g.abstract_parameters;
      }

      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, boost::any &cfg) const
      {
        PT* config = boost::any_cast<PT*>(cfg);
        if(!dynamic_reconfigure::ConfigTools::getGroupState(msg, name, (*config).*field))
          return false;

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          boost::any n = &((*config).*field);
          if(!(*i)->fromMessage(msg, n))
            return false;
        }

        return true;
      }

      virtual void setInitialState(boost::any &cfg) const
      {
        PT* config = boost::any_cast<PT*>(cfg);
        T* group = &((*config).*field);
        group->state = state;

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          boost::any n = boost::any(&((*config).*field));
          (*i)->setInitialState(n);
        }

      }

      virtual void updateParams(boost::any &cfg, GainsConfig &top) const
      {
        PT* config = boost::any_cast<PT*>(cfg);

        T* f = &((*config).*field);
        f->setParams(top, abstract_parameters);

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          boost::any n = &((*config).*field);
          (*i)->updateParams(n, top);
        }
      }

      virtual void toMessage(dynamic_reconfigure::Config &msg, const boost::any &cfg) const
      {
        const PT config = boost::any_cast<PT>(cfg);
        dynamic_reconfigure::ConfigTools::appendGroup<T>(msg, name, id, parent, config.*field);

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          (*i)->toMessage(msg, config.*field);
        }
      }

      T (PT::* field);
      std::vector<GainsConfig::AbstractGroupDescriptionConstPtr> groups;
    };
    
class DEFAULT
{
  public:
    DEFAULT()
    {
      state = true;
      name = "Default";
    }

    void setParams(GainsConfig &config, const std::vector<AbstractParamDescriptionConstPtr> params)
    {
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator _i = params.begin(); _i != params.end(); ++_i)
      {
        boost::any val;
        (*_i)->getValue(config, val);

        if("maximum_linear_velocity"==(*_i)->name){maximum_linear_velocity = boost::any_cast<double>(val);}
        if("maximum_angular_velocity"==(*_i)->name){maximum_angular_velocity = boost::any_cast<double>(val);}
        if("error_tolerance2goal"==(*_i)->name){error_tolerance2goal = boost::any_cast<double>(val);}
        if("no_of_segments_ahead"==(*_i)->name){no_of_segments_ahead = boost::any_cast<int>(val);}
        if("error_gain"==(*_i)->name){error_gain = boost::any_cast<double>(val);}
        if("cte_gain"==(*_i)->name){cte_gain = boost::any_cast<double>(val);}
        if("heading_gain"==(*_i)->name){heading_gain = boost::any_cast<double>(val);}
        if("velocity_constraint"==(*_i)->name){velocity_constraint = boost::any_cast<double>(val);}
        if("obstacle_edge2robotcenter"==(*_i)->name){obstacle_edge2robotcenter = boost::any_cast<double>(val);}
        if("trajectory_projection"==(*_i)->name){trajectory_projection = boost::any_cast<double>(val);}
        if("cross_track_error_deadband"==(*_i)->name){cross_track_error_deadband = boost::any_cast<double>(val);}
        if("side_distance_avoidance_threshold"==(*_i)->name){side_distance_avoidance_threshold = boost::any_cast<double>(val);}
        if("front_distance_avoidance_threshold"==(*_i)->name){front_distance_avoidance_threshold = boost::any_cast<double>(val);}
        if("side_avoidance_blindband"==(*_i)->name){side_avoidance_blindband = boost::any_cast<double>(val);}
        if("minimum_velocity_constraint"==(*_i)->name){minimum_velocity_constraint = boost::any_cast<double>(val);}
      }
    }

    double maximum_linear_velocity;
double maximum_angular_velocity;
double error_tolerance2goal;
int no_of_segments_ahead;
double error_gain;
double cte_gain;
double heading_gain;
double velocity_constraint;
double obstacle_edge2robotcenter;
double trajectory_projection;
double cross_track_error_deadband;
double side_distance_avoidance_threshold;
double front_distance_avoidance_threshold;
double side_avoidance_blindband;
double minimum_velocity_constraint;

    bool state;
    std::string name;

    
}groups;



//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double maximum_linear_velocity;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double maximum_angular_velocity;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double error_tolerance2goal;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      int no_of_segments_ahead;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double error_gain;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double cte_gain;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double heading_gain;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double velocity_constraint;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double obstacle_edge2robotcenter;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double trajectory_projection;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double cross_track_error_deadband;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double side_distance_avoidance_threshold;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double front_distance_avoidance_threshold;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double side_avoidance_blindband;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double minimum_velocity_constraint;
//#line 218 "/opt/ros/indigo/share/dynamic_reconfigure/cmake/../templates/ConfigType.h.template"

    bool __fromMessage__(dynamic_reconfigure::Config &msg)
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();

      int count = 0;
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        if ((*i)->fromMessage(msg, *this))
          count++;

      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); i ++)
      {
        if ((*i)->id == 0)
        {
          boost::any n = boost::any(this);
          (*i)->updateParams(n, *this);
          (*i)->fromMessage(msg, n);
        }
      }

      if (count != dynamic_reconfigure::ConfigTools::size(msg))
      {
        ROS_ERROR("GainsConfig::__fromMessage__ called with an unexpected parameter.");
        ROS_ERROR("Booleans:");
        for (unsigned int i = 0; i < msg.bools.size(); i++)
          ROS_ERROR("  %s", msg.bools[i].name.c_str());
        ROS_ERROR("Integers:");
        for (unsigned int i = 0; i < msg.ints.size(); i++)
          ROS_ERROR("  %s", msg.ints[i].name.c_str());
        ROS_ERROR("Doubles:");
        for (unsigned int i = 0; i < msg.doubles.size(); i++)
          ROS_ERROR("  %s", msg.doubles[i].name.c_str());
        ROS_ERROR("Strings:");
        for (unsigned int i = 0; i < msg.strs.size(); i++)
          ROS_ERROR("  %s", msg.strs[i].name.c_str());
        // @todo Check that there are no duplicates. Make this error more
        // explicit.
        return false;
      }
      return true;
    }

    // This version of __toMessage__ is used during initialization of
    // statics when __getParamDescriptions__ can't be called yet.
    void __toMessage__(dynamic_reconfigure::Config &msg, const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__, const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__) const
    {
      dynamic_reconfigure::ConfigTools::clear(msg);
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->toMessage(msg, *this);

      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); ++i)
      {
        if((*i)->id == 0)
        {
          (*i)->toMessage(msg, *this);
        }
      }
    }
    
    void __toMessage__(dynamic_reconfigure::Config &msg) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();
      __toMessage__(msg, __param_descriptions__, __group_descriptions__);
    }
    
    void __toServer__(const ros::NodeHandle &nh) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->toServer(nh, *this);
    }

    void __fromServer__(const ros::NodeHandle &nh)
    {
      static bool setup=false;

      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->fromServer(nh, *this);

      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();
      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); i++){
        if (!setup && (*i)->id == 0) {
          setup = true;
          boost::any n = boost::any(this);
          (*i)->setInitialState(n);
        }
      }
    }

    void __clamp__()
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const GainsConfig &__max__ = __getMax__();
      const GainsConfig &__min__ = __getMin__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->clamp(*this, __max__, __min__);
    }

    uint32_t __level__(const GainsConfig &config) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      uint32_t level = 0;
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->calcLevel(level, config, *this);
      return level;
    }
    
    static const dynamic_reconfigure::ConfigDescription &__getDescriptionMessage__();
    static const GainsConfig &__getDefault__();
    static const GainsConfig &__getMax__();
    static const GainsConfig &__getMin__();
    static const std::vector<AbstractParamDescriptionConstPtr> &__getParamDescriptions__();
    static const std::vector<AbstractGroupDescriptionConstPtr> &__getGroupDescriptions__();
    
  private:
    static const GainsConfigStatics *__get_statics__();
  };
  
  template <> // Max and min are ignored for strings.
  inline void GainsConfig::ParamDescription<std::string>::clamp(GainsConfig &config, const GainsConfig &max, const GainsConfig &min) const
  {
    return;
  }

  class GainsConfigStatics
  {
    friend class GainsConfig;
    
    GainsConfigStatics()
    {
GainsConfig::GroupDescription<GainsConfig::DEFAULT, GainsConfig> Default("Default", "", 0, 0, true, &GainsConfig::groups);
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.maximum_linear_velocity = 0.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.maximum_linear_velocity = 1.1;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.maximum_linear_velocity = 0.5;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("maximum_linear_velocity", "double", 0, "Max speed Geobot can go", "", &GainsConfig::maximum_linear_velocity)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("maximum_linear_velocity", "double", 0, "Max speed Geobot can go", "", &GainsConfig::maximum_linear_velocity)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.maximum_angular_velocity = 0.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.maximum_angular_velocity = 1.1;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.maximum_angular_velocity = 0.5;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("maximum_angular_velocity", "double", 0, "Max spin speed Geobot will do", "", &GainsConfig::maximum_angular_velocity)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("maximum_angular_velocity", "double", 0, "Max spin speed Geobot will do", "", &GainsConfig::maximum_angular_velocity)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.error_tolerance2goal = 0.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.error_tolerance2goal = 1.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.error_tolerance2goal = 0.4;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("error_tolerance2goal", "double", 0.1, "Fraction of current segment where next segment is considered", "", &GainsConfig::error_tolerance2goal)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("error_tolerance2goal", "double", 0.1, "Fraction of current segment where next segment is considered", "", &GainsConfig::error_tolerance2goal)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.no_of_segments_ahead = 1;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.no_of_segments_ahead = 10;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.no_of_segments_ahead = 2;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<int>("no_of_segments_ahead", "int", 0, "Number of future segments considered for speed reduction", "", &GainsConfig::no_of_segments_ahead)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<int>("no_of_segments_ahead", "int", 0, "Number of future segments considered for speed reduction", "", &GainsConfig::no_of_segments_ahead)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.error_gain = 0.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.error_gain = 2.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.error_gain = 1.1;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("error_gain", "double", 0, "K_k Path offset gain term", "", &GainsConfig::error_gain)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("error_gain", "double", 0, "K_k Path offset gain term", "", &GainsConfig::error_gain)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.cte_gain = 0.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.cte_gain = 2.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.cte_gain = 0.2;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("cte_gain", "double", 0, "cte Cross track error term", "", &GainsConfig::cte_gain)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("cte_gain", "double", 0, "cte Cross track error term", "", &GainsConfig::cte_gain)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.heading_gain = 0.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.heading_gain = 2.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.heading_gain = 0.5;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("heading_gain", "double", 0, "K_e Geobot heading error gain term", "", &GainsConfig::heading_gain)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("heading_gain", "double", 0, "K_e Geobot heading error gain term", "", &GainsConfig::heading_gain)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.velocity_constraint = 0.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.velocity_constraint = 1.1;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.velocity_constraint = 1.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("velocity_constraint", "double", 0, "Max speed Geobot can go", "", &GainsConfig::velocity_constraint)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("velocity_constraint", "double", 0, "Max speed Geobot can go", "", &GainsConfig::velocity_constraint)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.obstacle_edge2robotcenter = 0.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.obstacle_edge2robotcenter = 1.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.obstacle_edge2robotcenter = 0.7;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("obstacle_edge2robotcenter", "double", 0, "Half of gap_width threshold", "", &GainsConfig::obstacle_edge2robotcenter)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("obstacle_edge2robotcenter", "double", 0, "Half of gap_width threshold", "", &GainsConfig::obstacle_edge2robotcenter)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.trajectory_projection = 0.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.trajectory_projection = 1.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.trajectory_projection = 1.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("trajectory_projection", "double", 0, "trajectory_projection", "", &GainsConfig::trajectory_projection)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("trajectory_projection", "double", 0, "trajectory_projection", "", &GainsConfig::trajectory_projection)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.cross_track_error_deadband = 0.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.cross_track_error_deadband = 1.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.cross_track_error_deadband = 0.02;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("cross_track_error_deadband", "double", 0, "cross track error deadband", "", &GainsConfig::cross_track_error_deadband)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("cross_track_error_deadband", "double", 0, "cross track error deadband", "", &GainsConfig::cross_track_error_deadband)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.side_distance_avoidance_threshold = 0.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.side_distance_avoidance_threshold = 1.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.side_distance_avoidance_threshold = 0.6;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("side_distance_avoidance_threshold", "double", 0, "side distance avoidance threshold", "", &GainsConfig::side_distance_avoidance_threshold)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("side_distance_avoidance_threshold", "double", 0, "side distance avoidance threshold", "", &GainsConfig::side_distance_avoidance_threshold)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.front_distance_avoidance_threshold = 0.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.front_distance_avoidance_threshold = 2.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.front_distance_avoidance_threshold = 1.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("front_distance_avoidance_threshold", "double", 0, "front distance avoidance threshold", "", &GainsConfig::front_distance_avoidance_threshold)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("front_distance_avoidance_threshold", "double", 0, "front distance avoidance threshold", "", &GainsConfig::front_distance_avoidance_threshold)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.side_avoidance_blindband = 0.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.side_avoidance_blindband = 1.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.side_avoidance_blindband = 0.4;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("side_avoidance_blindband", "double", 0, "side avoidance blindband", "", &GainsConfig::side_avoidance_blindband)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("side_avoidance_blindband", "double", 0, "side avoidance blindband", "", &GainsConfig::side_avoidance_blindband)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.minimum_velocity_constraint = 0.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.minimum_velocity_constraint = 1.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.minimum_velocity_constraint = 0.1;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("minimum_velocity_constraint", "double", 0, "minimum velocity constraint", "", &GainsConfig::minimum_velocity_constraint)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(GainsConfig::AbstractParamDescriptionConstPtr(new GainsConfig::ParamDescription<double>("minimum_velocity_constraint", "double", 0, "minimum velocity constraint", "", &GainsConfig::minimum_velocity_constraint)));
//#line 235 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.convertParams();
//#line 235 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __group_descriptions__.push_back(GainsConfig::AbstractGroupDescriptionConstPtr(new GainsConfig::GroupDescription<GainsConfig::DEFAULT, GainsConfig>(Default)));
//#line 353 "/opt/ros/indigo/share/dynamic_reconfigure/cmake/../templates/ConfigType.h.template"

      for (std::vector<GainsConfig::AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); ++i)
      {
        __description_message__.groups.push_back(**i);
      }
      __max__.__toMessage__(__description_message__.max, __param_descriptions__, __group_descriptions__); 
      __min__.__toMessage__(__description_message__.min, __param_descriptions__, __group_descriptions__); 
      __default__.__toMessage__(__description_message__.dflt, __param_descriptions__, __group_descriptions__); 
    }
    std::vector<GainsConfig::AbstractParamDescriptionConstPtr> __param_descriptions__;
    std::vector<GainsConfig::AbstractGroupDescriptionConstPtr> __group_descriptions__;
    GainsConfig __max__;
    GainsConfig __min__;
    GainsConfig __default__;
    dynamic_reconfigure::ConfigDescription __description_message__;

    static const GainsConfigStatics *get_instance()
    {
      // Split this off in a separate function because I know that
      // instance will get initialized the first time get_instance is
      // called, and I am guaranteeing that get_instance gets called at
      // most once.
      static GainsConfigStatics instance;
      return &instance;
    }
  };

  inline const dynamic_reconfigure::ConfigDescription &GainsConfig::__getDescriptionMessage__() 
  {
    return __get_statics__()->__description_message__;
  }

  inline const GainsConfig &GainsConfig::__getDefault__()
  {
    return __get_statics__()->__default__;
  }
  
  inline const GainsConfig &GainsConfig::__getMax__()
  {
    return __get_statics__()->__max__;
  }
  
  inline const GainsConfig &GainsConfig::__getMin__()
  {
    return __get_statics__()->__min__;
  }
  
  inline const std::vector<GainsConfig::AbstractParamDescriptionConstPtr> &GainsConfig::__getParamDescriptions__()
  {
    return __get_statics__()->__param_descriptions__;
  }

  inline const std::vector<GainsConfig::AbstractGroupDescriptionConstPtr> &GainsConfig::__getGroupDescriptions__()
  {
    return __get_statics__()->__group_descriptions__;
  }

  inline const GainsConfigStatics *GainsConfig::__get_statics__()
  {
    const static GainsConfigStatics *statics;
  
    if (statics) // Common case
      return statics;

    boost::mutex::scoped_lock lock(dynamic_reconfigure::__init_mutex__);

    if (statics) // In case we lost a race.
      return statics;

    statics = GainsConfigStatics::get_instance();
    
    return statics;
  }


}

#endif // __GAINSRECONFIGURATOR_H__