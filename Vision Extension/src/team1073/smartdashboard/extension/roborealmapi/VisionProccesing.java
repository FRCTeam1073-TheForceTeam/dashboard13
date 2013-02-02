/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package team1073.smartdashboard.extension.roborealmapi;

import java.awt.image.BufferedImage;

/**
 *
 * @author Greg
 */
public class VisionProccesing {
    
    BufferedImage image;
    RR_API api;
    float[] variables;
    
    VisionProccesing()
    {
        //add constructor code here if neccessary
    }

    public BufferedImage proccessImage(BufferedImage rawImage, RR_API roboApi)
    {
        image = rawImage; //not neccesary, but ok as a backup in case we want to use in different functions
        api = roboApi;
        variables = getRRVariables();
        
        //do processing and image overlaying here
        
        return image;
    }
    
    private float[] getRRVariables()
    {
        //only call from proccessImage function please
        float[] values = new float[8];
        
        String variable = api.getVariable("nameOfYourVariableHere");
        System.out.println("RoboRealm returned variable :" + variable);
        values[0] = Float.parseFloat(variable);
        //add more getVariable calls for more variables
        
        return values;
    }
            
    
}
