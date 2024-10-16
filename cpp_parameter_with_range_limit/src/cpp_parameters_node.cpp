#include "rcl_interfaces/msg/integer_range.hpp"
#include "rcl_interfaces/msg/parameter_descriptor.hpp"
#include "rcl_interfaces/msg/parameter_type.hpp"
#include <functional>
#include <rclcpp/parameter.hpp>

#include <rclcpp/rclcpp.hpp>

using namespace std::chrono_literals;

class MinimalParam : public rclcpp::Node
{
  public:
    MinimalParam()
      : Node("minimal_param_node")
    {
      auto param_desc = rcl_interfaces::msg::ParameterDescriptor{};
      param_desc.name = "Cool parameter";
      param_desc.description = "Gets printed every second";
      //param_desc.type = rcl_interfaces::msg::ParameterType::PARAMETER_INTEGER;
      param_desc.type = rclcpp::PARAMETER_INTEGER;

      auto range = rcl_interfaces::msg::IntegerRange();
      //range.step = 1;
      range.from_value = 0;
      range.to_value = 256;
      param_desc.integer_range.push_back(range);

      this->declare_parameter<int>("my_parameter", 47, param_desc);

      timer_ = this->create_wall_timer(
          1000ms, std::bind(&MinimalParam::timer_callback, this));
    }

    void timer_callback()
    {
      int my_param = this->get_parameter("my_parameter").as_int();

      RCLCPP_INFO(this->get_logger(), "Hey %i!", my_param);

      std::vector<rclcpp::Parameter> all_new_parameters{rclcpp::Parameter("my_parameter", 47)};
      this->set_parameters(all_new_parameters);
    }

  private:
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalParam>());
  rclcpp::shutdown();
  return 0;
}

