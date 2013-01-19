Instructions:
Simply place these into your Dashboard folder
e.g.=C:\Program Files (x86)\FRC Dashboard

The BroncBotz_Dashboard.ini may need to be changed for the path of the SmartDashBoard... by default this is
SmartDashboard C:\WindRiver\WPILib\SmartDashboard.jar

If your .ini ever gets corrupted simply delete for the default values... it will automatically save your preview windows position and size

Nov 15, 2012
Initial 1.0 proof of concept draft... simply populates the preview window with a streaming test pattern as a popup.

Nov 17 2012
Given ability to merge the preview inside the smart dashboard as a child window... The .ini file lets you choose the whether or not to use a popup... you can fix the window and size while in popup then set it to 0 to make it a child

Nov 19 2012
Added context menu to switch from popup to child... it will allow to position and size window in the smart dashboard

Nov 20 2012
Added properties in .ini needed to have multiple video feeds
Added plug-in dll example that draws in green block
Changed .ini name to Video1 by default, and demo a 2 feed setup

Nov 21 2012
Added ability to lock aspect ratio for 4:3 or 16:9 (or stretch)
Added ability to show 480i or half res (will show 480 of 16:9 if that aspect was selected)
Added Editable option to allow child windows to be repositioned
The Video2.ini is popup to demo the aspect only works in popup mode (as does resizing)

Nov 28 2012
Added a preliminary frame grabber that is ffmpeg and supports RTSP (h264 of the m1011 camera)
This also supports files (currently video only), and testpattern (using none)
This version is very clunky and has latency issues due to the queue
-Fixed bug with the editable rectangle region blit

Nov 29 2012
Improved latency in ffmpeg, and improved preview blt timing... both are much better, but I may be able
to get this even better.

Nov 30 2012
The preview had one last bug in it removed... now it runs properly (I'm confident it is ready to go now).
The framing is very smooth as shown in the test pattern. The horizontal lines are always visible at half res
as they are in the field test on the line in the color gradient region.
Now... just need to get the latency down!

Dec 4 2012
Released 1.1 enabled NI_Vision, and gave ability to choose mjpeg as the streaming profile (which does not have latency issues).
