/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package team1073.smartdashboard.extension.roborealmapi;

import edu.wpi.first.wpilibj.networktables.NetworkTable;

import java.awt.Color;
import java.awt.image.BufferedImage;

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
    
    final double imageH = 600;
    final double deltaH = 63;
    final double cameraFieldOfView = 34.2;
    final double cameraAngle = 2;
    final double theta1 = (3.141592/180)*(cameraAngle/2);
    final double theta2 = ((3.141592/180)*(cameraFieldOfView/2)) - theta1;
    final double targetCenter = 103.25/12;
    final double maxRPM = 3600;
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
        
        
                
        distance = deltaH/(Math.tan((Math.atan((underneathH - (imageH/2))*(Math.tan(theta1+theta2)/240)))+theta2-theta1));

        targetAngle = Math.atan(targetCenter/distance);
        targetRPM = maxRPM;
        System.out.println(distance + " , " + targetAngle + " , " + targetRPM);
        
        sendCalcValues(targetAngle, targetRPM);
        
        // distance calcs
//        if (variables[0] != 0) {
//            distance = (deltaH/(Math.tan(variables[0]+theta2-theta1)))/12;
//        }
//        
//        Calcs calc = new Calcs();
//        final double MIDDLE_TARGET_HEIGHT = 101/12;
//        // Creating useless variables that don't need to exist
//        double projectedPath = calc.getHeight(distance, currentSpeed, currentAngle);
//        System.out.println(projectedPath);
//        double PixelToLifeRatio = variables[1]/variables[2];
//        // Implementing useless variables to give a value to another variable
//        double projectedPointY = variables[4] - (MIDDLE_TARGET_HEIGHT - projectedPath)*PixelToLifeRatio;
//        
//        // Drawing point
//        image.getGraphics().fillOval((int)variables[3], (int)projectedPointY, 10, 10);
        
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
            System.out.println("ERROR: BLAME PEPIN");
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
            currentAngle = (float) visionTable.getNumber("currentAngle");
            currentSpeed = (float) visionTable.getNumber("currentSpeed");
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
