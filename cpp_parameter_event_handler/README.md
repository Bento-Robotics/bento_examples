# parameter event handler (cpp)
> This program checks for changes in parameters on all nodes and prints them all out
> It can easily be adapted to check for parameter changes on the current node (example in comments)
> *adapted from [ros2 wiki](https://docs.ros.org/en/humble/Tutorials/Intermediate/Monitoring-For-Parameter-Changes-CPP.html)*

> [!NOTE]
> changes since Humble, more options https://docs.ros.org/en/humble/Releases/Release-Iron-Irwini.html#pre-and-post-set-parameter-callback-support

**Run in container:**
```bash
podman run -it --privileged --network=host -v ~/Code/bento_examples/:/bento_ws/src/ --name bento_examples --rm rosbox:robot bash

# in container
rm -rf install/ build/ log/
colcon build --packages-select cpp_parameter_event_handler
source install/setup.bash
ros2 run cpp_parameter_event_handler parameter_event_handler & # run in background
ros2 param set /node_with_parameters int_param 42
fg # move back to foreground, kill with ctrl+c
```
