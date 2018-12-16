pixy2_ros
=========

Basic ROS node to publish image from a [pixy2](http://www.cmucam.org/projects/cmucam5/wiki) camera.

This code is based in the orginal code [erle_pixy](https://github.com/erlerobot/erle_pixy/) for version 1.0.

# Add permissions for Pixy USB interface

In order to communicate with Pixy over USB as a non-root user you must set permissions for Pixy.

To do this copy the 'pixy.rules' file to '/etc/udev/rules.d'

```
sudo cp pixy.rules /etc/udev/rules.d/
```

#Compile the code 

Add this folder to `catkin_ws/src` or similar ROS workspace and then compile the code:

```
>> cd <your catkin_worspace>
>> catkin_make
```

You need to load the script:

```
>> source <your catkin_worspace>/devel/setup.bash
```

#Usage

Whit this component you can see the image from Pixy2 Cam.

```
>>rosrun pixy2_ros pixy2_cam
```

#Parameters

`image_raw` to change the desired topic for example:

```
<remap from="image_raw" to="/camera/rgb/image"/>
```

`frame_rate` to change the camera frame rate, from 1 to 60, for example:

```
<param name="frame_rate" type="int" value="5" />
```


#Show the image

To visualize the image to need to run:

```
>>rosrun image_view image_view image:=/image_raw
```
