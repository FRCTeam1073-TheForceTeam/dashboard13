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
    double currentAngle = 0;
    double currentSpeed = 0;
    
    //camera resolution
//    final double imageH = 600;
//    final double imageW = 800;
    final int imageH = 480;
    final int imageW = 640;
    
    //robot or situation dependent variables
    final double cameraHeight = 20.5;
    final double elevation = 0;
    double deltaH = cameraHeight + elevation; // changes depending on target
    final double cameraAngle = 15.7;
    final double HIGH_DELTA_H = 101 - deltaH;
    final double MIDDLE_DELTA_H = 84 - deltaH;
    final double TARGET_WIDTH = 54;
    
    //final double deltaH = deltaH0-34; // used for stairs (or, like, a robot. but really when is that gonna happen. i mean do you honestly think we're gonna be able to shoot discs at a target that is like seven feet up in the air? no, i didn't think so either. but i guess mechanical does.... idk sucks to be them), delete otherwise
    final double cameraOffset = 0;
    double targetCenter = 103.25;
    final double midTargetCenter = 103.25;
    final double highTargetCenter = 111;
    
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
    
    // random constant
    final double k = (imageW/(2*Math.tan(cameraFieldOfView/2))) * (imageW/(2*Math.tan(cameraFieldOfView/2)));
    
    VisionProccesing()
    {
        //NetworkTable.setTeam(1073);
        //NetworkTable.setClientMode();
        //NetworkTable.setIPAddress("10.10.73.2");
        visionTable = NetworkTable.getTable("tracking");
    }

    public BufferedImage processImage(BufferedImage rawImage, double underneathHX, double underneathHY, double targetRatio, double rightUnderneathHX, double rightUnderneathHY)
    {  
        image = rawImage; //not neccesary, but ok as a backup in case we want to use in different functions
        getCurrentValues();//gets actual valus from robot, see below
        
        //do processing and image overlaying here
        //Don't tell me what to do, Courtney!
        
        // target type determining
        if(Math.abs(targetRatio - HIGH_RATIO) < Math.abs(targetRatio - MIDDLE_RATIO)) {
            isHighGoal = true;
        } else {
            isHighGoal = false;
        }
                
        deltaH = (isHighGoal?HIGH_DELTA_H:MIDDLE_DELTA_H);
        targetCenter = (isHighGoal?highTargetCenter:midTargetCenter);
                
        distance = getDistance(underneathHX, underneathHY);
        double rightDistance = getDistance(rightUnderneathHX, rightUnderneathHY);
        double xOffset = (rightDistance*rightDistance - distance*distance - TARGET_WIDTH*TARGET_WIDTH) / (2*TARGET_WIDTH);
        double yOffset = Math.sqrt(distance*distance - xOffset*xOffset);
        double angleOffset = Math.atan(xOffset/yOffset) * 180 / Math.PI;
        
        // correction

        System.out.println("distance: " + distance);
        System.out.println("rightDistance: " + rightDistance);
        System.out.println("xOffset: " + xOffset);
        System.out.println("yOffset: " + yOffset);
        System.out.println("angleOffset: " + angleOffset);
        
        //System.out.println(alpha + ", " + underneathH);
        
//        System.out.println("distance:  " + distance);
//        System.out.println("underneathH:  " + underneathH);
//        System.out.println("alpha:  " + alpha);
//        System.out.println("theta1:  " + theta1);
//        System.out.println("theta2:  " + theta2);
//        System.out.println("imageH:  " + imageH);
        
        //System.out.println(distance + " , " + theta1 + " , " + theta2 + " , " + imageH + " , ");
        
        //calculate "optimal" shooter state
        //double[] target = optimize(currentAngle, currentSpeed, distance, isHighGoal);
        double[] target = new double[2];
        target[0] = 30;
        target[1] = 2000;
        targetAngle = target[0];
        targetRPM = target[1];
        //distance = 350;
        //sends "optimal" speed and angle to robot
        
        sendCalcValues(targetAngle, targetRPM);
        //sendFakeValues();
        
        //Distance calculations
        
        //find point of impact based on current shooter state
        Calcs calc = new Calcs();
        impactH = 39.37 * calc.getHeight(distance / 39.37, currentSpeed, currentAngle); //THIS LINE CHANGED!!!!!!!!!!!!!
        int impactXPixel = 0;
        int impactYPixel = 0;
        
        if (impactH == 0)
        {       
           System.out.println("ALDSKFJASD;LKFJASLDK;FJASLDKFJASKLDFJASKLDFJ");
            return image;
        } else {
        //finding Y coordinate (Anish version)
          double deltaH2 = impactH - cameraHeight - elevation;
//        double numerator = Math.tan (Math.atan(deltaH2 / (distance)) + theta2 - theta1);
//        double denominator = Math.tan(theta1 + theta2);
//        impactYPixel = (int) ((imageH/2) * (1 - (numerator)/(denominator))); 
  
        double zero = imageH/(2 * Math.tan(theta1 + theta2));   //BADASS MOFO UP IN THIS BITCH.
        double three = 0 - Math.atan(deltaH2 / distance) + theta2 - theta1;
        impactYPixel = imageH - ((int) ((imageH/2) - (zero * Math.tan(three))));
            
        System.out.println("distance:  " + distance + "\nimpactH:  " + impactH+ "\nimpactYPixel:  " + impactYPixel);
        //System.out.println("underneathH:  " + underneathH);
        //System.out.println("delataH2:  " + deltaH2);
        //System.out.println("e:  " + zero);
        //System.out.println("thetathree:  " + three);
        //System.out.println("impactH:  " + impactH);
        //System.out.println("impactYPixel:  " + impactYPixel);
        
        
        //finding X coordinate
        impactXPixel = (int) ((imageW/2) * (1+(cameraOffset / (distance * Math.tan(cameraHorizontalView / 2)))));
        
        //draws reticle
        return drawing(image, impactXPixel, impactYPixel);
        }
    }
    
    public BufferedImage drawing(BufferedImage image, int X, int Y) 
    {
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
            g.drawString("impactH: " + Math.round(impactH) + ", distance "
                    + Math.round(distance) + ", Target type: " 
                    + (isHighGoal?"High":"Middle"), 15, (int)(imageH-20));
            
        return image;
    }
    
    
    
            
    private void getCurrentValues()
    {
        System.out.println("Is Connected: " + visionTable.isConnected());
        System.out.println("Is Server Mode: " + visionTable.isServer());
        
        try
        {
//            currentAngle = (float) visionTable.getNumber("currentAngle");
//            currentSpeed = (float) visionTable.getNumber("currentSpeed");
  
            currentAngle = 30;
            currentSpeed = 2800;
            
        }
        catch(Exception e)
        {
            System.out.println("Caught Exception in Network Table getNumber" + e);
//            currentAngle = 20;
//            currentSpeed = 2500;
        }
        
        System.out.println("currentAngle: " + currentAngle + "   currentSpeed: " + currentSpeed);
        
                
    }
            
    private void sendCalcValues(double angle, double calcRPM)
    {
        visionTable.putNumber("calculatedAngle", angle);
        visionTable.putNumber("calculatedVelocityRPM", calcRPM);
    }
    
    private void sendFakeValues()
    {
        visionTable.putNumber("calculatedAngle", 34);
        visionTable.putNumber("calculatedVelocityRPM", 2500);
    }
    
    
    public double[] optimize(double currentAngle, double currentRPM, double distance, boolean targetType){
        final int targetHeight = isHighGoal?101:84;
        final int max = targetHeight + 2;
        final int min = targetHeight - 2;
        double[] optimal = new double[2];
        double testAngle = currentAngle;
        double testRPM = currentRPM;
        Calcs test = new Calcs();
        while(min > test.getHeight(testAngle, testRPM, distance) || test.getHeight(testAngle, testRPM, distance) > max){
            if (test.getHeight(testAngle, testRPM, distance) > max){
                testRPM -= 100;
            } else {
                if(test.getHeight(testAngle, testRPM, distance) < test.getHeight(testAngle - 1, testRPM, distance)){
                    testAngle--;
                }else if (test.getHeight(testAngle + 1, testRPM, distance) > test.getHeight(testAngle, testRPM, distance)){
                    testAngle++;
                } else {
                    testRPM += 100;
                }
            }
        }
        optimal[0] = testAngle;
        optimal[1] = testRPM;
        return optimal;
    }
    
    private double getDistance(double x, double y) {
        return ((deltaH/(Math.tan(Math.atan((((y - (imageH/2))*(Math.tan(theta1+theta2)))/(imageH/2))) + theta2 - theta1)))/k)*Math.sqrt((x-imageW/2)*(x-imageW/2)-k);
        
    }

    
}
