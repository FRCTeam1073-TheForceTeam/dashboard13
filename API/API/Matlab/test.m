% See http://www.roborealm.com/help/API.php for more information
% about the RoboRealm API. Below are example routines that use the
% mex RoboRealm.dll located in this same folder that is used to
% integrate Matlab with RoboRealm. Note that most of the file  is
% commented out except for the first few lines. Thus you can run this
% without causing any harm.

% if RR is not running ... you can start it from Matlab
RoboRealm('open', 'c:\www\RoboRealm\bin\RoboRealm.exe', 6060);

[width, height] = RoboRealm('get_dimension');
fprintf(1, 'Dimension: %d, %d\n', width, height);

%count = RoboRealm('get_variable', 'IMAGE_COUNT');
%fprintf(1, 'Current image count: %d\n', count);

%img = RoboRealm('get_image'); 
%imshow(img);

%I = imread('remo.ppm');
%RoboRealm('set_image', I); 

%[width, height, fps, count] = RoboRealm('get_variables', 'image_width,image_height,fps,image_count');
%fprintf(1, 'Width: %s Height: %s FPS: %s Count:%s\n', width, height, fps, count);

%RoboRealm('set_variable', 'test', 1234.56);
%RoboRealm('set_variable', 'test_str', 'my_string');

%RoboRealm('set_variables', 'test', 789.56, 'test_str', 'my_next_string');

%RoboRealm('delete_variable', 'test');
%RoboRealm('delete_variable', 'test_str');

%RoboRealm('execute', '<RGB_Filter><min_value>40</min_value><channel>3</channel></RGB_Filter>');

%RoboRealm('load_program', 'c:/temp/mex/test.robo');

%current_xml_program = RoboRealm('get_program');
%fprintf(1, current_xml_program);

%RoboRealm('load_image','c:\temp\mex\remo.ppm');

%RoboRealm('save_image','c:\temp\mex\processed.ppm');

%RoboRealm('set_camera', 'Quickcam');

%camera_name = RoboRealm('get_camera');
%fprintf(1, camera_name);

%RoboRealm('run', 'off');
%RoboRealm('run', 'on');

%RoboRealm('wait_variable', 'IMAGE_COUNT', '2700', 100000);

%RoboRealm('wait_image');

%RoboRealm('minimize_window');
%RoboRealm('maximize_window');
%RoboRealm('move_window', 100, 100);
%RoboRealm('resize_window', 640 , 480);
%RoboRealm('position_window', 100, 100, 640, 480);

%[width, height, frame_rate, compression] = RoboRealm('get_camera_format');
%fprintf(1, 'Capture Width: %d Capture Height: %d FPS: %d Compression:%s\n', width, height, frame_rate, compression);

%RoboRealm('set_camera_format', 640, 480, 30, 'RGB');

%[properties] = RoboRealm('get_camera_properties');
%fprintf(1, '%s\n', properties);

%[brightness, gain, exposure] = RoboRealm('get_camera_properties', 'brightness','gain','exposure');
%fprintf(1, 'Value: %d Min %d Max %d Automatic %d\n', brightness(1), brightness(2), brightness(3), brightness(4));

% property_name, value, set_automatic
%RoboRealm('set_camera_properties', 'brightness',200,0);

RoboRealm('disconnect');

% unload the dll in case you are recompiling
%clear mex;
