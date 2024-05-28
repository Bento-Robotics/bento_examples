#include <memory>

#include "rclcpp/rclcpp.hpp"

class SampleNodeWithParameters : public rclcpp::Node
{
public:
	SampleNodeWithParameters() : Node("node_with_parameters") {
		RCLCPP_INFO(this->get_logger(), "started");
		this->declare_parameter("int_param", 0);
		this->declare_parameter("double_param", 0.f);
		this->declare_parameter("string_param", "henlo");
		this->declare_parameter("bool_param", false);

		// Create a parameter subscriber that can be used to monitor parameter changes
		param_subscriber_ = std::make_shared<rclcpp::ParameterEventHandler>(this);
		cb_handle_ = param_subscriber_->add_parameter_event_callback(std::bind(&SampleNodeWithParameters::on_parameter_event, this, std::placeholders::_1));
	}

	// Set a callback for parameter changes
	void on_parameter_event(const rcl_interfaces::msg::ParameterEvent &event) {
		//if ( event.node.compare( this->get_fully_qualified_name() ) == 0 ) { // limit to only this node
		auto params = param_subscriber_->get_parameters_from_event(event);
		for (auto &p : params) {
			RCLCPP_INFO(
				this->get_logger(), "cb: Received an update to parameter \"%s\" of type %s: \"%s\" for %s",
				p.get_name().c_str(),
				p.get_type_name().c_str(),
				p.value_to_string().c_str(),
				event.node.c_str());
		}
	    //}
	}


private:
	std::shared_ptr<rclcpp::ParameterEventHandler> param_subscriber_;
	std::shared_ptr<rclcpp::ParameterEventCallbackHandle> cb_handle_;
};

int main(int argc, char ** argv)
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<SampleNodeWithParameters>());
	rclcpp::shutdown();

	return 0;
}
