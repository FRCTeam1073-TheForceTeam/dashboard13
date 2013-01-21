import processing.net.*; 
Client rr; 
String message; 
String totalMsg; 
 
void setup() 
{ 
  size(200, 200); 
  // Connect to the local machine at port 5204.
  // This example will not run if you haven't
  // previously started a server on this port
  rr = new Client(this, "127.0.0.1", 6060); 
} 
 
String readMessage()
{
  int count=0;
  String msg;
  totalMsg = "";
  
  while ((++count)<10000)
  {
    while (rr.available() <= 0);

    msg = rr.readStringUntil('>');
    if (msg!=null)
    {
      totalMsg = totalMsg + msg;
      if (totalMsg.length()>11)
      {
        if (totalMsg.substring(totalMsg.length()-11).equals("</response>"))
        {
          return totalMsg;
        }
      }
    }
  }
  
  return null;
}

int getVariable(String name)
{
  rr.write("<request><get_variable>"+name+"</get_variable></request>\n");
  message = readMessage();
  if (message!=null)
  {
    String[] m = match(message, "<response>[^>]+>([^<]+)");
    if (m!=null) return Integer.parseInt(m[1]);
  }
  
  return 0;
}  
 
void draw() 
{ 
  background(0);
  
  int result = getVariable("IMAGE_COUNT");
  println("The current image count is "+result);
}

