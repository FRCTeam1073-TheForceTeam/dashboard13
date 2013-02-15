/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package team1073.smartdashboard.extension.roborealmapi;

import edu.wpi.first.wpilibj.networktables.NetworkTable;
<<<<<<< HEAD
=======
import java.awt.Color;
>>>>>>> Added Calcs to Vision Extension (Not Working)
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
<<<<<<< HEAD
    float currentAngle;
    float currentSpeed;
=======
    double currentAngle = 0;
    double currentSpeed = 0;
    
    final double deltaH = 63;
    final double cameraFieldOfView = 34.2;
    final double cameraAngle = 2;
    final double theta1 = (3.141592/180)*(cameraAngle/2);
    final double theta2 = ((3.141592/180)*(cameraFieldOfView/2)) - theta1;
    double distance = 0;
>>>>>>> Added Calcs to Vision Extension (Not Working)
    
    VisionProccesing()
    {
        //NetworkTable.setTeam(1073);
        //NetworkTable.setClientMode();
        //NetworkTable.setIPAddress("10.10.73.2");
        visionTable = NetworkTable.getTable("tracking");
        
    }

    public BufferedImage proccessImage(BufferedImage rawImage, RR_API roboApi)
<<<<<<< HEAD
    {
=======
    {  
>>>>>>> Added Calcs to Vision Extension (Not Working)
        image = rawImage; //not neccesary, but ok as a backup in case we want to use in different functions
        api = roboApi;
        variables = getRRVariables();//gets roboRealm's variables, see below
        getCurrentValues();//gets actual valus from robot, see below
        
        //do processing and image overlaying here
<<<<<<< HEAD
=======
        //Don't tell me what to do, Courtney!
        
        // distance calcs
        if (variables[0] != 0) {
            distance = (deltaH/(Math.tan(variables[0]+theta2-theta1)))/12;
        }
        
        Calcs calc = new Calcs();
        final double MIDDLE_TARGET_HEIGHT = 101/12;
        // Creating useless variables that don't need to exist
        double projectedPath = calc.getHeight(distance, currentSpeed, currentAngle);
        System.out.println(projectedPath);
        double PixelToLifeRatio = variables[1]/variables[2];
        // Implementing useless variables to give a value to another variable
        double projectedPointY = variables[4] - (MIDDLE_TARGET_HEIGHT - projectedPath)*PixelToLifeRatio;
        
        // Drawing point
        image.getGraphics().setColor(Color.red);
        image.getGraphics().drawOval((int)variables[3], (int)projectedPointY, 5, 5);
>>>>>>> Added Calcs to Vision Extension (Not Working)
        
        return image;
    }
    
    private double[] getRRVariables()
    {
<<<<<<< HEAD
        //only call from proccessImage function please
        double[] values = new double[8];
        
        String variable = api.getVariable("testVariable");
        System.out.println("RoboRealm returned variable :" + variable);
        values[0] = Double.parseDouble(variable);
        //add more getVariable calls for more variables
        
=======
        
        //only call from proccessImage function please
        double[] values = new double[8];
        
        //String variable = api.getVariable("Distance");
        //System.out.println("RoboRealm returned variable :" + variable);
        try
        {
            System.out.println("hi");
        values[0] = Double.parseDouble(api.getVariable("alpha"));
        System.out.println(values[0]);
        values[1] = Double.parseDouble(api.getVariable("targetH"));
        System.out.println(values[1]);
        values[2] = Double.parseDouble(api.getVariable("IMAGE_HEIGHT"));
        System.out.println(values[2]);
        values[3] = Double.parseDouble(api.getVariable("targetCenterX"));
        System.out.println(values[3]);
        values[4] = Double.parseDouble(api.getVariable("targetCenterY"));
        System.out.println(values[4]);
        System.out.println("bye");
        }
        catch(Exception e)
        {
            System.out.println("ERROR: BLAME PEPIN");
        }
        //add more getVariable calls for more variables
        //Don't tell me what to do!
            
>>>>>>> Added Calcs to Vision Extension (Not Working)
        return values;
    }
    
    private void getCurrentValues()
    {
        System.out.println("Is Connected: " + visionTable.isConnected());
        System.out.println("Is Server Mode: " + visionTable.isServer());
        
        try
        {
<<<<<<< HEAD
            currentAngle = (float) visionTable.getNumber("currentAngle");
            currentSpeed = (float) visionTable.getNumber("currentSpeed");
=======
            currentAngle = visionTable.getNumber("currentAngle");
            currentSpeed = visionTable.getNumber("currentSpeed");
>>>>>>> Added Calcs to Vision Extension (Not Working)
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
