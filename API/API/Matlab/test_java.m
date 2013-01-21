% tell matlab where RR_API.class is
javaaddpath('C:\Program Files\RoboRealm\API\Java');

% create a new RR API object
rr = RR_API();

% connect to RoboRealm (assumes API is on and RR is running)
rr.connect('localhost');

% sample to get a variable's value
fprintf(1, char(rr.getVariable('IMAGE_COUNT')));

% get the current processed image
imgBytes = rr.getImage('processed');

h = rr.height;
w = rr.width;

imgData = zeros([h,w,3],'uint8');
pixelsData = reshape(typecast(imgBytes,'uint32'),w,h).';
imgData(:,:,3) = bitshift(bitand(pixelsData,256^1-1),-8*0);
imgData(:,:,2) = bitshift(bitand(pixelsData,256^2-1),-8*1);
imgData(:,:,1) = bitshift(bitand(pixelsData,256^3-1),-8*2);

% show grabbed image
imshow(imgData);

% disconnect from the RR API server
rr.disconnect();



