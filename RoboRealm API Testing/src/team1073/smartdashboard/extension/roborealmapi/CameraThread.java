/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package team1073.smartdashboard.extension.roborealmapi;

import edu.wpi.first.smartdashboard.gui.StaticWidget;
import edu.wpi.first.smartdashboard.properties.Property;
import java.awt.Dimension;
import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import javax.imageio.ImageIO;
import java.awt.image.MemoryImageSource;
import java.awt.Image;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.SwingWorker;

/**
 *
 * @author Greg
 */
public class CameraThread extends SwingWorker<BufferedImage, BufferedImage> {
    
    RR_API roboApi;
    BufferedImage savedImage = null;
    
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
            /*MemoryImageSource source;
            source = new MemoryImageSource(size.width, size.height, pixels, 0, size.width);
            source.setAnimated(true);*/
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
        int imageCount = 0;
        while(! isCancelled())
        {
            image = this.displayImage();
            savedImage = image;
            imageCount++;
            setProgress(imageCount);
            String filename = String.format("C:/images/test %5d.bmp", imageCount);
            ImageIO.write(image, "bmp", new File(filename));
        }
        
        return null;    
    }
    
    
    
}
