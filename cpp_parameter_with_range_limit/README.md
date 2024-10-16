# parameters demo (cpp)
> This program prints `Hello <parameter>` in a loop
> the parameter defaults to `world`
> *copied from [ros wiki](https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Using-Parameters-In-A-Class-CPP.html)*

**Run in container:**
```bash
podman run -it --privileged --network=host -v ~/Code/bento_examples/:/bento_ws/src/ --name bento_examples --rm rosbox:robot bash

# in container
rm -rf install/ build/ log/
colcon build --packages-select cpp_parameters
source install/setup.bash
ros2 run cpp_parameters minimal_param_node & # run in background
ros2 param set /minimal_param_node my_parameter "jazz"
fg # move back to foreground, kill with ctrl+c
```
