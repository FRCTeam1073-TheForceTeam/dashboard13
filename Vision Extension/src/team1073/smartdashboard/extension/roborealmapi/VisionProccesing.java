/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package team1073.smartdashboard.extension.roborealmapi;

import edu.wpi.first.wpilibj.networktables.NetworkTable;
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
    double currentAngle;
    double currentSpeed;
    
    VisionProccesing()
    {
        NetworkTable.setTeam(1073);
        NetworkTable.setIPAddress("10.10.73.2");
        visionTable = NetworkTable.getTable("tracking");
        
    }

    public BufferedImage proccessImage(BufferedImage rawImage, RR_API roboApi)
    {
        image = rawImage; //not neccesary, but ok as a backup in case we want to use in different functions
        api = roboApi;
        variables = getRRVariables();//gets roboRealm's variables, see below
        getCurrentValues();//gets actual valus from robot, see below
        
        //do processing and image overlaying here
        
        return image;
    }
    
    private double[] getRRVariables()
    {
        //only call from proccessImage function please
        double[] values = new double[8];
        
        String variable = api.getVariable("testVariable");
        System.out.println("RoboRealm returned variable :" + variable);
        values[0] = Double.parseDouble(variable);
        //add more getVariable calls for more variables
        
        return values;
    }
    
    private void getCurrentValues()
    {
        try
        {
            currentAngle = visionTable.getNumber("currentAngle");
            currentSpeed = visionTable.getNumber("currentSpeed");
        }
        catch(Exception e){System.out.println("Exception in Network Table getNumber" + e);}
        
        System.out.println("currentAngle: " + currentAngle + "   currentSpeed: " + currentSpeed);
        System.out.println("Is Connected: " + visionTable.isConnected());
    }
            
    private void sendCalcValues(double angle, double distance)
    {
        visionTable.putNumber("calcAngle", angle);
        visionTable.putNumber("calcDistance", distance);
    }
    
}
