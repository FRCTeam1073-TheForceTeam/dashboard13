/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package team1073.smartdashboard.extension.roborealmapi;

import edu.wpi.first.wpilibj.networktables.NetworkTable;

import java.awt.Color;
import java.awt.Font;
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
    double underneathH;
    double currentAngle = 0;
    double currentSpeed = 0;
    
    //camera resolution
//    final double imageH = 600;
//    final double imageW = 800;
    final double imageH = 480;
    final double imageW = 640;
    
    //robot or situation dependent variables
    final double cameraHeight = 25;
    final double elevation = 34;
    double deltaH = cameraHeight + elevation; // changes depending on target
    final double cameraAngle = 17.8;
    final double HIGH_DELTA_H = 101 - deltaH;
    final double MIDDLE_DELTA_H = 84 - deltaH;
    
    //final double deltaH = deltaH0-34; // used for stairs (or, like, a robot. but really when is that gonna happen. i mean do you honestly think we're gonna be able to shoot discs at a target that is like seven feet up in the air? no, i didn't think so either. but i guess mechanical does.... idk sucks to be them), delete otherwise
    final double cameraOffset = 0;
    final double targetCenter = 103.25;
    
    final double maxRPM = 3600;
    
    //calibrated values for m1013
    final double cameraFieldOfView = 48.8;
    final double cameraHorizontalView = 67;
   
    //calculated values for making distance calcs easier
    final double theta1 = (3.141592/180)*(cameraAngle/2);
    final double theta2 = ((3.141592/180)*(cameraFieldOfView/2)) - theta1;
    
    //initializing variables from robot
    double distance = 0;
    double targetAngle = 0;
    double targetRPM = 0;
    
    // target determining
    final double MIDDLE_RATIO = 2.32;
    final double HIGH_RATIO = 3.1;
    double targetRatio = 0;
    double impactH = 0;
    boolean isHighGoal = false;
    double deltaT;
    
    VisionProccesing()
    {
        //NetworkTable.setTeam(1073);
        //NetworkTable.setClientMode();
        //NetworkTable.setIPAddress("10.10.73.2");
        visionTable = NetworkTable.getTable("tracking");
        
    }

    public BufferedImage processImage(BufferedImage rawImage, double underneathH, double targetRatio)
    {  
        deltaT = System.nanoTime();
        image = rawImage; //not neccesary, but ok as a backup in case we want to use in different functions
        getCurrentValues();//gets actual valus from robot, see below
        
        //do processing and image overlaying here
        //Don't tell me what to do, Courtney!
        
        //Distance calculations
                if(Math.abs(targetRatio - HIGH_RATIO) < Math.abs(targetRatio - MIDDLE_RATIO)) {
            isHighGoal = true;
        } else {
            isHighGoal = false;
        }
                
        deltaH = (isHighGoal?HIGH_DELTA_H:MIDDLE_DELTA_H);
        
        double alpha = Math.atan((((underneathH - (imageH/2))*(Math.tan(theta1+theta2)))/(imageH/2)));        
        distance = deltaH/(Math.tan(alpha + theta2 - theta1));
        
        System.out.println("raw distance: " + distance);
        
        // correction
        if(!isHighGoal) {
            distance = 1.1849*distance - 25.659;
        } else {
            distance = 1.018*distance - 3.9154;
        }
        
        
        //System.out.println(alpha + ", " + underneathH);
        
//        System.out.println("distance:  " + distance);
//        System.out.println("underneathH:  " + underneathH);
//        System.out.println("alpha:  " + alpha);
//        System.out.println("theta1:  " + theta1);
//        System.out.println("theta2:  " + theta2);
//        System.out.println("imageH:  " + imageH);
        
        //System.out.println(distance + " , " + theta1 + " , " + theta2 + " , " + imageH + " , ");
        
        //calculate "optimal" shooter state
        targetAngle = Math.atan(targetCenter/distance);
        targetRPM = maxRPM;
        //distance = 350;
        //sends "optimal" speed and angle to robot
        
        sendCalcValues(targetAngle, targetRPM);
        
        
        //find point of impact based on current shooter state
        Calcs calc = new Calcs();
        impactH = 39.37 * calc.getHeight(distance / 39.37, currentSpeed, currentAngle, cameraHeight);
        int impactXPixel = 0;
        int impactYPixel = 0;
        
        if (impactH != 0){
        
        //finding Y coordinate
        double deltaH2 = impactH - cameraHeight;
        double numerator = Math.tan (Math.atan(deltaH2 / (distance)) + theta2 - theta1);
        double denominator = Math.tan(theta1 + theta2);
        impactYPixel = (int) ((imageH/2) * (1 - (numerator)/(denominator))); 
  
//        double zero = imageH/(2 * Math.tan(theta1 + theta2));   //BADASS MOFO UP IN THIS BITCH.
//        double three = Math.atan(deltaH2 / distance) + theta2 - theta1;
//        impactYPixel = (int) ((imageH/2) - (zero * Math.tan(three)));
        
        
        
        System.out.println("distance:  " + distance + "\nimpactH:  " + impactH);
        //System.out.println("underneathH:  " + underneathH);
        //System.out.println("delataH2:  " + deltaH2);
        //System.out.println("e:  " + zero);
        //System.out.println("thetathree:  " + three);
        //System.out.println("impactH:  " + impactH);
        //System.out.println("impactYPixel:  " + impactYPixel);
        
        
        //finding X coordinate
        impactXPixel = (int) ((imageW/2) * (1+(cameraOffset / (distance * Math.tan(cameraHorizontalView / 2)))));
        }
        
        // target type determining

        
        deltaT = System.nanoTime() - deltaT;
        System.out.println("DeltaT: " + deltaT);
        
        //draws reticle
        return drawing(image, impactXPixel, impactYPixel);
    }
    
    public BufferedImage drawing(BufferedImage image, int X, int Y) {
        if (impactH != 0){
        Graphics g = image.getGraphics();
        
        //reticle Parameters
        int radius = 10;
        g.setColor(Color.RED);
        g.drawLine(X - radius, Y, X + radius, Y);
        g.drawLine(X, Y - radius, X, Y + radius);
        g.drawOval(X-radius, Y-radius, 2*radius, 2*radius);
        
        // strings
        g.setColor(Color.WHITE);
        g.setFont(new Font("Matt Carr", Font.BOLD, 22));
        g.drawString("RPM: " + Math.round(currentSpeed) + ", Angle: "
                + Math.round(currentAngle) + ", Target Angle:" 
                + Math.round(targetAngle) + ", Target type: " 
                + (isHighGoal?"High":"Middle"), 15, (int)(imageH-20));
        }
                
        return image;
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
            currentSpeed = 2000;
        
        }
        catch(Exception e)
        {
            System.out.println("Caught Exception in Network Table getNumber" + e);
        }
        
        System.out.println("currentAngle: " + currentAngle + "   currentSpeed: " + currentSpeed);
        
                
    }
            
    private void sendCalcValues(double angle, double velocityRPM)
    {
        visionTable.putNumber("calculatedAngle", angle);
        visionTable.putNumber("calculatedVelocityRPM", velocityRPM);
    }
    
}
