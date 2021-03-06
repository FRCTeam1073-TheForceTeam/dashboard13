/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package team1073.smartdashboard.extension.roborealmapi;

import java.awt.Dimension;
import java.awt.image.BufferedImage;
import java.io.File;
import java.util.Date;
import javax.imageio.ImageIO;
import javax.swing.SwingWorker;

/**
 *
 * @author Greg
 */
public class CameraThread extends SwingWorker<BufferedImage, BufferedImage> {
    
    RR_API roboApi;
    BufferedImage savedImage = null;
    int imageCount = 0;
    double underneathHY;
    double underneathHX;
    double rightUnderneathHY;
    double rightUnderneathHX;
    double targetRatio;
    
CameraThread()
{
    roboApi = new RR_API();
    roboApi.connect("localhost");

}
  
protected void process(BufferedImage image)
{
    savedImage = image;
}

public BufferedImage getSavedImage()
{
    return savedImage;
}
public double getUnderneathHY()
{
    return underneathHY;
}

public double getUnderneathHX()
{
    return underneathHX;
}

public double getRightUnderneathHY()
{
    return rightUnderneathHY;
}

public double getRightUnderneathHX()
{
    return rightUnderneathHX;
}

public double getTargetRatio()
{
    return targetRatio;
}
        
    public BufferedImage displayImage() {
        //one byte for each r, g, or b value
        //Dimension size = new Dimension(800, 600);
        Dimension size = new Dimension(640, 480);
        int[] pixels = roboApi.getImage("processed");
        BufferedImage image = null;
        
        try { 
            image = new BufferedImage(size.width, size.height, BufferedImage.TYPE_INT_RGB);
            image.setRGB(0, 0, size.width, size.height, pixels, 0, size.width);
            
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        
        return image;
    }


    @Override
    protected BufferedImage doInBackground() throws Exception {
       
        BufferedImage image;
        Date d = new Date();
        String folderName = (d.getMonth()+1) + "_" + d.getDay() +"_"+ (d.getHours()%12) + "_" + d.getMinutes();
        File folder = new File("C:/"+folderName);
        folder.mkdir();
        
        while(! isCancelled())
        {   
            image = this.displayImage();
            savedImage = image;
            imageCount++;
            
            getRRVariables();

            System.out.println("Image Count:" + imageCount);
            setProgress(imageCount % 99);
            
            if (imageCount % 10 == 0)
            {
                String filename = String.format("C:/%s/test %5d.bmp", folderName, imageCount);
                ImageIO.write(image, "bmp", new File(filename));
            }
            // Change FPS here:
            Thread.sleep(200);
        }
        
        
        return null;    
    }
    
    public RR_API getApi()
    {
        return roboApi;
    }
    
    private void getRRVariables()
    {
        //only call from proccessImage function please
        
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
          underneathHX = Double.parseDouble(roboApi.getVariable("underneathHX"));
          underneathHY = Double.parseDouble(roboApi.getVariable("underneathHY"));
          rightUnderneathHX = Double.parseDouble(roboApi.getVariable("rightUnderneathHX"));
          rightUnderneathHY = Double.parseDouble(roboApi.getVariable("rightUnderneathHY"));
          targetRatio = Double.parseDouble(roboApi.getVariable("targetRatio"));
          if(roboApi.getVariable("targetRatio") == null) {
               targetRatio = 0;
           }
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
            
    }
    
    
}
