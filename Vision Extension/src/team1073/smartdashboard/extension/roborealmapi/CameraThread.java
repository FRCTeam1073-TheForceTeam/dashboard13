/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package team1073.smartdashboard.extension.roborealmapi;

import java.awt.Dimension;
import java.awt.image.BufferedImage;
import java.io.File;
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
        
    public BufferedImage displayImage() {
        //one byte for each r, g, or b value
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
        
        while(! isCancelled())
        {
            Thread.sleep(50);
            
            image = this.displayImage();
            savedImage = image;
            imageCount++;

            System.out.println("Image Count:" + imageCount);
            setProgress(imageCount % 99);
            
            if (imageCount % 10 == 0)
            {
                String filename = String.format("C:/images/test %5d.bmp", imageCount);
                ImageIO.write(image, "bmp", new File(filename));
            }
            
        }
        
        return null;    
    }
    
    public RR_API getApi()
    {
        return roboApi;
    }
    
}
