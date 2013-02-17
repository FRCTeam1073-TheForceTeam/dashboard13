/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package team1073.smartdashboard.extension.roborealmapi;

import edu.wpi.first.wpilibj.networktables.NetworkTable;

import java.awt.Color;
import java.awt.image.BufferedImage;
import java.awt.Graphics;

/**
 *
 * @author Greg
 */
public class VisionProccesing {
    
    BufferedImage image;
    RR_API api;
    double[] variables;
    NetworkTable visionTable;
    float currentAngle;
    float currentSpeed;
    double underneathH;
    //double currentAngle = 0;
    //double currentSpeed = 0;
    
    //camera resolution
    final double imageH = 600;
    final double imageW = 800;
    
    //robot or situation dependent variables
    final double cameraAngle = 13.5;
    final double deltaH0 = 58;
    final double deltaH = deltaH0-34;
    final double cameraOffset = 0;
    final double targetCenter = 103.25;
    final double cameraHeight = 2;
    final double maxRPM = 3600;
    
    //calibrated values for m1013
    final double cameraFieldOfView = 47.3;
    final double cameraHorizontalView = 67;
   
    //calculated values for making distance calcs easier
    final double theta1 = (3.141592/180)*(cameraAngle/2);
    final double theta2 = ((3.141592/180)*(cameraFieldOfView/2)) - theta1;
    
    //initializing variables from robot
    double distance = 0;
    double targetAngle = 0;
    double targetRPM = 0;
    
    VisionProccesing()
    {
        //NetworkTable.setTeam(1073);
        //NetworkTable.setClientMode();
        //NetworkTable.setIPAddress("10.10.73.2");
        visionTable = NetworkTable.getTable("tracking");
        
    }

    public BufferedImage processImage(BufferedImage rawImage, RR_API roboApi)
    {  
        image = rawImage; //not neccesary, but ok as a backup in case we want to use in different functions
        api = roboApi;
        variables = getRRVariables();//gets roboRealm's variables, see below
        getCurrentValues();//gets actual valus from robot, see below
        
        //do processing and image overlaying here
        //Don't tell me what to do, Courtney!
        
        //Distance calculations
        double alpha = Math.atan((((underneathH - (imageH/2))*(Math.tan(theta1+theta2)))/(imageH/2)));        
        distance = deltaH/(Math.tan(alpha + theta2 - theta1));
        //System.out.println(alpha + ", " + underneathH);
        
        System.out.println("distance:  " + distance);
        System.out.println("underneathH:  " + underneathH);
        System.out.println("alpha:  " + alpha);
        System.out.println("theta1:  " + theta1);
        System.out.println("theta2:  " + theta2);
        System.out.println("imageH:  " + imageH);
        
        //System.out.println(distance + " , " + theta1 + " , " + theta2 + " , " + imageH + " , ");
        
        //calculate target shooter state
        targetAngle = Math.atan(targetCenter/distance);
        targetRPM = maxRPM;
        
        //sends "optimal" speed and angle to robot
        sendCalcValues(targetAngle, targetRPM);
        
        
        //find point of impact based on current shooter state
        Calcs calc = new Calcs();
        double impactH = 39.37 * calc.getHeight(distance / 39.37, currentSpeed, currentAngle);
        
        //finding Y coordinate
        double deltaH2 = impactH - cameraHeight;
        double numerator = Math.tan (Math.atan(deltaH2 / (distance * 12)) + theta2 - theta1);
        double denominator = Math.tan(theta1 + theta2);
        int impactYPixel = (int) ((imageH/2) * (1 - (numerator)/(denominator))); 
        
        //finding X coordinate
        int impactXPixel = (int) ((imageW/2) * (1+(cameraOffset / (distance * Math.tan(cameraHorizontalView / 2)))));
        
        
        //draws reticle
        return drawReticle(image, impactXPixel, impactYPixel);
    }
    
    public BufferedImage drawReticle(BufferedImage image, int X, int Y) {
        Graphics g = image.getGraphics();
        
        //reticle Parameters
        int radius = 10;
        
        g.drawLine(X - radius, Y, X + radius, Y);
        g.drawLine(X, Y - radius, X, Y + radius);
        g.drawOval(X-radius, Y-radius, 2*radius, 2*radius);
                
        return image;
    }
    
    
    private double[] getRRVariables()
    {
        //only call from proccessImage function please
        double[] values = new double[8];
        
        //String variable = api.getVariable("Distance");
        //System.out.println("RoboRealm returned variable :" + variable);
        try
        {
//        values[0] = Double.parseDouble(api.getVariable("alpha"));
//        System.out.println(values[0]);
//        values[1] = Double.parseDouble(api.getVariable("targetH"));
//        System.out.println(values[1]);
//        values[2] = Double.parseDouble(api.getVariable("IMAGE_HEIGHT"));
//        System.out.println(values[2]);
          underneathH = Double.parseDouble(api.getVariable("underneathH"));
//        System.out.println(values[3]);
//        values[4] = Double.parseDouble(api.getVariable("targetCenterY"));
//        System.out.println(values[4]);
        
//        double alpha = Math.atan((values[3] - (imageH/2))*(Math.tan(theta1+theta2)/240));
//        double distance = deltaH/(Math.tan(alpha+theta2-theta1));
        
        }
        catch(Exception e)
        {
            System.out.println("ERROR: BLAME PEPIN" + e);
        }
        //add more getVariable calls for more variables
        //Don't tell me what to do!
            
        return values;
    }
    
    private void getCurrentValues()
    {
        System.out.println("Is Connected: " + visionTable.isConnected());
        System.out.println("Is Server Mode: " + visionTable.isServer());
        
        try
        {
            //currentAngle = (float) visionTable.getNumber("currentAngle");
            //currentSpeed = (float) visionTable.getNumber("currentSpeed");
            currentAngle = 20;
            currentSpeed = 3000;
        
        }
        catch(Exception e)
        {
            System.out.println("Caught Exception in Network Table getNumber" + e);
        }
        
        System.out.println("currentAngle: " + currentAngle + "   currentSpeed: " + currentSpeed);
        
                
    }
            
    private void sendCalcValues(double angle, double distance)
    {
        visionTable.putNumber("calcAngle", angle);
        visionTable.putNumber("calcDistance", distance);
    }
    
}
